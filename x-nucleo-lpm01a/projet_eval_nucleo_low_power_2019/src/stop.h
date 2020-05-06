#include "mbed.h"
#include "stm32l073xx.h"

#define _CLEAR_BIT(a, b) (a &=~ b)
#define _SET_BIT(a, b) (a |= b)

// function prototypes
void stop_mode(int time);

// other functions
void enable_RTC_reg_access(void);
void disable_RTC_reg_access(void);
void config_EXTI(void);
int config_RTC(uint16_t time);
void config_stopmode(void);
void enter_stopmode(void);

void enable_RTC_reg_access(void)
{
    /* Enable write access for RTC registers - Reference Manual 27.7.9 (pg 672) */
    RTC->WPR = 0xCA; // - Reference Manual 27.4.7 (pg 649)
    RTC->WPR = 0x53; 
}

void disable_RTC_reg_access(void)
{
    /* Disable write access for RTC registers */
    RTC->WPR = 0xFE;  
    RTC->WPR = 0x64;  
}

void enable_reg_access(void)
{
    // Disable backup write protection. this bit must be set in order to enable RTC registers write access - Reference Manual 27.4.7 (pg 649)
    //PWR->CR |= PWR_CR_DBP; // - Reference Manual 27.4.7 (pg 649)
    _SET_BIT(PWR->CR, PWR_CR_DBP);
}

void config_EXTI(void)
{
    
        NVIC_EnableIRQ(RTC_IRQn); // Enable Interrupt on RTC
        NVIC_SetPriority(RTC_IRQn,0); // Set priority for RTC
        //EXTI->IMR |= EXTI_IMR_IM20; // Enable RTC alarm going through EXTI 20 line to NVIC
        _SET_BIT(EXTI->IMR, EXTI_IMR_IM20); // IMR = Interrupt Mask Register
        //EXTI->EMR |= EXTI_IMR_IM20;
        //EXTI->RTSR |= EXTI_IMR_IM20; // Select Rising Edge Trigger 
        _SET_BIT(EXTI->RTSR, EXTI_IMR_IM20); // Select Rising Edge Trigger (ligne 20 sensible à des fronts montants)
}

int config_RTC(uint16_t time)
{
    enable_reg_access();
    // RTC Reset - Reference Manual 7.3.21 (pg 219)
    //RCC->CSR |= RCC_CSR_RTCRST; 
    _SET_BIT(RCC->CSR, RCC_CSR_RTCRST);
    //RCC->CSR &=~ RCC_CSR_RTCRST; 
    _CLEAR_BIT(RCC->CSR, RCC_CSR_RTCRST);
    //enable_reg_access();
    
    // Reset and Clock Control
    //RCC->APB1ENR |= RCC_APB1ENR_PWREN; // Power interface clock enabled - Reference Manual 7.3.15 (pg 208)
    _SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    enable_reg_access();
    //RCC->CSR |= RCC_CSR_RTCSEL_LSE; // Select the RTC clock source: LSE oscillator (32768Hz) - Reference Manual 7.3.21 (pg 220)
    _SET_BIT(RCC->CSR, RCC_CSR_RTCSEL_LSE);
    //RCC->CSR |= RCC_CSR_LSEON; // Enable the external low-speed LSE oscillator - Reference Manual 7.3.21 (pg 220)
    _SET_BIT(RCC->CSR, RCC_CSR_LSEON);

    //enable_RTC_reg_access();
    /* Enable write access for RTC registers - Reference Manual 27.7.9 (pg 672) */
    RTC->WPR = 0xCA; // - Reference Manual 27.4.7 (pg 649)
    RTC->WPR = 0x53; 
    
    // RTC configuration
    ////Timer timeout; // <https://os.mbed.com/handbook/Timer>
    //uint32_t tickstart;
    //RTC->CR &=~ RTC_CR_WUTE; // Disable wake up timer to modify it - Reference Manual 27.4.7 (pg 650)
    _CLEAR_BIT(RTC->CR, RTC_CR_WUTE);
    //timeout.start();
    //tickstart = Tick;
    while((RTC->ISR & RTC_ISR_WUTWF) != RTC_ISR_WUTWF) { 
        // Wait until it is allowed to modify wake up reload value - Reference Manual 27.7.4 (pg 667)
        // LSE clock = 32768Hz -> 30,52us -> it takes up to 2RTCCLK = 61us to clear WUTWF after WUTE is cleared
        // If it takes more than 100 microseconds, return FALSE
        /*if(timeout.read_us() > 100) {
          if((Tick - tickstart) > 100) {
            //timeout.stop();
            return 0;
        }*/
    }
    //timeout.stop();
    
    RTC->WUTR = time-1; // Wake up value reload counter [s] - Reference Manual 27.7.6 (pg 669)
    RTC->PRER = 0x7F00FF; // ck_spre = 1Hz PREDIV_A = 0x7F(127) PREDIV_S = 0xFF(255) using LSE (32768Hz). ck = (32768)/(PREDIV_A * PREDIV_S)
    //RTC->CR |= RTC_CR_OSEL; // OSEL (output selection) = 0x3 -> RTC_ALARM output = Wake up timer - Reference Manual 27.7.3 (pg 662)
    _SET_BIT(RTC->CR, RTC_CR_OSEL);
    //RTC->CR |= RTC_CR_WUCKSEL_2; // WUCKSEL = 0x4 -> RTC Timer [1s - 18h] - Reference Manual 27.7.3 (pg 648, 664)
    _SET_BIT(RTC->CR, RTC_CR_WUCKSEL_2);
    //RTC->CR |= RTC_CR_WUTE | RTC_CR_WUTIE; // Enable wake up counter/interrupt - Reference Manual 27.7.3 (pg 650, 663, WUTIE 663)
    _SET_BIT(RTC->CR, RTC_CR_WUTE | RTC_CR_WUTIE);
    
    //disable_RTC_reg_access();
    /* Disable write access for RTC registers */
    RTC->WPR = 0xFE;  
    RTC->WPR = 0x64;  
        
//  RCC->CSR |= RCC_CSR_RTCEN; // Re-enable the RTC clock
    _SET_BIT(RCC->CSR, RCC_CSR_RTCEN);
    return 1; // Return TRUE
}

void config_stopmode(void)
{
//    uint32_t temp_reg = 0;
    
    // Clear the WUF flag - Reference Manual 6.4.1 (PG 168)
    _SET_BIT(PWR->CR, PWR_CR_CWUF);
    
    // disable DAC
    _CLEAR_BIT(DAC->CR, (DAC_CR_EN1 | DAC_CR_EN2));
    //DAC->CR &=~ DAC_CR_EN1 | DAC_CR_EN2;
    // disable ADC
    _CLEAR_BIT(ADC1->CR, ADC_CR_ADEN); // ADC->CR2, ADC_CR_ADON
    // select the regulator state in stop mode
//    temp_reg = PWR->CR;
    // PDDS = 0
    _CLEAR_BIT(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPSDSR)); // ENLEVER pour le mode standby
    
    // select MSI as wakeup from stop mode
    _CLEAR_BIT(RCC->CFGR, RCC_CFGR_STOPWUCK);
    
    // Set clear wake-up flag, low-power deepsleep run bit (regulator in low power mode)
    // and V_{REFINT}
    _SET_BIT(PWR->CR, (PWR_CR_CWUF | PWR_CR_LPSDSR | PWR_CR_ULP)); // stop
    //_SET_BIT(PWR->CR, (PWR_CR_CWUF | PWR_CR_LPSDSR)); // stop
    //_SET_BIT(PWR->CR, PWR_CR_CWUF | PWR_CR_PDDS | PWR_CR_ULP); // standby
    // store the new value
    //PWR->CR = temp_reg;
}

void enter_stopmode()
{
    // System control block
    _SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);
    //SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk; // Reenter low-power mode after ISR
    SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
} 

void stop_mode(int time)
{
    config_EXTI(); // configure the interruptions
    config_stopmode();
    config_RTC(time); // configure the RTC    
    enter_stopmode();
    __WFI();
}
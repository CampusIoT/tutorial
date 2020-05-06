#include "mbed.h"
//#include "stm32l073xx.h"

#define _CLEAR_BIT(a, b) (a &=~ b)
#define _SET_BIT(a, b) (a |= b)

// function prototypes
void sleep_mode(const uint16_t time); // time in second

// other functions
void enable_RTC_reg_access(void);
void disable_RTC_reg_access(void);
int config_RTC(int time);
void enable_bkp_access(void);
void config_Sleep(void);
void config_EXTI(void);
void enter_Sleep(void);
void verification_standby(void);
void _write_RTC_bkp_reg(void);
void config_GPIO(void);

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

int config_RTC(uint16_t time)
{    
    enable_bkp_access();
    // RTC Reset - Reference Manual 7.3.21 (pg 219)
    //RCC->CSR |= RCC_CSR_RTCRST; 
    _SET_BIT(RCC->CSR, RCC_CSR_RTCRST);
    //RCC->CSR &=~ RCC_CSR_RTCRST; 
    _CLEAR_BIT(RCC->CSR, RCC_CSR_RTCRST);
    
    // Reset and Clock Control
    //RCC->APB1ENR |= RCC_APB1ENR_PWREN; // Power interface clock enabled - Reference Manual 7.3.15 (pg 208)
    _SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    enable_bkp_access();
    //RCC->CSR |= RCC_CSR_RTCSEL_LSE; // Select the RTC clock source: LSE oscillator (32768Hz) - Reference Manual 7.3.21 (pg 220)
    _SET_BIT(RCC->CSR, RCC_CSR_RTCSEL_LSE);
    //RCC->CSR |= RCC_CSR_LSEON; // Enable the external low-speed LSE oscillator - Reference Manual 7.3.21 (pg 220)
    _SET_BIT(RCC->CSR, RCC_CSR_LSEON);

    enable_RTC_reg_access();
    /* Enable write access for RTC registers - Reference Manual 27.7.9 (pg 672) */
    //RTC->WPR = 0xCA; // - Reference Manual 27.4.7 (pg 649)
    //RTC->WPR = 0x53; 
    
    // RTC configuration
    //RTC->CR &=~ RTC_CR_WUTE; // Disable wake up timer to modify it - Reference Manual 27.4.7 (pg 650)
    _CLEAR_BIT(RTC->CR, RTC_CR_WUTE);
    while((RTC->ISR & RTC_ISR_WUTWF) != RTC_ISR_WUTWF) { 
        // Wait until it is allowed to modify wake up reload value - Reference Manual 27.7.4 (pg 667)
    }
    
    RTC->WUTR = time-1; // Wake up value reload counter [s] - Reference Manual 27.7.6 (pg 669)
    RTC->PRER = 0x7F00FF; // ck_spre = 1Hz PREDIV_A = 0x7F(127) PREDIV_S = 0xFF(255) using LSE (32768Hz). ck = (32768)/(PREDIV_A * PREDIV_S)
    //RTC->CR |= RTC_CR_OSEL; // OSEL (output selection) = 0x3 -> RTC_ALARM output = Wake up timer - Reference Manual 27.7.3 (pg 662)
    _SET_BIT(RTC->CR, RTC_CR_OSEL);
    //RTC->CR |= RTC_CR_WUCKSEL_2; // WUCKSEL = 0x4 -> RTC Timer [1s - 18h] - Reference Manual 27.7.3 (pg 648, 664)
    _SET_BIT(RTC->CR, RTC_CR_WUCKSEL_2);
    //RTC->CR |= RTC_CR_WUTE | RTC_CR_WUTIE; // Enable wake up counter/interrupt - Reference Manual 27.7.3 (pg 650, 663, WUTIE 663)
    _SET_BIT(RTC->CR, RTC_CR_WUTE | RTC_CR_WUTIE);
    
    disable_RTC_reg_access();
    /* Disable write access for RTC registers */
    //RTC->WPR = 0xFE;  
    //RTC->WPR = 0x64;  
        
//  RCC->CSR |= RCC_CSR_RTCEN; // Re-enable the RTC clock
    _SET_BIT(RCC->CSR, RCC_CSR_RTCEN);
    return 1; // Return TRUE
}

void enable_bkp_access(void)
{
    // Disable backup write protection. this bit must be set in order to enable RTC registers write access - Reference Manual 27.4.7 (pg 649)
    //PWR->CR |= PWR_CR_DBP; // - Reference Manual 27.4.7 (pg 649)
    _SET_BIT(PWR->CR, PWR_CR_DBP);
}

void config_Sleep(void)
{
                    
    // Power configuration  
    
    //PWR->CR |= PWR_CR_CWUF; // Clear the WUF flag - Reference Manual 6.4.1 (PG 168)
    _SET_BIT(PWR->CR, PWR_CR_CWUF);
    //PWR->CR |= PWR_CR_ULP; // V_{REFINT} (internal voltage reference for analog peripherals) is off in low-power mode - Reference Manual 6.2.4 (pg 151)
//    _SET_BIT(PWR->CR, PWR_CR_ULP);
    //PWR->CR |= PWR_CR_PDDS; // Enter Standby mode when the CPU enters deepsleep - Reference Manual 6.4.1 (PG 168)
    _CLEAR_BIT(PWR->CR, (PWR_CR_PDDS | PWR_CR_LPSDSR));
}

void config_EXTI(void)
{
    
        NVIC_EnableIRQ(RTC_IRQn); // Enable Interrupt on RTC
        NVIC_SetPriority(RTC_IRQn,0); // Set priority for RTC
        //EXTI->IMR |= EXTI_IMR_IM20; // Enable RTC alarm going through EXTI 20 line to NVIC
        _SET_BIT(EXTI->IMR, EXTI_IMR_IM20);
        //EXTI->EMR |= EXTI_IMR_IM20; IMR = Interrupt Mask Register
        //EXTI->RTSR |= EXTI_IMR_IM20; // Select Rising Edge Trigger 
        _SET_BIT(EXTI->RTSR, EXTI_IMR_IM20);
}

void enter_Sleep(void)
{
    
        // System Control Block
        //SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // Low power mode -> Deep Sleep
        _CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);
        //SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk; // Reenter low-power mode after ISR
        //_SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
        /**
          * @brief Indicates Sleep-On-Exit when returning from Handler mode to Thread mode. 
          * @note Set SLEEPONEXIT bit of SCR register. When this bit is set, the processor 
          *       re-enters SLEEP mode when an interruption handling is over.
          *       Setting this bit is useful when the processor is expected to run only on
          *       interruptions handling.
          */
}

void sleep_mode(uint16_t time){
        config_EXTI();
        config_GPIO();
        config_Sleep();
        config_RTC(time);
        enter_Sleep();
        __WFI(); // Waiting for Interruption -> Enter low-power mode
}

void config_GPIO(void)
{
    uint32_t temp, position;
    
    temp = GPIOA->MODER;
    // port A (reset state)
    for(position = 0; position < 16; position++) _SET_BIT(temp, (GPIO_MODER_MODE0 << (position * 2U)));
    GPIOA->MODER = temp;
    //_SET_BIT(GPIOA->MODER, 0xFCFFU); // Select Analog mode for all GPIOs
    //GPIOA->OSPEEDR = 0x0C000000; // All GPIOs set to low speed
    _CLEAR_BIT(GPIOA->PUPDR, 0xFFFFU); // All GPIOs set to no pull-up, pull-down
    _CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); // Disable the peripherical clock for GPIOA

    temp = GPIOB->MODER;
    // port B (reset state)
    for(position = 0; position < 16; position++) _SET_BIT(temp, (GPIO_MODER_MODE0 << (position * 2U)));
    GPIOB->MODER = temp;
    //_SET_BIT(GPIOB->MODER, 0xFFFFU); // Select Analog mode for all GPIOs
    //GPIOB->OSPEEDR = 0x00000000; // All GPIOs set to low speed
    _CLEAR_BIT(GPIOB->PUPDR, 0xFFFFU); // All GPIOs set to no pull-up, pull-down
    _CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN); // Disable the peripherical clock for GPIOB

    temp = GPIOC->MODER;
    // port C (reset state)
    for(position = 0; position < 16; position++) _SET_BIT(temp, (GPIO_MODER_MODE0 << (position * 2U)));
    GPIOC->MODER = temp;
    //_SET_BIT(GPIOC->MODER, 0xFFFFU); // Select Analog mode for all GPIOs
    //GPIOC->OSPEEDR = 0x00000000; // All GPIOs set to low speed
    _CLEAR_BIT(GPIOC->PUPDR, 0xFFFFU); // All GPIOs set to no pull-up, pull-down
    _CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN); // Disable the peripherical clock for GPIOC
}
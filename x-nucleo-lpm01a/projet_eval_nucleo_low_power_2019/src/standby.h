#include "mbed.h"
#include "stm32l073xx.h"

#define _CLEAR_BIT(a, b) (a &=~ b)
#define _SET_BIT(a, b) (a |= b)

#define BKP1    1
#define BKP2    2
#define BKP3    3
#define BKP4    4
#define BKP5    5

static uint32_t RTC_bkp_value[5];

// function prototypes
void standby_mode(uint16_t time); // time in second
uint32_t read_RTC_bkp_reg(uint32_t bkp_reg); // read the BKPx register
void write_RTC_bkp_reg(uint32_t bkp_reg, uint32_t value); // write to BKPx register
void reset_RTC_bkp_reg(void); // reset all the BKPx registers

// other functions
void debug_LPM(void);
void enable_RTC_bkp_reg(void);
void disable_RTC_protection_access(void);
void enable_RTC_protection_access(void);
int config_RTC(uint16_t time);
void enable_reg_access(void);
void disable_reg_access(void);
void config_Standby(void);
void config_EXTI(void);
void enter_Standby(void);
void verification_standby(void);
void _write_RTC_bkp_reg(void);
void config_GPIO(void);

void debug_LPM(void)
{ 
	
		//RCC->APB2ENR |= RCC_APB2ENR_DBGMCUEN; // To be able to debug in low power modes
		_SET_BIT(RCC->APB2ENR, RCC_APB2ENR_DBGMCUEN);
		//DBGMCU->CR |= DBGMCU_CR_DBG_SLEEP;  
		//DBGMCU->CR |= DBGMCU_CR_DBG_STOP; 
		//DBGMCU->CR |= DBGMCU_CR_DBG_STANDBY; // Debugger enable in standby mode
		_SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

void enable_RTC_bkp_reg(void)
{
	//RCC->APB1ENR |= RCC_APB1ENR_PWREN; // Power interface clock enabled - Reference Manual 7.3.15 (pg 208)
    _SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    enable_reg_access();
}

void disable_RTC_protection_access(void)
{
	/* Enable write access for RTC registers - Reference Manual 27.7.9 (pg 672) */
    RTC->WPR = 0xCA; // - Reference Manual 27.4.7 (pg 649)
    RTC->WPR = 0x53; 
}

void enable_RTC_protection_access(void)
{
	/* Disable write access for RTC registers */
    RTC->WPR = 0xFE;  
    RTC->WPR = 0x64;  
}

int config_RTC(uint16_t time)
{
	enable_reg_access();
	// RTC Reset - Reference Manual 7.3.21 (pg 219)
    //RCC->CSR |= RCC_CSR_RTCRST; 
    _SET_BIT(RCC->CSR, RCC_CSR_RTCRST);
    //RCC->CSR &=~ RCC_CSR_RTCRST; 
    _CLEAR_BIT(RCC->CSR, RCC_CSR_RTCRST);
    
    _write_RTC_bkp_reg();
	
	// Reset and Clock Control
    //RCC->APB1ENR |= RCC_APB1ENR_PWREN; // Power interface clock enabled - Reference Manual 7.3.15 (pg 208)
    _SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    enable_reg_access();
    //RCC->CSR |= RCC_CSR_RTCSEL_LSE; // Select the RTC clock source: LSE oscillator (32768Hz) - Reference Manual 7.3.21 (pg 220)
    _SET_BIT(RCC->CSR, RCC_CSR_RTCSEL_LSE);
	//RCC->CSR |= RCC_CSR_LSEON; // Enable the external low-speed LSE oscillator - Reference Manual 7.3.21 (pg 220)
	_SET_BIT(RCC->CSR, RCC_CSR_LSEON);

	disable_RTC_protection_access();
    /* Enable write access for RTC registers - Reference Manual 27.7.9 (pg 672) */
    //RTC->WPR = 0xCA; // - Reference Manual 27.4.7 (pg 649)
    //RTC->WPR = 0x53; 
	
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
	
	enable_RTC_protection_access();
	/* Disable write access for RTC registers */
    //RTC->WPR = 0xFE;  
    //RTC->WPR = 0x64;  
		
//	RCC->CSR |= RCC_CSR_RTCEN; // Re-enable the RTC clock
	_SET_BIT(RCC->CSR, RCC_CSR_RTCEN);
	disable_reg_access();
	return 1; // Return TRUE
}

void enable_reg_access(void)
{
	// Disable backup write protection. this bit must be set in order to enable RTC registers write access - Reference Manual 27.4.7 (pg 649)
    //PWR->CR |= PWR_CR_DBP; // - Reference Manual 27.4.7 (pg 649)
    _SET_BIT(PWR->CR, PWR_CR_DBP);
}

void disable_reg_access(void)
{
	// Disable backup write protection. this bit must be set in order to enable RTC registers write access - Reference Manual 27.4.7 (pg 649)
    //PWR->CR |= PWR_CR_DBP; // - Reference Manual 27.4.7 (pg 649)
    _CLEAR_BIT(PWR->CR, PWR_CR_DBP);
}

void config_Standby(void)
{
	    			
	// Power configuration  
    
    // Clear the WUF flag - Reference Manual 6.4.1 (PG 168)
    _SET_BIT(PWR->CR, PWR_CR_CWUF);
    // clear PWR Standby flag - Reference Manua 6.4.1 (PG 167)
    _SET_BIT(PWR->CR, PWR_CR_CSBF);
	//PWR->CR |= PWR_CR_FWU; // Enable Fast wake-up
    // V_{REFINT} (internal voltage reference for analog peripherals) is off in low-power mode - Reference Manual 6.2.4 (pg 151)
    _SET_BIT(PWR->CR, PWR_CR_ULP);
    // Enter Standby mode when the CPU enters deepsleep - Reference Manual 6.4.1 (PG 168)
    _SET_BIT(PWR->CR, PWR_CR_PDDS);
}

void config_EXTI(void)
{
	
	NVIC_EnableIRQ(RTC_IRQn); // Enable Interrupt on RTC
	NVIC_SetPriority(RTC_IRQn,0); // Set priority for RTC
	// Enable RTC alarm going through EXTI 20 line to NVIC
	_SET_BIT(EXTI->IMR, EXTI_IMR_IM20);
	// Select Rising Edge Trigger 
	_SET_BIT(EXTI->RTSR, EXTI_IMR_IM20);
}

void enter_Standby(void)
{

	// System Control Block
	//SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // Low power mode -> Deep Sleep
	_SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);
	//SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk; // Reenter low-power mode after ISR
	_SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
	/**
	  * @brief Indicates Sleep-On-Exit when returning from Handler mode to Thread mode. 
	  * @note Set SLEEPONEXIT bit of SCR register. When this bit is set, the processor 
	  *       re-enters SLEEP mode when an interruption handling is over.
	  *       Setting this bit is useful when the processor is expected to run only on
	  *       interruptions handling.
	  */
}

void standby_mode(uint16_t time){
	config_GPIO();
	config_Standby();
	config_RTC(time);
	enter_Standby();
	__WFI(); // Waiting for Interruption -> Enter low-power mode
}

void verification_standby(void)
{
	// check standby flag
    // Reference Manual 6.3.10 <<Exiting Standby Mode>> (PG 162) &
    // Reference Manual 6.4.2(PG 170)
    if((PWR->CSR)&(PWR_CSR_SBF)) {
        // clear PWR Wake Up flag - Reference Manua 6.4.1 (PG 168)
        //PWR->CR |= PWR_CR_CWUF;
        _SET_BIT(PWR->CR, PWR_CR_CWUF);
        // clear PWR Standby flag - Reference Manua 6.4.1 (PG 167)
        //PWR->CR |= PWR_CR_CSBF;
        _SET_BIT(PWR->CR, PWR_CR_CSBF);
        
        printf("\nLa carte se reveille du mode standby\n");
    }
    else {
        printf("\nLa carte se reveille du power cycle\n");
    }
}

uint32_t read_RTC_bkp_reg(uint32_t bkp_reg)
{
	// RTC_BKPxR, x = 0 - 4
	
	uint32_t bkp_val = 0;
	
	// Reset and Clock Control
    //RCC->APB1ENR |= RCC_APB1ENR_PWREN; // Power interface clock enabled - Reference Manual 7.3.15 (pg 208)
    _SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    //RCC->CSR |= RCC_CSR_RTCSEL_LSE; // Select the RTC clock source: LSE oscillator (32768Hz) - Reference Manual 7.3.21 (pg 220)
    _SET_BIT(RCC->CSR, RCC_CSR_RTCSEL_LSE);
	//RCC->CSR |= RCC_CSR_LSEON; // Enable the external low-speed LSE oscillator - Reference Manual 7.3.21 (pg 220)
	_SET_BIT(RCC->CSR, RCC_CSR_LSEON);
	
	disable_RTC_protection_access();
	
	switch(bkp_reg)
	{
		case 1:
			bkp_val = RTC->BKP0R;
			break;
		case 2:
			bkp_val = RTC->BKP1R;
			break;
		case 3:
			bkp_val = RTC->BKP2R;
			break;
		case 4:
			bkp_val = RTC->BKP3R;
			break;
		case 5:
			bkp_val = RTC->BKP4R;
			break;
		default:
			bkp_val = RTC->BKP0R;
			break;
	}
	
	enable_RTC_protection_access();
	disable_reg_access();
	return bkp_val;
	
	//enable_RTC_reg_access();
	//disable_RTC_reg_access();
}

void write_RTC_bkp_reg(uint32_t bkp_reg, uint32_t value)
{
	RTC_bkp_value[bkp_reg - 1] = value;
}

void reset_RTC_bkp_reg(void)
{
	for(int i = 0; i < 5; i++)
		RTC_bkp_value[i] = 0;
}

void _write_RTC_bkp_reg(void)
{
	// Reset and Clock Control
    //RCC->APB1ENR |= RCC_APB1ENR_PWREN; // Power interface clock enabled - Reference Manual 7.3.15 (pg 208)
    _SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    enable_reg_access();
    //RCC->CSR |= RCC_CSR_RTCSEL_LSE; // Select the RTC clock source: LSE oscillator (32768Hz) - Reference Manual 7.3.21 (pg 220)
    _SET_BIT(RCC->CSR, RCC_CSR_RTCSEL_LSE);
	//RCC->CSR |= RCC_CSR_LSEON; // Enable the external low-speed LSE oscillator - Reference Manual 7.3.21 (pg 220)
	_SET_BIT(RCC->CSR, RCC_CSR_LSEON);
	
	disable_RTC_protection_access();
	
	RTC->BKP0R = RTC_bkp_value[0];
	RTC->BKP1R = RTC_bkp_value[1];
	RTC->BKP2R = RTC_bkp_value[2];
	RTC->BKP3R = RTC_bkp_value[3];
	RTC->BKP4R = RTC_bkp_value[4];
	
	enable_RTC_protection_access();
	disable_reg_access();
}

void config_GPIO(void)
{
	uint32_t temp, position;
	
	temp = GPIOA->MODER;
	// port A (reset state)
	_SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); // Disable the peripherical clock for GPIOA
	for(position = 0; position < 16; position++) _SET_BIT(temp, (GPIO_MODER_MODE0 << (position * 2U)));
	GPIOA->MODER = temp;
	_CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN); // Disable the peripherical clock for GPIOA
	//_SET_BIT(GPIOA->MODER, 0xFCFFU); // Select Analog mode for all GPIOs
	//GPIOA->OSPEEDR = 0x0C000000; // All GPIOs set to low speed
	//_CLEAR_BIT(GPIOA->PUPDR, 0xFFFFU); // All GPIOs set to no pull-up, pull-down

	temp = GPIOB->MODER;
	// port B (reset state)
	_SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN); // Disable the peripherical clock for GPIOB
	for(position = 0; position < 16; position++) _SET_BIT(temp, (GPIO_MODER_MODE0 << (position * 2U)));
	GPIOB->MODER = temp;
	_CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN); // Disable the peripherical clock for GPIOB
	//_SET_BIT(GPIOB->MODER, 0xFFFFU); // Select Analog mode for all GPIOs
	//GPIOB->OSPEEDR = 0x00000000; // All GPIOs set to low speed
	//_CLEAR_BIT(GPIOB->PUPDR, 0xFFFFU); // All GPIOs set to no pull-up, pull-down

	temp = GPIOC->MODER;
	// port C (reset state)
	_SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN); // Disable the peripherical clock for GPIOC
	for(position = 0; position < 16; position++) _SET_BIT(temp, (GPIO_MODER_MODE0 << (position * 2U)));
	GPIOC->MODER = temp;
	_CLEAR_BIT(RCC->IOPENR, RCC_IOPENR_GPIOCEN); // Disable the peripherical clock for GPIOC
	//_SET_BIT(GPIOC->MODER, 0xFFFFU); // Select Analog mode for all GPIOs
	//GPIOC->OSPEEDR = 0x00000000; // All GPIOs set to low speed
	//_CLEAR_BIT(GPIOC->PUPDR, 0xFFFFU); // All GPIOs set to no pull-up, pull-down
}
#ifndef _STOP_H
#define _STOP_H

#define _CLEAR_BIT(a, b) (a &=~ b)
#define _SET_BIT(a, b) (a |= b)

// Includes
//#include "mbed.h"
//#include "stm32l073xx.h"

// Prototypes
void enable_RTC_reg_access(void);
void disable_RTC_reg_access(void);
void config_EXTI(void);
int config_RTC(uint16_t time);
void config_stopmode(void);
void enter_stopmode(void);
void stop_mode(int time);

   

#endif
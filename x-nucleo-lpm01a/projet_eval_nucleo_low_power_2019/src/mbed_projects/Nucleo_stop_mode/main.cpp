#include "mbed.h"
#include "stop.h"

DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);

int main(void)
{
    config_EXTI();
    config_RTC(5);
    while(1)
    {
        
        pc.printf("Entrer dans le stop mode\n");
        stop_mode(5); // go to sleep for 10 seconds
        pc.printf("Sortir du mode\n");
        myled = 1; // LED is ON
        wait(0.2); // 200 ms
        myled = 0; // LED is OFF
        _SET_BIT(PWR->CR, PWR_CR_CWUF); // clear wakeup flag
    }
}

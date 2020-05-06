#include "mbed.h"
#include "sleep.h"
#include "stop.h"

DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);

int main() {
    while(1) {
        myled = 1; // LED is ON
        wait(0.2); // 200 ms
        myled = 0; // LED is OFF

        pc.printf("La carte entre dans le mode low-power\n");
	stop_mode(10); // go to sleep for 10 sec in stop mode
//        sleep_mode(10); // go to sleep for 10 sec in sleep mode
        pc.printf("La carte sort du mode low-power\n");
    }
}

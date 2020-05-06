#include "mbed.h"
#include "sleep.h"

DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);

int main() {
    while(1) {
        myled = 1; // LED is ON
        wait(0.2); // 200 ms
        myled = 0; // LED is OFF
        //wait(1.0); // 1 sec
        pc.printf("La carte entre dans le mode sleep\n");
        sleep_mode(5);
        pc.printf("La carte sort du mode sleep\n");
    }
}

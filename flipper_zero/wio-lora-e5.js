/*
 * Simple LoRaWAN sender with WIo LoRa E5 for Flipper Zero
 * Copyright : 2024, Université Grenoble Alpes
 * Author : Didier DONSEZ
 */ 

// JS API https://developer.flipper.net/flipperzero/doxygen/js_serial.html

let APPKEY = "1234567890ABCDEF1234567890ABCDEF";

let serial = require("serial");
serial.setup("usart", 9600);


function receive(nb_line, timeout) {
    let line;
    for(let i=0; i<nb_line; i++) {
        line = serial.readln(timeout);
        if(line) {
            print(line);
        }
    }
}

function send(cmdline, nb_line, timeout) {
    print(cmdline); // for debug
    serial.write(cmdline, [0x0d, 0x0a]);
    receive(nb_line, timeout);
}

print("-------------------"); // for debug
print("Flipper LoRaWAN FTD"); // for debug
print("-------------------"); // for debug
delay(5000); // one second for debug

send("AT+ID", 5, 1000);
delay(1000); // one second for debug

send("AT+MODE=LWOTAA", 3, 1000);
delay(1000); // one second for debug

send("AT+DR", 4, 1000);
delay(1000); // one second for debug

send("AT+DR=5", 4, 1000);
delay(1000); // one second for debug

send("AT+POWER=14", 4, 1000); // Change LoRaWAN AT module TX power to 14 dBm
delay(1000); // one second for debug

send("AT+ADR=ON", 4, 1000);
delay(1000); // one second for debug

send("AT+CLASS=A", 4, 1000);
delay(1000); // one second for debug

send("AT+KEY=APPKEY,"+APPKEY, 2, 1000);
delay(1000); // one second for debug

// TODO loop on JOIN if OTAA join procedure failed

send("AT+JOIN", 7, 10000);
delay(1000); // one second for debug

delay(10000); // one minute for duty cycle

send("AT+PORT=10", 2, 1000);
delay(1000); // one second for debug

// TODO loop on CMSG

send("AT+CMSG=HELLO", 9, 1000);

receive(10, 10000)

send("AT+CMSG=HELLO", 9, 1000);

receive(10, 10000)


// More AT Commands in https://github.com/CampusIoT/tutorial/blob/master/wio-lora-e5/AT.md
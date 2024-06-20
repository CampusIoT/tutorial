/*
 * Simple LoRaWAN Field Test Device with WIo LoRa E5 for Flipper Zero
 * Copyright : 2024, Université Grenoble Alpes
 * Author : Didier DONSEZ
 */ 

// JS API https://developer.flipper.net/flipperzero/doxygen/js_serial.html
// https://github.com/cesanta/mjs/blob/master/README.md

let APPKEY = "1234567890ABCDEF1234567890ABCDEF";
let PORT = 10;

let serial = require("serial");
serial.setup("usart", 9600);


function receive(nb_line, timeout, sentence) {
    let res  = false;
    let line;
    for(let i=0; i<nb_line; i++) {
        line = serial.readln(timeout);
        if(line) {
            console.log(line);
            if(sentence && line.indexOf(sentence) >= 0){
                res = true;
            }
        }
    }
    return res;
}

function send(cmdline, nb_line, timeout, sentence) {
    print(cmdline); // for debug
    //console.log(cmdline); // for debug
    serial.write(cmdline, [0x0d, 0x0a]);
    return receive(nb_line, timeout, sentence);
}

print("-------------------"); // for debug
print("Flipper LoRaWAN FTD"); // for debug
print("-------------------"); // for debug
delay(2000); // one second for debug

send("AT+ID", 5, 1000);
delay(1000); // one second for debug

send("AT+MODE=LWOTAA", 3, 1000);
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

// loop on JOIN if OTAA join procedure failed
let joined = false;
while(!joined) {
    joined = send("AT+JOIN", 7, 10000, "+JOIN: Network joined");
    delay(1000); // one second for debug
    if(!joined) {
        print("Join failed : retry later !");
        // retry until joined
        delay(10000); // 10 sec for duty cycle
    } else {
        print("Network joined");
    }
}

delay(10000); // one minute for duty cycle

send("AT+PORT="+to_string(PORT), 2, 1000);
delay(1000); // one second for debug

// loop on CMSG
let cpt = 1;
while(true) {
    print("Msg #"+to_string(cpt)); // for debug
    send("AT+CMSG=FTD_"+to_string(cpt), 9, 1000);
    // TODO check if the message has been succesfully sent
    // TODO print Downlink message
    // TODO retry immediatly when lower DR and higher TxPower if unconfirmed
    cpt++;

    // TODO change TxPower and Data in unconfirmed
    // Encode into payload : TxPower, Last Downlink FCnt, RSSI and SNR

    receive(10, 10000)    
}

// More AT Commands in https://github.com/CampusIoT/tutorial/blob/master/wio-lora-e5/AT.md
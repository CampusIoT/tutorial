/*
 * Simple LoRaWAN Field Test Device with Seeedstudio Wio Grove E5 for Flipper Zero
 * Copyright : 2024, Université Grenoble Alpes
 * Author : Didier DONSEZ
 */ 

/*
* References
* https://wiki.seeedstudio.com/Grove_LoRa_E5_New_Version/
* JS API https://developer.flipper.net/flipperzero/doxygen/js_serial.html
* https://github.com/cesanta/mjs/blob/master/README.md
*/

/*
Pinout: Grove cable on Flipper GPIO
* `Red` on `3V3` (9)
* `Black` on `GND` (11)
* `White` on `TX` (13)
* `Yellow` on `RX` (14)

Set baudrate at 9600
*/

let notify = require("notification");

let APPKEY = "1234567890ABCDEF1234567890ABCDEF";
let PORT = 10;

let serial = require("serial");
serial.setup("usart", 9600);


function receive(nb_line, timeout, sentence) {
    let line;
    let res;
    for(let i=0; i<nb_line; i++) {
        line = serial.readln(timeout);
        if(line) {
            console.log(line);
            if(sentence && line.indexOf(sentence) >= 0){
                res = line;
            }
        }
    }
    return res;
}

function send(cmdline, nb_line, timeout, sentence) {
    print(cmdline);
    console.log(cmdline); // for debug
    serial.write(cmdline, [0x0d, 0x0a]);
    return receive(nb_line, timeout, sentence);
}

function dec_dr(){
    serial.write("AT+DR", [0x0d, 0x0a]);
    let l = receive(4, 1000, "+DR: DR");
    if(l) {
        let dr = l.at(7) - 48; // '0' is 0x30 or 48
        if(dr>0) {
            dr--;
        }
        serial.write("AT+DR="+to_string(dr), [0x0d, 0x0a]);
        receive(4, 1000, "+DR: DR");
        print("DR="+to_string(dr));
        return dr;
    }
    return undefined;
}


print("-------------------"); // for debug
print("Flipper LoRaWAN FTD"); // for debug
print("-------------------"); // for debug
delay(2000); // one second for debug

let line;

line = send("AT+ID", 5, 500, "DevEui");
print(line);
delay(1000); // one second for debug

send("AT+MODE=LWOTAA", 3, 500);
delay(1000); // one second for debug

send("AT+DR=5", 4, 500);
delay(1000); // one second for debug

send("AT+POWER=14", 4, 500); // Change LoRaWAN AT module TX power to 14 dBm
delay(1000); // one second for debug

send("AT+ADR=ON", 4, 500);
delay(1000); // one second for debug

send("AT+CLASS=A", 4, 500);
delay(1000); // one second for debug

send("AT+KEY=APPKEY,"+APPKEY, 2, 500);
delay(1000); // one second for debug

// loop on JOIN if OTAA join procedure failed
let joined = false;
while(!joined) {
    let line = send("AT+JOIN", 7, 10000, "+JOIN: Network joined");
    if(line) {
        joined = true;
    }
    if(!joined) {
        print("Join failed: retry later!");
        notify.error();
        // retry until joined
        // TODO increment TxPower and decrement DR.
        dec_dr();
        delay(10000); // 10 sec for duty cycle
    } else {
        print("Network joined");
        notify.success();
    }
}

delay(10000); // one minute for duty cycle

send("AT+PORT="+to_string(PORT), 2, 1000);
delay(1000); // one second for debug

// loop on CMSG
let cpt = 1;
while(true) {
    print("Msg #"+to_string(cpt)); // for debug

    let dr_line = send("AT+DR", 5, 1000, "+DR: DR");
    print(dr_line);

    let rssi = send("AT+CMSG=FTD_"+to_string(cpt), 10, 1000, "RSSI");
    // TODO check if the message has been succesfully sent
    // TODO print downlink message
    // TODO retry immediatly when lower DR and higher TxPower if unconfirmed
    console.log(rssi);
    if(rssi) {
        // TODO parse RSSI and SNR and get DN FCnt
        print("DN Cnf "+rssi);
        notify.success();
    } else {
        print("DN Cnf not received");
        dec_dr();
    }
    cpt++;

    // TODO change TxPower and Data in unconfirmed
    // Encode into payload : TxPower, Last Downlink FCnt, RSSI and SNR

    receive(10, 10000)    
}

// More AT Commands in https://github.com/CampusIoT/tutorial/blob/master/wio-lora-e5/AT.md
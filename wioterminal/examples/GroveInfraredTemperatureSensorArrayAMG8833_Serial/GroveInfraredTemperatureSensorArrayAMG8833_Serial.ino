/*
    basic_demo.ino
    Driver for DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR

    Copyright (c) 2018 Seeed Technology Co., Ltd.
    Website    : www.seeed.cc
    Author     : downey
    Create Time: May 2018
    Change Log :

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/
#include "Seeed_AMG8833_driver.h"


AMG8833 sensor;



void parse_int_status(u8* status) {
    u8 val = 0;
    for (u32 i = 0; i < 8; i++) {
        if (status[i]) {
            for (u32 j = 0; j < 8; j++) {
                if (status[i] & ((1 << j))) {
                    Serial.print("pixel ");
                    Serial.print(8 * i + j + 1);
                    Serial.println("interrupt is generated!!!");
                }
            }
        }
    }
}

void print_status(u8* status) {
    Serial.print("interrupt status value are::");
    for (u32 i = 0; i < 8; i++) {

        Serial.print(status[i], HEX);
        Serial.print("  ");

    }
    Serial.println("  ");
}




void setup() {
    Serial.begin(115200);
    if (sensor.init()) {
        Serial.println("init failed!!!");
        while (1);
    }
    Serial.println("AMG8833 init OK!!!");
}



void loop() {
    u8 val = 0;
    float pixels_temp[PIXEL_NUM] = {0};
    u8 int_status[8] = {0};

    /*Read temp*/
    sensor.read_pixel_temperature(pixels_temp);
    /*Print 8X8 pixels value.*/
    Serial.println("Temperature for 8X8 matrix are::");
    for (int i = 0; i < PIXEL_NUM; i++) {
        Serial.print(pixels_temp[i]);
        Serial.print("  ");
        if (0 == (i + 1) % 8) {
            Serial.println(" ");
        }
    }

    /*  Get interrupt status for every channel and print out.
    **NODE!!:Interrupt Table is renewed in timing with when output data is renewed.This indicate that when you read the interrupt status
    **register for every channel Periodically.The results of interrupt status register are not the moment you were reading,But the sum of the
        interruptions generated during the entire cycle.
    **/
    if (sensor.get_interrupt_status()) {
        //sensor.reset_flags(FLAG_RESET_VALUE);
        sensor.read_pixels_interrupt_status(int_status);
        print_status(int_status);
        parse_int_status(int_status);
        //sensor.clear_status(0x2);
        sensor.reset_flags(FLAG_RESET_VALUE);

    }
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
    delay(1000);
}

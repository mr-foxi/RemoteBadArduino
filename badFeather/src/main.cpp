#include <Arduino.h>
#include <oled.h>
#include <oledPages.h>
#include <oledPinMode.h>
#include <serials.h>
#include <wifi.h>
#include <blue.h>

const int RX_PIN = 16;
const int TX_PIN = 17;
const int POLL_TIME = 200;

void setup() {
    #ifdef OLED_H
        oled.init();
        delay(3000); //  DO NOT TOUCH
        oled.clear(); //  DO NOT TOUCH
        oled.clear(); //  DO NOT TOUCH
    #endif
    #ifdef SERIALS_H
        serials.usbInit();
        serials.pinInit();
    #endif
    oled.printlnString("!!  FoxDev BADUSB  !!");


    // wifi.apStart();
    // wifi.up();
    // wifi.RSSI();
    // wifi.httpRequest();
    // delay(3000);
    // blue.up();
    // delay(3000);
    // blue.poll();
    // delay(2000);
    // blue.poll();
    // delay(2000);
    // oled.clear();
    // oled.printlnString("foxTest Procedure");
    // oled.printlnString("Complete...");
}

void loop () {
    // String pinResponse = serials.pinRead();
    // serials.checkResponse(pinResponse);

    // wifi.apRecieve();
    // wifi.sendMessage();
    
    // oledPinMode.02();
    delay(POLL_TIME);
}
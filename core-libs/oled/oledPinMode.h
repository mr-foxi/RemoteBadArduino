#ifdef OLED_h
#ifndef OLEDPINMODE_H
#define OLEDPINMODE_H

#include <oled.h>
#include <wifi.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <serials.h>
#include <wifi.h>
// #include <blue.h>

class OLEDPINMODE
{
public:
    OLEDPINMODE();
    void example();
    void mode00();
    void mode01();
    void mode02();
};

extern OLEDPINMODE oledPinMode;

#endif
#endif
#ifdef USING_SD
#ifndef SDBCARD_H
#define SDCARD_H
#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

extern const int pinSD;

class SDCARD
{
public:
    SDCARD();
    void init();
    void up();
    void down();
    String getPayload(String payloadName);
    void copy();
};

extern SDCARD sd;

#endif
#endif
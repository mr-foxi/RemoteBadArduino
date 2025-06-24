#ifndef SERIALS_H
#define SERIALS_H

#include <Arduino.h>
#include <HardwareSerial.h> // For Arduino framework

extern const int RX_PIN; // For WiPy3 Tthis is GPIO 26, which is P21 in silk screen
extern const int TX_PIN; // For WiPy3 Tthis is GPIO 22, which is P11 in silk screen
extern const int SERIALS_BAUD;

enum ResponseCode {
  #ifdef DEBUG_SERIAL
  RESPONSE_ERROR222,
  #endif
  RESPONSE_UNKNOWN,
  // RESPONSE_HELLO,
  RESPONSE_EMPTY,
  RESPONSE_ROGER,
  RESPONSE_ERROR404,
  RESPONSE_ERROR,
// Bad Arduino
  RESPONSE_SDCARD,
  RESPONSE_PULLSCRIPT,
  RESPONSE_PULLSCRIPTEXIT
};

class SERIALS
{
public:
    SERIALS();
// Bad Pycom & Feather (ESP32)
    void usbInit();
    void pinInit();
    String pinRead();
    void print(String);
    void checkResponse(String);
    void sdPayload();
    void pullScript();
    void pullScriptExit();

// Bad Arduino
    void upUsb();
    void up1();
    void up2();
    void up3();
    String read1();
    // void print(String);
    // void checkResponse(String);
};

extern SERIALS serials;

#endif
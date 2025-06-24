#include <serials.h>
#include <payloadsList.h>
#include <key.h>
#include <sd.h>
#include <sdPayloads.h>
// #ifdef OLED_h
// #include <oled.h> THINK I WANT TO REMOVE OLED COMMANDS FROM HERE, AND HAVE THEM WHERE FUNCTIONS CALLED
// #endif

extern const int RX_PIN; // For WiPy3 This is GPIO 26, which is P21 in silk screen
extern const int TX_PIN; // For WiPy3 This is GPIO 22, which is P11 in silk screen
extern const int SERIALS_BAUD = 115200;

#ifdef HW_ESP
HardwareSerial pinSerial(1); // Use UART1 (you can pick another depending on your setup) Pycom
#endif
#ifdef HW_ARDUINO
void SERIALS::upUsb() {Serial.begin(SERIALS_BAUD);} // USB Serial for Arduino Due
void SERIALS::up1() {Serial1.begin(SERIALS_BAUD);} // Pin 18 (TX1) & Pin 19 (RX1) for Arduino Due
// void SERIALS::up2() {Serial2.begin(SERIALS_BAUD);} // Pin 16 (TX2) & Pin 17 (RX2) for Arduino Due
// void SERIALS::up3() {Serial3.begin(SERIALS_BAUD);} // Pin 14 (TX3) & Pin 15 (RX3) for Arduino Due
#endif

void sendSerial(String command) {
    #ifdef HW_ESP
    pinSerial.println(command);
    #endif
    #ifdef HW_ARDUINO
    Serial1.println(command);
    #endif
}

SERIALS::SERIALS() {}

void SERIALS::usbInit() {
    Serial.begin(SERIALS_BAUD);
    Serial.println("Hello USB Serial World!");
}
#ifdef HW_ESP
void SERIALS::pinInit() {
    pinSerial.begin(SERIALS_BAUD, SERIAL_8N1, RX_PIN, TX_PIN);
}
String SERIALS::pinRead() {
    if (pinSerial.available()) {
        String msg = pinSerial.readStringUntil('\n');
        msg.trim();
        return msg;
    } else {
        return "";
    //     return "!ERROR: 222!"; GOOD DEBUG LINE
    }
}
#endif
void SERIALS::sdPayload() {
    Serial.println();
    Serial.println("Sending Command: sdPayload");
    // oled.clear();
    // oled.printlnString("Sending Command:");
    // oled.printlnString("sdPayload");
    sendSerial(payloadsList.CONST_SDCARD);
}
void SERIALS::pullScript() {
    Serial.println();
    Serial.println("Sending Command: pullScript");
    // oled.clear();
    // oled.printlnString("Sending Command:");
    // oled.printlnString("pullScript");
    sendSerial(payloadsList.CONST_PULLSCRIPT);
}
void SERIALS::pullScriptExit() {
    Serial.println();
    Serial.println("Sending Command: pullScript");
    // oled.clear();
    // oled.printlnString("Sending Command:");
    // oled.printlnString("pullScript");
    sendSerial(payloadsList.CONST_PULLSCRIPTEXIT);
}

#ifdef HW_ARDUINO
String SERIALS::read1() {
    if (Serial1.available()) {
        String msg = Serial1.readStringUntil('\n');
        msg.trim();
        return msg;
    } else {
        #ifdef DEBUG_SERIALS
        return "!ERROR: 222!"; GOOD DEBUG LINE
        #endif
        return "";
    }
}
#endif

ResponseCode parseResponse(String response) {
  response.trim();
  if (response == "") return RESPONSE_EMPTY;
  if (response == "Error") return RESPONSE_ERROR;
  if (response == "!ERROR: 404!") return RESPONSE_ERROR404;
//   if (response == "!ERROR: 222!") return RESPONSE_ERROR222; GOOD DEBUG LINE
  if (response == "#Roger Roger#") return RESPONSE_ROGER;
  return RESPONSE_UNKNOWN;
}
void SERIALS::checkResponse(String response) {
    switch(parseResponse(response)) {
        case RESPONSE_EMPTY:
            #ifdef DEBUG_SERIALS
            Serial.println("No Response Yet..."); GOOD DEBUG LINE
            #endif
            break;
        #ifdef DEBUG_SERIALS
        case RESPONSE_ERROR222:
            Serial.println("!Error: 222! - Serial Pin Not Available"); GOOD DEBUG LINE
            break;
        #endif
        case RESPONSE_ERROR:
            Serial.println("Response Error");
            break;
        case RESPONSE_ERROR404:
            Serial.println("!Error: 404! - Error Not Found");
            break;
        case RESPONSE_UNKNOWN:
            Serial.print("Unknown Response: ");
            Serial.println(response);
            break;
// Bad Pycom and Feather
        case RESPONSE_ROGER:
            Serial.println("Roger Roger!");
            // oled.clear(); // How isolate?
            // oled.printlnString("Roger Roger!"); // How isolate?
            // delay(3000); // How isolate?
            // oled.clear(); // How isolate?
            // oled.printlnString("!!  FoxDev BADUSB  !!"); // How isolate?
            break;
// Bad Arduino 
#ifdef HW_ARDUINO
        case RESPONSE_SDCARD: 
            Serial.println();
            Serial.print("Roger Roger: ");
            Serial.println(response);
            sdPayloads.usePayload(sd.getPayload(payloadsList.CONST_SD_FILE));
            sendSerial("#Roger Roger#");
            break;
        case RESPONSE_PULLSCRIPT:
            Serial.println();
            Serial.print("Roger Roger: ");
            Serial.println(response);
            key.pullScript();
            sendSerial("#Roger Roger#");
            break;
        case RESPONSE_PULLSCRIPTEXIT:
            Serial.println();
            Serial.print("Roger Roger: ");
            Serial.println(response);
            key.pullScriptExit();
            sendSerial("#Roger Roger#");
            break;
#endif
    }
}
SERIALS serials = SERIALS();
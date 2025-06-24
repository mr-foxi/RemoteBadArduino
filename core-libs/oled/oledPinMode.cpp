#ifdef OLED_h
#include <oledPinMode.h>

OLEDPINMODE::OLEDPINMODE() {}

void OLEDPINMODE::example() {
    if(!digitalRead(BUTTON_A)) display.print("A");
    if(!digitalRead(BUTTON_B)) display.print("B");
    if(!digitalRead(BUTTON_C)) display.print("C");
    delay(10);
    yield();
    display.display();
}
void OLEDPINMODE::mode00() {
    if(!digitalRead(BUTTON_A)) serials.sdPayload();
    if(!digitalRead(BUTTON_B)) serials.pullScript();
    if(!digitalRead(BUTTON_C)) wifi.sdPayload();
}
void OLEDPINMODE::mode01() {
    if(!digitalRead(BUTTON_A)) wifi.sdPayload();
    if(!digitalRead(BUTTON_B)) wifi.pullScript();
    if(!digitalRead(BUTTON_C)) serials.sdPayload();
}
void OLEDPINMODE::mode02() {
    if(!digitalRead(BUTTON_A)) wifi.sdPayload();
    if(!digitalRead(BUTTON_B)) wifi.pullScript();
    if(!digitalRead(BUTTON_C)) wifi.pullScriptExit();
}

OLEDPINMODE oledPinMode = OLEDPINMODE();

#endif
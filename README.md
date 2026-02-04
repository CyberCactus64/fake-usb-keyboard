# ESP32 USB HID Fake Keyboard

This project uses an ESP32 microcontroller with native USB support to emulate a USB HID keyboard.
It is designed exclusively as a demonstration tool for corporate security awareness, penetration testing, training sessions, or controlled simulations related to the risks of untrusted USB devices.

---

## Project purpose

The goal of this project is to demonstrate how an apparently harmless USB device can behave as a keyboard and inject keystrokes into a computer, in order to:
 - Raise awareness about the risks of unknown or untrusted USB devices
 - Test security policies and incident response procedures

This project is **not intended for real-world offensive use** or for production environments.

---

## Hardware compatibility
This project is compatible **only with ESP32 microcontrollers that provide native USB support**.  

### Supported ESP32 families
- ESP32-S2  
  - ESP32-S2 Dev Module  
  - ESP32-S2 Saola  
- ESP32-S3  
  - ESP32-S3 Dev Module  
  - ESP32-S3 DevKitC-1  
  - ESP32-S3 DevKitM-1  
  - Other ESP32-S3 boards with exposed USB-OTG interface
#### Standard ESP32 boards (ESP32, ESP32-WROOM, ESP32-WROVER, etc.) **are not supported**.

### Supported Arduino families (native USB)
- ATmega32U4  
  - Arduino Leonardo  
  - Arduino Micro  
  - Arduino Pro Micro (and compatibles)  
- SAMD21 / SAMD51  
  - Arduino Zero  
  - Arduino MKR family (MKR Zero, MKR WiFi 1010, etc.)  
  - Arduino Nano 33 IoT  
  - Arduino Nano 33 BLE / BLE Sense  
- Other official boards  
  - Arduino Due (native USB port)  
#### Standard Arduino boards without native USB (Uno, Mega, Nano classic, etc.) **are not supported**.

### Other microcontrollers I tested:
- Particle Photon

---

## Keyboard layout compatibility

The project supports **multiple keyboard layouts**, configurable in the source code, including:
- US English
- Italian
- French
- German
- Additional layouts can be added with minimal changes

The selected layout **must match the operating system keyboard layout** on the host machine to avoid incorrect character mapping.

---

## Software requirements

- Arduino IDE or PlatformIO
- Esp32

---

## Disclaimer

This project must be used **only in controlled environments** and on systems for which explicit authorization has been granted.
It is the responsibility of the user to ensure that usage complies with internal company policies, local laws, and applicable regulations.

This repository is provided **for educational and demonstration purposes only**.

The author(s) and the organization:
- assume no responsibility for improper, illegal, or unauthorized use of this code
- disclaim any liability for direct or indirect damages resulting from the use of this project
- do not encourage or support attacks, intrusions, or system compromise

By using this code, you acknowledge that you do so **at your own risk and responsibility**.

---

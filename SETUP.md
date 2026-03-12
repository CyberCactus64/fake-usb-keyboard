
# HOW TO SETUP

## Command and Control server
 - Name your malicious payload "utility.exe" and place it at `/var/www/html/utility.exe`
 - Setup the C2 server with the given ServerSetup.sh (in the /Server folder)

## Microcontroller
 - Change your microcontroller code adding the target KeyboardLayout and the content of GetPayload.ps1
 - GetPayload.ps1 command is what your microcontroller will actually write on victim console

# ATTACK SEQUENCE:
 - Fake usb get utility.exe (the malicious code) from the C2 server and store in in /Temp folder
 - Then utility.exe is linked to startup folder
 - Utility.exe can be anything, from a simple Keylogger to something more sophisticated


#### NOTE the given `utility.exe` is just a MessageBox that says HI
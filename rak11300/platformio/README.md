# RAK Wireless RAK11300 / RAK11310 :: Developing with PlatformIO


https://learn.rakwireless.com/hc/en-us/articles/26687276346775-How-To-Perform-Installation-of-Board-Support-Package-in-PlatformIO

`Platformio.ini`:
```
[platformio]
boards_dir = rakwireless/boards
; other required definitions

[env:rak11300]
platform = https://github.com/maxgerhardt/platform-raspberrypi
board_build.core = earlephilhower
board = rakwireless_rak11300
framework = arduino
build_flags = 
-D ARDUINO_RAKWIRELESS_RAK11300=1
; WisBlock definitions
-I rakwireless/variants/rak11300
-D WB_IO1=6
-D WB_IO2=22
-D WB_IO3=7
-D WB_IO4=28
-D WB_IO5=9
-D WB_IO6=8
-D WB_A0=26
-D WB_A1=27
-D PIN_LED1=23
-D PIN_LED2=24
-D LED_BUILTIN=23
-D LED_CONN=24
-D LED_GREEN=23
-D LED_BLUE=24
; other build flags
lib_deps = 
; project library dependencies
; other required environment definitions
```
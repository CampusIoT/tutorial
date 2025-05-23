# micro:bit

https://microbit.org/

The micro:bit is a pocket-sized computer designed to inspire creative thinking in children. It can be programmed in many different ways and has multiple uses. Through the micro:bit, children are encouraged to explore ideas using real code.

![Heart Beat](makecode_heart_beat.gif)

## Versions

> Note: [2 versions of micro:bit boards coexist](https://kitronik.co.uk/blogs/resources/explore-micro-bit-v1-microbit-v2-differences) : 

| Previous (v1.5) |	Feature |	Latest (v2) |
|	-	|	-	|	-	|
|	25 Programmable LEDs in a 5 x 5 grid	|	LED Matrix	|	25 Programmable LEDs in a 5 x 5 grid	|
|	3-axis motion sensing	|	Accelerometer	|	3-axis motion sensing	|
|	On-board magnetometer	|	Compass	|	On-board magnetometer	|
|	On-board temperature sensor	|	Temperature sensing	|	On-board temperature sensor	|
|	On-board light level sensing	|	Light level sensing	|	On-board light level sensing	|
|	2 x programmable buttons, A & B	|	User Buttons	|	2 x programmable buttons, A & B	|
|	BLE Bluetooth 4.0	|	Bluetooth	|	BLE Bluetooth 5.0	|
|	2.4Ghz Micro:bit Radio	|	Radio	|	2.4Ghz Micro:bit Radio	|
|	Rear-mounted push button	|	Reset Button	|	Rear-mounted push button	|
|	N/A	|	On/Off switch	|	Power off (push and hold power button)	|
|	25 pins	|	Edge Connector	|	25 pins	|
|	N/A	|	Microphone	|	MEMS microphone and LED indicator	|
|	N/A	|	Speaker	|	Onboard speaker	|
|	N/A	|	Logo touch	|	Touch-sensitive logo pin	|
|	N/A	|	Power indicator	|	LED power indicator	|
|	C++, MakeCode, Python, Scratch	|	Software	|	C++, MakeCode, Python, Scratch	|


## Pinouts

![](images/56100-micro-bit-v2-V1-edge-connector.webp)

## Firmware


### Makecode

drag-n-drop block programming or Javascript

https://learn.adafruit.com/how-to-use-micro-bit-classroom-to-manage-programming-lessons

### Javascript

https://makecode.microbit.org/courses/blocks-to-javascript/hello-javascript

### Micropython

https://python.microbit.org/v/3

### Arduino

https://learn.adafruit.com/use-micro-bit-with-arduino/overview

go to Preferences and add `https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json`

Open `Tools>Board>Boards Manager` from the menu bar, search for nRF5 and install `Nordic Semiconductor nRF5 Boards` by Sandeep Mistry

Select `BBC micro:bit` from the Boards menu

* Blink
* Buttons
* GPIO
* Speaker
* LED Matrix
* Accelerometer (MMA8653 or LSM303AGR)
* Magnetometer (MAG3110 or LSM303AGR)
* BLE UART
* BLE Plotter
* BLE Controller
* Temperature


* [Adafruit Bluefruit Connect for iOS (and MacOSX)](https://apps.apple.com/us/app/bluefruit-connect/id830125974)


### RIOT OS

https://doc.riot-os.org/group__boards__microbit.html


## Enclosures

* https://www.printables.com/model/319713-bbc-microbit-v2-case
* https://www.printables.com/model/293153-gamer-case-for-bbc-microbit-v2-remix-wip

## Funny projects

* [Tilt Controlled Marble Maze](https://learn.adafruit.com/tilt-controlled-marble-maze) with [[MicroPython](https://learn.adafruit.com/tilt-controlled-marble-maze/circuitpython-code)]

## References

* https://kitronik.co.uk/blogs/resources/explore-micro-bit-v1-microbit-v2-differences
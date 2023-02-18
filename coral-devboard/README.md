# Google Coral Dev Board

The [Google Coral Dev Board](https://coral.ai/products/dev-board/) is a Quad-core symmetric Cortex-A53 processors (with GPU and VPU) and an Edge TPU coprocessor as low-power ML acceleror ([4 TOPS, 2 TOPS per watt](https://coral.ai/docs/edgetpu/benchmarks/)). The 40x48mm system-on-module (SoM) included with the Dev Board is based on NXP's iMX 8M system-on-chip (SoC) and contains all the essential system hardware, including the Edge TPU and Wi-Fi/Bluetooth radios. It is attached to the Dev Board baseboard with three 100-pin board-to-board connectors. Network interfaces include Gigabit Ethernet, WiFi and Bluetooh 4.2 (including BLE). The board had a MicroSD slot and connectors for camera (MIPI CSI-2 camera connector), audio, external stereo speakers, video (HDMI and MIPI DSI display connector), USB-C and USB Micro-B for serial console. GPIO are available on the 40-pin I/O header.

![coral-devboard](./images/coral-devboard-01.jpg)

## Getting started
TODO

### Install Mendel Linux

* https://coral.ai/docs/dev-board/get-started/#flash-the-board
* https://coral.googlesource.com/docs/+/refs/heads/master/GettingStarted.md


## OV5644 Camera (5 megapixels)

* https://fr.aliexpress.com/item/1005003709936187.html
* https://coral.ai/products/camera/
* https://coral.ai/docs/dev-board/camera/#view-on-a-monitor

## Environmental Sensor Board

* https://coral.ai/products/environmental/

## LoRaWAN modem

Connect the [LoRaWAN E5 modem](https://wiki.seeedstudio.com/Grove_LoRa_E5_New_Version/) on the header according the following pinout:

TODO

## Machine Learning with Edge TPU

TODO

* https://coral.ai/docs/edgetpu/models-intro/#compatibility-overview


## References 
* https://www.mouser.fr/datasheet/2/963/Coral-Dev-Board-datasheet-1605708.pdf
* https://github.com/google-coral
* https://github.com/google-coral/tutorials
* https://colab.research.google.com/github/google-coral/tutorials/blob/master/run_colab_on_devboard.ipynb


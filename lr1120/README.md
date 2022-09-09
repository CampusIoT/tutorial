# Semtech LR1120 :: LoRa transceiver + GNSS/Wifi Sniffer

''The [LR1120](https://fr.semtech.com/products/wireless-rf/lora-edge/lr1120) is an ultra-low power device targeting global geolocation applications. It provides multi band LoRa® and Long Range - Frequency Hopping Spread Spectrum (LR-FHSS) communication over sub-GHz and 2.4GHz Industrial, Scientific and Medical (ISM) bands as well as licensed S-Band for satellites. It integrates a Cloud-native multi-constellation global navigation satellite system (GNSS) scanner and a passive Wi-Fi MAC address scanner, both leveraging Semtech’s LoRa Cloud™ services.''


Check the model of your LR1120 shield. Mine is `LR1120MB1DIS` (868 MHz for the SubGhz interface)

## Build

```bash
mkdir -p github/lora-net
cd github/lora-net/
git clone https://github.com/Lora-net/SWSD003
cd SWSD003/
```

## Demonstration

### Ping Pong

```bash
cd ping_pong/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/ping_pong.bin  /Volumes/NODE_L476RG/
```

###  Spectral scan

```bash
cd spectral_scan/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/spectral_scan.bin  /Volumes/NODE_L476RG/
```

###  GNSS

```bash
cd gnss/gnss_autonomous/
cd makefile/
make RADIO_SHIELD=LR1120MB1DIS
cp build/gnss.bin  /Volumes/NODE_L476RG/
```


## Console
```bash
brew install tio
tio -L
tio -b 921600 -m INLCRNL /dev/tty.usbmodem142xxx
````

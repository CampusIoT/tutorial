# Liligo TTgo TBEAM SUPREME

https://lilygo.cc/products/t-beam-supreme-meshtastic


## Fiche technique

    Microprocesseur : ESP32-S3FN8 double cœur LX7
    Module LoRa : SX1262
    Fréquences ISM : 868 MHz
    Puissance d'émission max. : +20dBm - 100mW
    Stabilité en fréquence : +/- 15KHz
    Interface : SPI
    Température de fonctionnement: -40° / +85°
    Fonction numérique RSSI
    Correction automatique de fréquence
    Contrôle automatique du gain
    Réveil rapide et saut de fréquence
    Gestionnaire de paquets de données
    Connecteur antennes : SMA femelle
    Modules GPS L76K
    Avec antenne GPS céramique intégrée
    Module Bluetooth 5
    Module WIFI : 2.4 GHz
    Sauvegarde des données de configuration EEPROM
    Indicateur de signal LED
    Gestion de la batterie
    Alimentation : 3V-5V
    Alimentation : Micro-USB ou batterie 18650 (non incluses)
    Puce série : CH9102
    Firmware pré-chargé : Meshtastic
    Version TTGO T-BEAM : SUPREME
    Mémoire flash : 8MB
    Mémoire PSRAM : 8MB
    3 boutons : Power+IO38+Reset

schematic : https://github.com/Xinyuan-LilyGO/LilyGo-LoRa-Series/blob/master/schematic/LilyGo_T-BeamS3Supreme.pdf

## Firmware

* https://github.com/Xinyuan-LilyGO/LilyGo-LoRa-Series
* https://github.com/meshtastic/firmware

### Arduino

```
./examples/
├── ArduinoLoRa                              # Only support SX1276/SX1278 radio module
│   ├── LoRaReceiver
│   └── LoRaSender
├── Display                                  # Only supports TBeam TFT Shield
│   ├── Free_Font_Demo
│   ├── TBeam_TFT_Shield
│   ├── TFT_Char_times
│   └── UTFT_demo
├── GPS                                      # T-Beam GPS demo examples
│   ├── TinyGPS_Example
│   ├── TinyGPS_FullExample
│   ├── TinyGPS_KitchenSink
│   ├── UBlox_BasicNMEARead                  # Only support Ublox GNSS Module           
│   ├── UBlox_NMEAParsing                    # Only support Ublox GNSS Module           
│   ├── UBlox_OutputRate                     # Only support Ublox GNSS Module      
│   └── UBlox_Recovery                       # Only support Ublox GNSS Module      
├── LoRaWAN                                  # LoRaWAN examples
│   ├── LMIC_Library_OTTA
│   └── RadioLib_OTAA
├── OLED
│   ├── SH1106FontUsage
│   ├── SH1106GraphicsTest
│   ├── SH1106IconMenu
│   ├── SH1106PrintUTF8
│   ├── SSD1306SimpleDemo
│   └── SSD1306UiDemo
├── PMU                                      # T-Beam & T-Beam S3 PMU demo examples
├── RadioLibExamples                         # RadioLib examples,Support SX1276/78/62/80...
│   ├── Receive_Interrupt
│   └── Transmit_Interrupt
├── Sensor                                   # Sensor examples,only support t-beams3-supreme
│   ├── BME280_AdvancedsettingsExample
│   ├── BME280_TestExample
│   ├── BME280_UnifiedExample
│   ├── PCF8563_AlarmByUnits
│   ├── PCF8563_SimpleTime
│   ├── PCF8563_TimeLib
│   ├── PCF8563_TimeSynchronization
│   ├── QMC6310_CalibrateExample
│   ├── QMC6310_CompassExample
│   ├── QMC6310_GetDataExample
│   ├── QMC6310_GetPolarExample
│   ├── QMI8658_BlockExample
│   ├── QMI8658_GetDataExample
│   ├── QMI8658_InterruptBlockExample
│   ├── QMI8658_InterruptExample
│   ├── QMI8658_LockingMechanismExample
│   ├── QMI8658_MadgwickAHRS
│   ├── QMI8658_PedometerExample
│   ├── QMI8658_ReadFromFifoExample
│   └── QMI8658_WakeOnMotion
|── T3S3Factory                              # T3 S3 factory test examples
└── BPFFactory                               # T-Beam BPF factory test examples
```
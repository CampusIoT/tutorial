# Ecole MPLS 2025 :: Atelier GNSS

## Partie 1: GNSS

### Installation

Installez l'[IDE Arduino](https://www.arduino.cc/en/software) (2.3.4 ou plus) sur votre PC (Windows ou Mac) ou Mac

Ajoutez la définition des cartes ESP32 `[https://dl.espressif.com/dl/package_esp32_index.json](https://github.com/espressif/arduino-esp32/tree/master/libraries)` dans les préférences `Preferences > URL of Board manager`

Installez la bibliothéque `TinyGPSPlusPlus` depuis le gestionnaire de bibliothèques `Tools > Manage Libraries ...`.

Sélectionnez votre carte (`ESP32S3 Dev Module` ou `ESP32C3 Dev Module`) dans `Tools > Board > esp32`.

Sélectionnez le port auquel est connecté la carte dans `Tools > Port`.

### Pratique

| Fabricant | Module | Baudrate |
| --------- | ------ | -------- |
|  [Adafruit Ultimate GPS Featherwing](https://learn.adafruit.com/adafruit-ultimate-gps-featherwing) | MTK3333 |  9600 |


#### Visualisation des trames NMEA0183

Ouvrez l'exemple `XXXX`

```c++
// Test code for Ultimate GPS Using Hardware Serial
// (e.g. GPS for Leonardo, Flora or FeatherWing)
//
// This code shows how to test a passthru between USB and hardware serial
//
// Tested and works great with the Adafruit GPS FeatherWing
// ------> https://www.adafruit.com/products/3133
// or Flora GPS
// ------> https://www.adafruit.com/products/1059
// but also works with the shield, breakout
// ------> https://www.adafruit.com/products/1272
// ------> https://www.adafruit.com/products/746
//
// Pick one up today at the Adafruit electronics shop
// and help support open source hardware & software! -ada


// what's the name of the hardware serial port?
#define GPSSerial Serial1


void setup() {
  // make this baud rate fast enough to we aren't waiting on it
  Serial.begin(115200);

  // wait for hardware serial to appear
  while (!Serial) delay(10);

  // 9600 baud is the default rate for the Ultimate GPS
  GPSSerial.begin(9600);
}


void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    GPSSerial.write(c);
  }
  if (GPSSerial.available()) {
    char c = GPSSerial.read();
    Serial.write(c);
  }
}
```


Compilez et chargez le programme sur la carte.

Ouvrez la console série (baudrate 9600).

```
$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C
$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62
$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77
$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C
$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D
$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F
```

Commentaires:
* les phrases `GPRMC` ...
* les phrases `GPGGA` ...

#### Décodage des trames NMEA0183 avec la bibliothèque TinyGPS d'Arduino

##### `DeviceExample`

Ouvrez l'exemple `DeviceExample` dans `Examples > TinyGPS++ > DeviceExample`

Modifiez la valeur `GPSBaud` dans la ligne `static const uint32_t GPSBaud = 4800;` en fonction du module GNSS que vous avez à vous disposition.

Compilez et chargez le programme sur la carte.

Ouvrez la console série.

##### `SatElevTracker`

Ce code d’exemple suit l’élévation des satellites en utilisant des objets TinyGPSCustom. Les numéros et élévations des satellites ne sont normalement pas suivis par TinyGPSPlus, mais en utilisant TinyGPSCustom, nous contournons cette limitation.

Modifiez la valeur `GPSBaud` dans la ligne `static const uint32_t GPSBaud = 4800;` en fonction du module GNSS que vous avez à vous disposition.

Compilez et chargez le programme sur la carte.

Ouvrez la console série.

##### `SatelliteTracker`

Modifiez la valeur `GPSBaud` dans la ligne `static const uint32_t GPSBaud = 4800;` en fonction du module GNSS que vous avez à vous disposition.

Compilez et chargez le programme sur la carte.

Ouvrez la console série.

##### `FullExample`

Modifiez la valeur `GPSBaud` dans la ligne `static const uint32_t GPSBaud = 4800;` en fonction du module GNSS que vous avez à vous disposition.

Modifiez la ligne `static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;` par la ligne `static const double LONDON_LAT = 44.910101, LONDON_LON = 5.782137;` qui est l'[emplacement du Murtel](https://www.openstreetmap.org/relation/109753#map=19/44.910101/5.782137).

Compilez et chargez le programme sur la carte.

Ouvrez la console série.

#### Récupération sur signal PPS du module GNSS

Code source à fournir : https://forum.arduino.cc/t/pps-from-ultimate-gps-synch-with-arduino-uno/336683/4

## Partie 2: RTK

### Installation

Installez l’application Bluetooth GNSS sur votre téléphone Android depuis le [Play Store](https://play.google.com/store/apps/details?id=com.clearevo.bluetooth_gnss&hl=fr)

### Configuration

![Bluetooth GNSS](../rtk_surveyor/bluetooth_gnss-01.png)
![Bluetooth GNSS](../rtk_surveyor/bluetooth_gnss-03.png)
![Bluetooth GNSS](../rtk_surveyor/bluetooth_gnss-02.png)

### Pratique

![Surveyor Belledone](../rtk_surveyor/surveyor-01.jpg)




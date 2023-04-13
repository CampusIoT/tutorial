/**
 * Scanner 1-Wire (Dallas) pour cartes Arduino et compatible.
 */

/* Dépendances */
#include <OneWire.h>
#include <avr/pgmspace.h>

/** Broche pour le bus 1-Wire */
const byte ONEWIRE_BUS_PIN = 10;

/** L'object OneWire pour communiquer via le protocole 1-Wire sur la broche spécifiée */
OneWire ds(ONEWIRE_BUS_PIN);

/** Fonction setup() */
void setup(void) {
  
  /* Initialise le port série */
  Serial.begin(115200);
  Serial.println(F("~~ Scanner 1-Wire ~~"));
}

/** Fonction loop() */
void loop(void) {
  byte address[8];
  
  /* Cherche un module 1-Wire sur le bus */
  if (!ds.search(address)) {
    Serial.println(F("End of Scan."));
    ds.reset_search();
    for(;;);
  }
  
  /* Module 1-Wire découvert ! */
  Serial.print(F("Found "));
  for(byte i = 0; i < 8; ++i) {
    if (address[i] < 0x10) Serial.write('0');
    Serial.print(address[i], HEX);
    Serial.write(' ');
  }

  /* Vérifie si l'adresse est valide */
  if (OneWire::crc8(address, 7) != address[7]) {
      Serial.print(F("(CRC invalid)"));
  }
  
  /* Affiche les informations sur le module */
  Serial.println(get_onewire_family_description(address));
}

/* Dictionnaire des modules 1-Wire connus */
const __FlashStringHelper * get_onewire_family_description(const byte * address) {
  switch(address[0]) {
    case 0: return F("(Link locator): Provide location information");
    case 1: return F("(DS2401, DS1990R, DS2411, DS2490A, DS1990A): 1-Wire serial number");
    case 2: return F("(DS1425, DS1991): Multikey iButton secure memory");
    case 4: return F("(DS2404, DS1994): Econoram NVRAM memory and clock, timer, alarms");
    case 5: return F("(DS2405): Single addressable switch");
    case 6: return F("(DS1993): 4Kb NVRAM memory");
    case 8: return F("(DS1992): 1Kb NVRAM memory");
    case 9: return F("(DS2704, DS2703, DS2502, DS1982): 1Kb EPROM memory");
    case 10: return F("(DS1995): 16Kb NVRAM memory");
    case 11: return F("(DS2505, DS1985): 16Kb EPROM memory");
    case 12: return F("(DS1996): 64Kb NVRAM memory");
    case 15: return F("(DS2506, DS1986): 64Kb EPROM memory");
    case 16: return F("(DS1920, DS18S20): High precision digital thermometer with alarm trips");
    case 18: return F("(DS2406, DS2407): 1Kb EPROM memory, two channel addressable switch");
    case 20: return F("(DS2430A, DS1971): 256-bit EEPROM memory and 64-bit OTP register");
    case 22: return F("(DS1954, DS1957): crypto-ibutton");
    case 24: return F("(DS1963S, DS1962): SHA iButton");
    case 26: return F("(DS1963L): 4Kb NVRAM memory with write cycle counters");
    case 27: return F("(DS2436): Battery monitor and ID");
    case 28: return F("(DS28E04-100): 4Kb EEPROM memory, two channel addressable switch");
    case 29: return F("(DS2423): 4Kb NVRAM memory with external counters");
    case 30: return F("(DS2437): Battery monitor");
    case 31: return F("(DS2409): Microhub, two channel addressable coupler for sub-netting");
    case 32: return F("(DS2450): Quad channel A/D converter");
    case 33: return F("(DS1921, DS1921H, DS1921Z, DS1921G): Thermochron temperature logger");
    case 34: return F("(DS1822, DS1922): Econo Digital Thermometer");
    case 35: return F("(DS1973, DS2433): 4Kb EEPROM memory");
    case 36: return F("(DS1904, DS2415): Real-time clock (RTC)");
    case 38: return F("(DS2438): Smart battery monitor");
    case 39: return F("(DS2417): Real-time clock (RTC) with interrupt");
    case 40: return F("(DS18B20): Programmable resolution digital thermometer");
    case 41: return F("(DS2408): 8-channel addressable switch");
    case 44: return F("(DS2890): 1-channel digital potentiometer");
    case 45: return F("(DS1972, DS2431): 1Kb EEPROM memory");
    case 46: return F("(DS2770): Battery monitor and charge controller");
    case 48: return F("(DS2760, DS2762, DS2761): High precision li+ battery monitor with alerts");
    case 49: return F("(DS2720): Single-cell rechargable lithium battery protection and ID");
    case 50: return F("(DS2780): Battery");
    case 51: return F("(DS1961S, DS2432): 1Kb protected EEPROM with SHA-1");
    case 52: return F("(DS2703): SHA-1 Battery");
    case 53: return F("(DS2755): Battery");
    case 54: return F("(DS2740): High precision Coulomb counter");
    case 55: return F("(DS1977): Password-protected 32KB (bytes) EEPROM");
    case 58: return F("(DS2413): Dual channel addressable switch");
    case 59: return F("(DS1825, MAX31826): Temperature and memory");
    case 61: return F("(DS2781): Battery");
    case 65: return F("(DS1922L, DS2422, DS1922T, DS1923): High-capacity Thermochron (temperature) and Hygrochron (humidity) loggers");
    case 66: return F("(DS28EA00): Programmable resolution digital thermometer with sequenced detection and PIO");
    case 67: return F("(DS28EC20): 20Kb EEPROM memory");
    case 68: return F("(DS28E10): SHA-1 Authenticator");
    case 81: return F("(DS2751): Battery monitor and level gauge");
    case 126: return F("(EDS00xx): Environmental Monitors");
    case 129: return F("(DS1420): Serial ID Button");
    case 130: return F("(DS1425): Authorization");
    case 132: return F("(DS2404S): Dual port plus time");
    case 137: return F("(DS2502-UNW, DS1982U, DS2502-E48): Uniqueware 48-bits node address chip");
    case 139: return F("(DS2505-UNW, DS1985U): Uniqueware 16Kb add-only memory");
    case 143: return F("(DS1986U, DS2506-UNW): Uniqueware 64k add-only memory");
    case 160: return F("(mRS001): Rotation Sensor");
    case 161: return F("(mVM001): Vibration");
    case 162: return F("(mCM001): AC Voltage");
    case 166: return F("(mTS017): IR Temperature");
    case 177: return F("(mTC001): Thermocouple Converter");
    case 178: return F("(mAM001): DC Current or Voltage");
    case 179: return F("(mTC002): Thermocouple Converter");
    case 238: return F("(UVI): Ultra Violet Index");
    case 239: return F("(Moisture Hub): Moisture meter, 4 channel hub");
    case 252: return F("(BAE0910, BAE0911): Programmable Microprocessor");
    case 255: return F("(LCD): Swart LCD (Swart)");
    default: return F("(unknown) : Unknown 1-Wire device");

// Feather9x_RX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (receiver)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_TX

#include <SPI.h>
#include <RH_RF95.h>

// First 3 here are boards w/radio BUILT-IN. Boards using FeatherWing follow.
#if defined (__AVR_ATmega32U4__)  // Feather 32u4 w/Radio
  #define RFM95_CS    8
  #define RFM95_INT   7
  #define RFM95_RST   4

#elif defined(ADAFRUIT_FEATHER_M0) || defined(ADAFRUIT_FEATHER_M0_EXPRESS) || defined(ARDUINO_SAMD_FEATHER_M0)  // Feather M0 w/Radio
  #define RFM95_CS    8
  #define RFM95_INT   3
  #define RFM95_RST   4

#elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_RFM)  // Feather RP2040 w/Radio
  #define RFM95_CS   16
  #define RFM95_INT  21
  #define RFM95_RST  17

#elif defined (__AVR_ATmega328P__)  // Feather 328P w/wing
  #define RFM95_CS    4  //
  #define RFM95_INT   3  //
  #define RFM95_RST   2  // "A"

#elif defined(ESP8266)  // ESP8266 feather w/wing
  #define RFM95_CS    2  // "E"
  #define RFM95_INT  15  // "B"
  #define RFM95_RST  16  // "D"

#elif defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2) || defined(ARDUINO_NRF52840_FEATHER) || defined(ARDUINO_NRF52840_FEATHER_SENSE)
  #define RFM95_CS   10  // "B"
  #define RFM95_INT   9  // "A"
  #define RFM95_RST  11  // "C"

#elif defined(ESP32)  // ESP32 feather w/wing
  #define RFM95_CS   33  // "B"
  #define RFM95_INT  27  // "A"
  #define RFM95_RST  13

#elif defined(ARDUINO_NRF52832_FEATHER)  // nRF52832 feather w/wing
  #define RFM95_CS   11  // "B"
  #define RFM95_INT  31  // "C"
  #define RFM95_RST   7  // "A"

#endif

/* Some other possible setups include:

// Feather 32u4:
#define RFM95_CS   8
#define RFM95_RST  4
#define RFM95_INT  7

// Feather M0:
#define RFM95_CS   8
#define RFM95_RST  4
#define RFM95_INT  3

// Arduino shield:
#define RFM95_CS  10
#define RFM95_RST  9
#define RFM95_INT  7

// Feather 32u4 w/wing:
#define RFM95_RST 11  // "A"
#define RFM95_CS  10  // "B"
#define RFM95_INT  2  // "SDA" (only SDA/SCL/RX/TX have IRQ!)

// Feather m0 w/wing:
#define RFM95_RST 11  // "A"
#define RFM95_CS  10  // "B"
#define RFM95_INT  6  // "D"
*/

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

#if defined(TINYGS)

#define RF95_FREQ 869.525
#define RF95_POWER 14 // 22
#define RF95_POWER_USERF0 false
#define RF95_PREAMBLE_LEN 8
#define RF95_SPREADING_FACTOR 8
#define RF95_BANDWIDTH 62500
#define RF95_CODING_RATE 8
#define RF95_CRC_ON true
//#define RF95_SYNCWORD 0x34 // public
#define RF95_SYNCWORD 0x12 // private
#define RF95_INVERT_IQ false

#else

#define RF95_FREQ 868.1
#define RF95_POWER 14
#define RF95_POWER_USERF0 false
#define RF95_PREAMBLE_LEN 8
#define RF95_SPREADING_FACTOR 12
#define RF95_BANDWIDTH 125000
#define RF95_CODING_RATE 5
#define RF95_CRC_ON true
//#define RF95_SYNCWORD 0x12 // private
#define RF95_SYNCWORD 0x34 // public
#define RF95_INVERT_IQ false

#endif

// add missing method for setting sync word 
//void RH_RF95::setSyncWord(int sw)
void RH_RF95_setSyncWord(int sw)
{
    rf95.spiWrite(RH_RF95_REG_39_SYNC_WORD,sw);
}

// SX127x series common LoRa registers
#define RADIOLIB_SX127X_REG_INVERT_IQ                           0x33
#define RADIOLIB_SX127X_REG_INVERT_IQ2                          0x3B

// RADIOLIB_SX127X_REG_INVERT_IQ
#define RADIOLIB_SX127X_INVERT_IQ_RXPATH_ON                     0b01000000  //  6     6   I and Q signals are inverted
#define RADIOLIB_SX127X_INVERT_IQ_RXPATH_OFF                    0b00000000  //  6     6   normal mode
#define RADIOLIB_SX127X_INVERT_IQ_TXPATH_ON                     0b00000001  //  0     0   I and Q signals are inverted
#define RADIOLIB_SX127X_INVERT_IQ_TXPATH_OFF                    0b00000000  //  0     0   normal mode

// RADIOLIB_SX127X_REG_INVERT_IQ2
#define RADIOLIB_SX127X_IQ2_ENABLE                              0x19        //  7     0   enable optimize for inverted IQ
#define RADIOLIB_SX127X_IQ2_DISABLE                             0x1D        //  7     0   reset optimize for inverted IQ

/*!
      From https://github.com/jgromes/RadioLib/blob/master/src/Module.h#L268
      \brief Overwrite-safe SPI write method with verification. This method is the preferred SPI write mechanism.
      \param reg Address of SPI register to write.
      \param value Single byte value that will be written to the SPI register.
      \param msb Most significant bit of the register variable. Bits above this one will not be affected by the write operation.
      \param lsb Least significant bit of the register variable. Bits below this one will not be affected by the write operation.
      \param checkInterval Number of milliseconds between register writing and verification reading. Some registers need up to 10ms to process the change.
      \param checkMask Mask of bits to check, only bits set to 1 will be verified.
      \param force Write new value even if the old value is the same.
      \returns \ref status_codes
    */
int16_t Module_SPIsetRegValue(uint32_t reg, uint8_t value, uint8_t msb = 7, uint8_t lsb = 0, uint8_t checkInterval = 2, uint8_t checkMask = 0xFF, bool force = false) {

  // read the current value
  uint8_t currentValue = rf95.spiRead(reg);
  uint8_t mask = ~((0b11111111 << (msb + 1)) | (0b11111111 >> (8 - lsb)));

  // update the register
  uint8_t newValue = (currentValue & ~mask) | (value & mask);
  rf95.spiWrite(reg, newValue);
}

// add missing method for setting invert iq 
// from https://github.com/jgromes/RadioLib/tree/master/src/modules/SX127x
void RH_RF95_setInvertIQ(bool enable)
{
  if(enable) {
    Module_SPIsetRegValue(RADIOLIB_SX127X_REG_INVERT_IQ, RADIOLIB_SX127X_INVERT_IQ_RXPATH_ON, 6, 6);
    Module_SPIsetRegValue(RADIOLIB_SX127X_REG_INVERT_IQ, RADIOLIB_SX127X_INVERT_IQ_TXPATH_OFF, 0, 0);
    Module_SPIsetRegValue(RADIOLIB_SX127X_REG_INVERT_IQ2, RADIOLIB_SX127X_IQ2_ENABLE);
  } else {
    Module_SPIsetRegValue(RADIOLIB_SX127X_REG_INVERT_IQ, RADIOLIB_SX127X_INVERT_IQ_RXPATH_OFF, 6, 6);
    Module_SPIsetRegValue(RADIOLIB_SX127X_REG_INVERT_IQ, RADIOLIB_SX127X_INVERT_IQ_TXPATH_ON, 0, 0);
    Module_SPIsetRegValue(RADIOLIB_SX127X_REG_INVERT_IQ2, RADIOLIB_SX127X_IQ2_DISABLE);
  }
}

// Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
void _config(void){

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  
  rf95.setTxPower(RF95_POWER, RF95_POWER_USERF0);
  rf95.setPreambleLength(RF95_PREAMBLE_LEN);
  rf95.setSpreadingFactor(RF95_SPREADING_FACTOR);
  rf95.setSignalBandwidth(RF95_BANDWIDTH);
  rf95.setCodingRate4(RF95_CODING_RATE);
  rf95.setPayloadCRC(RF95_CRC_ON);
  RH_RF95_setSyncWord(RF95_SYNCWORD);
//  RH_RF95_setInvertIQ(RF95_INVERT_IQ);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(9600);
  while (!Serial) delay(1);
  delay(100);

  Serial.println("Feather LoRa RX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  _config();
}

void loop() {

    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    Serial.println("Receiving ...");

    while (!rf95.available()) {
      // Should be a message for us now
    }

    if (rf95.recv(buf, &len)) {
      digitalWrite(LED_BUILTIN, HIGH);
      RH_RF95::printBuffer("Received: ", buf, len);
      Serial.print("Got: ");
      Serial.println((char*)buf);
       Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);

      // Send a reply
      uint8_t data[] = "And hello back to you";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Serial.println("Sent a reply");
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      Serial.println("Receive failed");
    }
}

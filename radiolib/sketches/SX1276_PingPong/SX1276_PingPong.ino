/*
  RadioLib SX127x Ping-Pong Example

  This example is intended to run on two SX126x radios,
  and send packets between the two.

  For default module settings, see the wiki page
  https://github.com/jgromes/RadioLib/wiki/Default-configuration#sx127xrfm9x---lora-modem

  For full API reference, see the GitHub Pages
  https://jgromes.github.io/RadioLib/
*/

// include the library
#include <RadioLib.h>

// uncomment the following only on one
// of the nodes to initiate the pings
#define INITIATING_NODE

// SX1276MB1xAS https://os.mbed.com/components/SX1276MB1xAS/


// SX1276 has the following connections:
// NSS pin:   10
// DIO0 pin:  2
// NRST pin:  9
// DIO1 pin:  3
SX1276 radio = new Module(D10, D2, A0, D3);

// or detect the pinout automatically using RadioBoards
// https://github.com/radiolib-org/RadioBoards
/*
#define RADIO_BOARD_AUTO
#include <RadioBoards.h>
Radio radio = new RadioModule();
*/

// save transmission states between loops
int transmissionState = RADIOLIB_ERR_NONE;

// flag to indicate transmission or reception state
bool transmitFlag = false;

// flag to indicate that a packet was sent or received
volatile bool operationDone = false;

// this function is called when a complete packet
// is transmitted or received by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
#if defined(ESP8266) || defined(ESP32)
  ICACHE_RAM_ATTR
#endif
void setFlag(void) {
  // we sent or received  packet, set the flag
  operationDone = true;
}

void _config() {

  // initialize the second LoRa instance with
  // non-default settings
  // this LoRa link will have high data rate,
  // but lower range
  // NOTE: when using spreading factor 6, the total packet
  //       length has to be known in advance!
  //       you have to pass the number of expected bytes
  //       to the receive() method

  // you can also change the settings at runtime
  // and check if the configuration was changed successfully

  // set carrier frequency to 433.5 MHz
  if (radio.setFrequency(433.5) == RADIOLIB_ERR_INVALID_FREQUENCY) {
    Serial.println(F("Selected frequency is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set bandwidth to 250.0 kHz
  if (radio.setBandwidth(62.5) == RADIOLIB_ERR_INVALID_BANDWIDTH) {
    Serial.println(F("Selected bandwidth is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set spreading factor to 10
  if (radio.setSpreadingFactor(12) == RADIOLIB_ERR_INVALID_SPREADING_FACTOR) {
    Serial.println(F("Selected spreading factor is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set coding rate to 6
  if (radio.setCodingRate(6) == RADIOLIB_ERR_INVALID_CODING_RATE) {
    Serial.println(F("Selected coding rate is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set LoRa sync word to 0x14
  // NOTE: value 0x34 is reserved for LoRaWAN networks and should not be used
  if (radio.setSyncWord(0x12) != RADIOLIB_ERR_NONE) {
    Serial.println(F("Unable to set sync word!"));
    while (true) { delay(10); }
  }

  // set output power to 10 dBm (accepted range is -3 - 17 dBm)
  // NOTE: 20 dBm value allows high power operation, but transmission
  //       duty cycle MUST NOT exceed 1%
  if (radio.setOutputPower(17) == RADIOLIB_ERR_INVALID_OUTPUT_POWER) {
    Serial.println(F("Selected output power is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set over current protection limit to 80 mA (accepted range is 45 - 240 mA)
  // NOTE: set value to 0 to disable overcurrent protection
  if (radio.setCurrentLimit(80) == RADIOLIB_ERR_INVALID_CURRENT_LIMIT) {
    Serial.println(F("Selected current limit is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set LoRa preamble length to 15 symbols (accepted range is 6 - 65535)
  if (radio.setPreambleLength(8) == RADIOLIB_ERR_INVALID_PREAMBLE_LENGTH) {
    Serial.println(F("Selected preamble length is invalid for this module!"));
    while (true) { delay(10); }
  }

  // set amplifier gain to 1 (accepted range is 1 - 6, where 1 is maximum gain)
  // NOTE: set value to 0 to enable automatic gain control
  //       leave at 0 unless you know what you're doing
  if (radio.setGain(1) == RADIOLIB_ERR_INVALID_GAIN) {
    Serial.println(F("Selected gain is invalid for this module!"));
    while (true) { delay(10); }
  }

  Serial.println(F("All settings successfully changed!"));
}

void setup() {
  Serial.begin(9600);

  // initialize SX1276 with default settings
  Serial.print(F("[SX1276] Initializing ... "));
  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true) { delay(10); }
  }

  _config();

  // set the function that will be called
  // when new packet is received
  radio.setDio0Action(setFlag, RISING);

  #if defined(INITIATING_NODE)
    // send the first packet on this node
    Serial.print(F("[SX1276] Sending first packet ... "));
    transmissionState = radio.startTransmit("Hello World!");
    transmitFlag = true;
  #else
    // start listening for LoRa packets on this node
    Serial.print(F("[SX1276] Starting to listen ... "));
    state = radio.startReceive();
    if (state == RADIOLIB_ERR_NONE) {
      Serial.println(F("success!"));
    } else {
      Serial.print(F("failed, code "));
      Serial.println(state);
      while (true) { delay(10); }
    }
  #endif
}

void loop() {
  // check if the previous operation finished
  if(operationDone) {
    // reset flag
    operationDone = false;

    if(transmitFlag) {
      // the previous operation was transmission, listen for response
      // print the result
      if (transmissionState == RADIOLIB_ERR_NONE) {
        // packet was successfully sent
        Serial.println(F("transmission finished!"));

      } else {
        Serial.print(F("failed, code "));
        Serial.println(transmissionState);

      }

      // listen for response
      radio.startReceive();
      transmitFlag = false;

    } else {
      // the previous operation was reception
      // print data and send another packet
      String str;
      int state = radio.readData(str);

      if (state == RADIOLIB_ERR_NONE) {
        // packet was successfully received
        Serial.println(F("[SX1276] Received packet!"));

        // print data of the packet
        Serial.print(F("[SX1276] Data:\t\t"));
        Serial.println(str);

        // print RSSI (Received Signal Strength Indicator)
        Serial.print(F("[SX1276] RSSI:\t\t"));
        Serial.print(radio.getRSSI());
        Serial.println(F(" dBm"));

        // print SNR (Signal-to-Noise Ratio)
        Serial.print(F("[SX1276] SNR:\t\t"));
        Serial.print(radio.getSNR());
        Serial.println(F(" dB"));

      }

      // wait a second before transmitting again
      delay(1000);

      // send another one
      Serial.print(F("[SX1276] Sending another packet ... "));
      transmissionState = radio.startTransmit("Hello World!");
      transmitFlag = true;
    }
  }
}

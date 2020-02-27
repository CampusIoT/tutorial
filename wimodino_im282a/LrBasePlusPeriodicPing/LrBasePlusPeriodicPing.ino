/*
 * This is a simple example file to show how to use the WiMOD Arduino
 * library to communicate with a WiMOD Module by IMST GmbH
 *
 * http://www.wireless-solutions.de
 *
 */

/*
 * Example usage:
 *
 * This example demonstrates the data link service of the LR-Base Plus firmware.
 *
 * A simple chat feature is implemented to send some messages from one device
 * to a peer device.
 *
 *
 * After setting up up everything the user can type in a short message that
 * is being transfered to the peer device.
 * If a message has been received from the peer device the message payload
 * will be printed as hex values.
 *
 * Setup requirements:
 * -------------------
 * - 2 WiMOD modules running LR-Base PLUS firmware
 *   * One WiMOD module is mounted to the (local) Ardunio
 *   * The second one can be an iM282 USB-Stick or a SK-iM282a connected to
 *     the WiMOD_LR_Studio Software. (Or a 2nd Arduino :-) )
 *  - Both modules must have the same radio settings (SF/Datarate/GroupAdr/...)
 *    (hint: simple way to archive that: do a factory reset on all devices)
 *
 * Usage:
 * -------
 * - Local device:
 *      -- Start the program
 *      -- open the serial monitor @ 115200 baud
 *      -- type in some short text and press enter
 *
 * - Peer device:
 *      -- the message should appear
 *      -- type in a new message and send it
 *
 * Note: Please enable the "Carriage return" option in the Serial Port Monitor
 *       of the Arduino IDE. The "carriage return" char is used to start
 *       transmitting the data.
 *
 */

// make sure to use only the WiMODLR_BASE_PLUS.h
#include <WiMODLR_BASE_PLUS.h>
#if defined(ARDUINO_ARCH_AVR)
#include <avr/pgmspace.h>
#endif


//-----------------------------------------------------------------------------
// platform defines
//-----------------------------------------------------------------------------
/*
 * Note: This sketch is for Arduino devices with two separate serial interfaces
 * (e.g. DUE). One interface is connected to a PC and one is used for WiMOD.
 *
 * For single serial interface boards (e.g. UNO) it is recommended to disbale
 * the PC / Debug messages
 */

#define WIMOD_IF    SerialWiMOD
#define PC_IF    SerialUSB


#define MAX_USER_INPUT_LEN                       50


//-----------------------------------------------------------------------------
// section RAM
//-----------------------------------------------------------------------------

/*
 * define two global radio messages
 *  Rx : This one is used for storing incomming RF messages
 *  Tx : This one is used for preparation of outgoing RF messages
 */
TWiMODLR_RadioLink_Msg radioRxMsg;
TWiMODLR_RadioLink_Msg radioTxMsg;

/*
 * user input related variables
 */
static bool showInputPrompt = true;
static char userInputData[MAX_USER_INPUT_LEN];
static unsigned int inputPos = 0;


/*
 * Create in instance of the interface to the WiMOD-LR-Base firmware
 */
WiMODLRBASE_PLUS wimod(WIMOD_IF);  // use the Arduino Serial3 as serial interface




//-----------------------------------------------------------------------------
// section code
//-----------------------------------------------------------------------------

void translate_Frequency(uint8_t msb, uint8_t mid, uint8_t lsb);
void translate_Modulation(TRadioCfg_ModulationPlus mod);
void translate_LoRaBandwith(TRadioCfg_LoRaBandwidthPlus bw);
void translate_FlrcBandwidth(TRadioCfg_FLRCBandwidthPlus bw);
void translate_FskBandwith(TRadioCfg_FSKBandwidthPlus bw);
void translate_LoRaSF(TRadioCfg_LoRaSpreadingFactorPlus sf);
void translate_LoRaErrorCoding(TRadioCfg_LoRaErrorCodingPlus ec);
void translate_FlrcErrorCoding(TRadioCfg_FLRCErrorCodingPlus ec);
void translate_TxControlMode(TRadioCfg_TxControlPlus txc);
void translate_RxControlMode(TRadioCfg_RxControlPlus rxc);
void translate_PwrSavingMode(TRadioCfg_PowerSavingModePlus pwr);
void translate_PowerLevel(TRadioCfg_PowerLevelPlus pwrLevel);
/*****************************************************************************
 * Functions for printing out some debug infos via serial interface
 ****************************************************************************/
void debugMsg(String msg) {
    PC_IF.print(msg);  // use default Arduino serial interface
}

void debugMsg(int a) {
    PC_IF.print(a, DEC);
}

void debugMsgChar(char c) {
    PC_IF.print(c);
}

void debugMsgHex(int a) {
    if (a < 0x10) {
        PC_IF.print(F("0"));
    }
    PC_IF.print(a, HEX);
}

/******************************************************************************
 * translate internal defines / names to user friendly strings
 * - for DataRateIndex field
 *****************************************************************************/

void translate_Frequency(uint8_t msb, uint8_t mid, uint8_t lsb) {
    uint32_t freq;
    char text[30];

    freq = wimod.calcRegisterToFreq(msb, mid, lsb);
    snprintf(text, 30, "%lu Hz", freq);

    debugMsg(String(text));
}

void translate_Modulation(TRadioCfg_ModulationPlus mod) {
    switch (mod) {
    case LRBASE_PLUS_Modulation_LoRa:
        debugMsg(F(" -> (LoRa)"));
        break;
    case LRBASE_PLUS_Modulation_FLRC:
        debugMsg(F(" -> (FLRC)"));
        break;
    case LRBASE_PLUS_Modulation_FSK:
        debugMsg(F(" -> (FSK)"));
        break;
    default:
        break;
    }
}

void translate_LoRaBandwith(TRadioCfg_LoRaBandwidthPlus bw) {
    switch (bw) {
    case LRBASE_PLUS_LoRaBandwith_200kHz:
        debugMsg(F(" -> (200 kHz)"));
        break;
    case LRBASE_PLUS_LoRaBandwith_400kHz:
        debugMsg(F(" -> (400 kHz)"));
        break;
    case LRBASE_PLUS_LoRaBandwith_800kHz:
        debugMsg(F(" -> (800 kHz)"));
        break;
    case LRBASE_PLUS_LoRaBandwith_1600kHz:
        debugMsg(F(" -> (1600 kHz)"));
        break;
    default:
        break;
    }
}

void translate_FlrcBandwidth(TRadioCfg_FLRCBandwidthPlus bw) {
    switch (bw) {
    case LRBASE_PLUS_FLRCBandwith_0_260MBs_0_3_MHz_DSB:
        debugMsg(F(" -> (260 kbps; 0.3 MHz)"));
        break;
    case LRBASE_PLUS_FLRCBandwith_0_325MBs_0_3_MHz_DSB:
        debugMsg(F(" -> (325 kbps; 0.3 MHz)"));
        break;
    case LRBASE_PLUS_FLRCBandwith_0_520MBs_0_6_MHz_DSB:
        debugMsg(F(" -> (520 kbps; 0.6 MHz)"));
        break;
    case LRBASE_PLUS_FLRCBandwith_0_650MBs_0_6_MHz_DSB:
        debugMsg(F(" -> (625 kbps; 0.6 MHz)"));
        break;
    case LRBASE_PLUS_FLRCBandwith_1_040MBs_1_2_MHz_DSB:
        debugMsg(F(" -> (1040 kbps; 1.2 MHz)"));
        break;
    case LRBASE_PLUS_FLRCBandwith_1_300MBs_1_2_MHz_DSB:
        debugMsg(F(" -> (1300 kbps; 1.2 MHz)"));
        break;
    default:
        break;
    }
}

void translate_FskBandwith(TRadioCfg_FSKBandwidthPlus bw) {
    switch (bw) {
    case LRBASE_PLUS_FSKBandwith_2_0MBs_2_4_MHz:
        debugMsg(F(" -> (2000 Mb/s /2,4 MHz)"));
        break;
    case LRBASE_PLUS_FSKBandwith_1_0MBs_1_2_MHz:
        debugMsg(F(" -> (1000 Mb/s /1,2 MHz)"));
        break;
        debugMsg(F(" -> (250 kb/s /0,3 MHz)"));
        break;
    case LRBASE_PLUS_FSKBandwith_0_250MBs_0_3_MHz:
        debugMsg(F(" -> (250 kb/s /0,3 MHz)"));
        break;
        debugMsg(F(" (125 kb/s /0,3 MHz)"));
        break;
    case LRBASE_PLUS_FSKBandwith_0_125MBs_0_3_MHz:
        debugMsg(F(" -> (125 kb/s /0,3 MHz)"));
        break;
    default:
        break;
    }
}

void translate_LoRaSF(TRadioCfg_LoRaSpreadingFactorPlus sf) {
    switch (sf) {
    case LRBASE_PLUS_LoRa_SF5:
        debugMsg(F(" -> (SF5)"));
        break;
    case LRBASE_PLUS_LoRa_SF6:
        debugMsg(F(" -> (SF6)"));
        break;
    case LRBASE_PLUS_LoRa_SF7:
        debugMsg(F(" -> (SF7)"));
        break;
    case LRBASE_PLUS_LoRa_SF8:
        debugMsg(F(" -> (SF8)"));
        break;
    case LRBASE_PLUS_LoRa_SF9:
        debugMsg(F(" -> (SF9)"));
        break;
    case LRBASE_PLUS_LoRa_SF10:
        debugMsg(F(" -> (SF10)"));
        break;
    case LRBASE_PLUS_LoRa_SF11:
        debugMsg(F(" -> (SF11)"));
        break;
    case LRBASE_PLUS_LoRa_SF12:
        debugMsg(F(" -> (SF12)"));
        break;
    default:
        break;
    }
}

void translate_LoRaErrorCoding(TRadioCfg_LoRaErrorCodingPlus ec) {
    switch (ec) {
    case LRBASE_PLUS_LoRa_ErrorCoding_4_5:
        debugMsg(F(" -> (4/5)"));
        break;
    case LRBASE_PLUS_LoRa_ErrorCoding_4_6:
        debugMsg(F(" -> (4/6)"));
        break;
    case LRBASE_PLUS_LoRa_ErrorCoding_4_7:
        debugMsg(F(" -> (4/7)"));
        break;
    case LRBASE_PLUS_LoRa_ErrorCoding_4_8:
        debugMsg(F(" -> (4/8)"));
        break;
    case LRBASE_PLUS_LoRa_ErrorCoding_LI_4_5:
        debugMsg(F(" -> (LongInterleave 4/5)"));
        break;
    case LRBASE_PLUS_LoRa_ErrorCoding_LI_4_6:
        debugMsg(F(" -> (LongInterleave 4/6)"));
        break;
    case LRBASE_PLUS_LoRa_ErrorCoding_LI_4_8:
        debugMsg(F(" -> (LongInterleave 4/8)"));
        break;
    default:
        break;
    }
}

void translate_FlrcErrorCoding(TRadioCfg_FLRCErrorCodingPlus ec) {
    switch (ec) {
    case LRBASE_PLUS_FLRC_ErrorCoding_1_2:
        debugMsg(F(" -> (1/2)"));
        break;
    case LRBASE_PLUS_FLRC_ErrorCoding_3_4:
        debugMsg(F(" -> (3/4)"));
        break;
    case LRBASE_PLUS_FLRC_ErrorCoding_1_1:
        debugMsg(F(" -> (1/1)"));
        break;
    default:
        break;
    }
}

void translate_PowerLevel(TRadioCfg_PowerLevelPlus pwrLevel) {
    switch (pwrLevel) {
        case LRBASE_PLUS_TxPowerLevel_m18_dBm:
            debugMsg(F(" -> (-18 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m17_dBm:
            debugMsg(F(" -> (-17 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m16_dBm:
            debugMsg(F(" -> (-16 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m15_dBm:
            debugMsg(F(" -> (-15 dBm)="));
            break;
        case LRBASE_PLUS_TxPowerLevel_m14_dBm:
            debugMsg(F(" -> (-14 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m13_dBm:
            debugMsg(F(" -> (-13 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m12_dBm:
            debugMsg(F(" -> (-12 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m11_dBm:
            debugMsg(F(" -> (-11 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m10_dBm:
            debugMsg(F(" -> (-10 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m09_dBm:
            debugMsg(F(" -> (-9 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m08_dBm:
            debugMsg(F(" -> (-8 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m07_dBm:
            debugMsg(F(" -> (-7 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m06_dBm:
            debugMsg(F(" -> (-6 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m05_dBm:
            debugMsg(F(" -> (-5 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m04_dBm:
            debugMsg(F(" -> (-4 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m03_dBm:
            debugMsg(F(" -> (-3 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m02_dBm:
            debugMsg(F(" -> (-2 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m01_dBm:
            debugMsg(F(" -> (-1 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_m00_dBm:
            debugMsg(F(" -> (0 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p01_dBm:
            debugMsg(F(" -> (1 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p02_dBm:
            debugMsg(F(" -> (2 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p03_dBm:
            debugMsg(F(" -> (3 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p04_dBm:
            debugMsg(F(" -> (4 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p05_dBm:
            debugMsg(F(" -> (5 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p06_dBm:
            debugMsg(F(" -> (6 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p07_dBm:
            debugMsg(F(" -> (7 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p08_dBm:
            debugMsg(F(" -> (8 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p09_dBm:
            debugMsg(F(" -> (9 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p10_dBm:
            debugMsg(F(" -> (10 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p11_dBm:
            debugMsg(F(" -> (11 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p12_dBm:
            debugMsg(F(" -> (12 dBm)"));
            break;
        case LRBASE_PLUS_TxPowerLevel_p13_dBm:
            debugMsg(F(" -> (13 dBm)"));
            break;
        default:
            break;
    }
}

void translate_TxControlMode(TRadioCfg_TxControlPlus txc) {
    switch (txc) {
        case LRBASE_PLUS_TxCtrl_LBT_Off:
            debugMsg(F(" -> (LBT check Off)"));
            break;
        case LRBASE_PLUS_TxCtrl_LBT_On:
            debugMsg(F(" -> (LBT check On)"));
            break;
        default:
            break;
    }
}

void translate_RxControlMode(TRadioCfg_RxControlPlus rxc) {
    switch (rxc) {
        case LRBASE_PLUS_RxCtrl_Receiver_Off:
            debugMsg(F(" -> (Receiver Off)"));
            break;
        case LRBASE_PLUS_RxCtrl_Receiver_AlwaysOn:
            debugMsg(F(" -> (Receiver Always On)"));
            break;
        case LRBASE_PLUS_RxCtrl_Receiver_RxWindowed:
            debugMsg(F(" -> (Receiver windowed RX)"));
            break;
        default:
            break;
    }
}


void translate_PwrSavingMode(TRadioCfg_PowerSavingModePlus pwr) {
    switch (pwr) {
        case LRBASE_PLUS_PowerSaving_Off:
            debugMsg(F(" -> (PwrSaving is Off)"));
            break;
        case LRBASE_PLUS_PowerSaving_On:
            debugMsg(F(" -> (PwrSaving is On)"));
            break;
        default:
            break;
    }
}
/*****************************************************************************
 * print out a welcome message
 ****************************************************************************/

void printStartMsg() {
    debugMsg(F("\n==================================================\n"));
    debugMsg(F("Starting...\n"));
    debugMsg(F("==================================================\n"));
}


void printConfigurationMsg() {
    debugMsg(F("\n==================================================\n"));
    debugMsg(F("Configuration\n"));
    debugMsg(F("==================================================\n"));
}

void printListeningAndSendingMsg() {
    debugMsg(F("\n==================================================\n"));
    debugMsg(F("Listening and sending packets ...\n"));
    debugMsg(F("==================================================\n"));
}



/*****************************************************************************
 * read and print out the configuration of the WiMOD module
 ****************************************************************************/
void printWimdRadioConfig() {
    TWiMODLR_DevMgmt_RadioConfigPlus radioCfg;

    debugMsg(F("\n\n RadioConfig:\n"));

    // read the current configuration of the WiMOD module
    if (wimod.GetRadioConfig(&radioCfg)) {
        // print out some parts of the config
        debugMsg(F("GroupAdr:      "));
        debugMsg(radioCfg.GroupAddress);
        debugMsg(F(" (0x"));
        debugMsgHex(radioCfg.GroupAddress);
        debugMsg(F(")\n"));

        debugMsg(F("TxGroupAdr:    "));
        debugMsg(radioCfg.TxGroupAddress);
        debugMsg(F(" (0x"));
        debugMsgHex(radioCfg.TxGroupAddress);
        debugMsg(F(")\n"));

        debugMsg(F("DeviceAdr:     "));
        debugMsg(radioCfg.DeviceAddress);
        debugMsg(F(" (0x"));
        debugMsgHex((radioCfg.DeviceAddress & 0xFF00) >> 8);
        debugMsgHex((radioCfg.DeviceAddress & 0xFF));
        debugMsg(F(")\n"));

        debugMsg(F("TxDeviceAdr:   "));
        debugMsg(radioCfg.TxDeviceAddress);
        debugMsg(F(" (0x"));
        debugMsgHex((radioCfg.TxDeviceAddress & 0xFF00) >> 8);
        debugMsgHex((radioCfg.TxDeviceAddress & 0xFF));
        debugMsg(F(")\n"));

        debugMsg(F("Frequency:     "));
        debugMsg(F("("));
        debugMsgHex(radioCfg.RfFreq_MSB);
        debugMsg(F("|"));
        debugMsgHex(radioCfg.RfFreq_MID);
        debugMsg(F("|"));
        debugMsgHex(radioCfg.RfFreq_LSB);
        debugMsg(F(")"));
        debugMsg(F(" -> "));
        translate_Frequency(radioCfg.RfFreq_MSB, radioCfg.RfFreq_MID,
                radioCfg.RfFreq_LSB);
        debugMsg(F("\n"));

        debugMsg(F("Modulation:    "));
        debugMsg((int) radioCfg.Modulation); // see TRadioCfg_ModulationPlus for symbolic meaning
        translate_Modulation(radioCfg.Modulation);
        debugMsg(F("\n"));

        switch (radioCfg.Modulation) {
        case LRBASE_PLUS_Modulation_LoRa:
            debugMsg(F("LoRa-BW ID:    "));
            debugMsg((int) radioCfg.LoRaBandWidth); // see TRadioCfg_LoRaBandwidthPlus for symbolic meaning
            translate_LoRaBandwith(radioCfg.LoRaBandWidth);
            debugMsg(F("\n"));

            debugMsg(F("LoRa-SF ID:    "));
            debugMsg((int) radioCfg.LoRaSpreadingFactor); // see TRadioCfg_LoRaSpreadingFactorPlus for symbolic meaning
            translate_LoRaSF(radioCfg.LoRaSpreadingFactor);
            debugMsg(F("\n"));

            debugMsg(F("LoRa-EC ID:    "));
            debugMsg((int) radioCfg.LoRaErrorCoding); // see TRadioCfg_LoRaErrorCodingPlus for symbolic meaning
            translate_LoRaErrorCoding(radioCfg.LoRaErrorCoding);
            debugMsg(F("\n"));

            break;
        case LRBASE_PLUS_Modulation_FLRC:
            debugMsg(F("FLRC-BW ID:    "));
            debugMsg((int) radioCfg.FLRCBandWidth); // see TRadioCfg_FLRCBandwidthPlus for symbolic meaning
            translate_FlrcBandwidth(radioCfg.FLRCBandWidth);
            debugMsg(F("\n"));

            debugMsg(F("FLRC-EC ID:    "));
            debugMsg((int) radioCfg.FLRCErrorCoding); // see TRadioCfg_FLRCErrorCodingPlus for symbolic meaning
            translate_FlrcErrorCoding(radioCfg.FLRCErrorCoding);
            debugMsg(F("\n"));

            break;

        case LRBASE_PLUS_Modulation_FSK:
            debugMsg(F("FSK-BW ID:     "));
            debugMsg((int) radioCfg.FSKBandWidth); // see TRadioCfg_FSKBandwidthPlus for symbolic meaning
            translate_FskBandwith(radioCfg.FSKBandWidth);
            debugMsg(F("\n"));
            break;
        default:
            break;
        }

        debugMsg(F("TxPwrLevel ID: "));  // see TRadioCfg_PowerLevelPlus for symbolic meaning
        debugMsg(radioCfg.PowerLevel);
        translate_PowerLevel(radioCfg.PowerLevel);
        debugMsg(F("\n"));

        debugMsg(F("TxControl:     0x"));  // see TRadioCfg_TxControlPlus for symbolic meaning
        debugMsgHex(radioCfg.TxControl);
        translate_TxControlMode(radioCfg.TxControl);
        debugMsg(F("\n"));

        debugMsg(F("RxControl:     0x"));  // see TRadioCfg_RxControlPlus for symbolic meaning
        debugMsgHex(radioCfg.RxControl);
        translate_RxControlMode(radioCfg.RxControl);
        debugMsg(F("\n"));

        debugMsg(F("RxWindow:      "));
        debugMsg((int) radioCfg.RxWindowTime);
        debugMsg(F(" ms \n"));

        debugMsg(F("LED Control:   0x"));
        debugMsgHex((int) radioCfg.LedControl);
        debugMsg(F("  \n"));

        debugMsg(F("Misc-Options:  0x"));
        debugMsgHex((int) radioCfg.MiscOptions);
        debugMsg(F("  \n"));

        debugMsg(F("PwrSave Mode:  "));
        debugMsg((int) radioCfg.PowerSavingMode); // see TRadioCfg_PowerSavingModePlus for symbolic meaning
        translate_PwrSavingMode(radioCfg.PowerSavingMode);
        debugMsg(F("  \n"));

        debugMsg(F("LBT Threshold: "));
        debugMsg((int) radioCfg.LbtThreshold);
        debugMsg(F("  dBm\n"));

    }

}

/*****************************************************************************
 * read and print out some infos about the firmware of the WiMOD module
 ****************************************************************************/
void printWimodFirmwareInfos() {
    TWiMODLR_DevMgmt_FwInfo fwInfo;

    debugMsg(F("\n\n FirmwareInfos:\n"));

    // readout the Firmware infomation
    if (wimod.GetFirmwareInfo(&fwInfo)) {
        debugMsg(F("FW-Name:  "));
        debugMsg((const char*) fwInfo.FirmwareName);
        debugMsg(F("\n"));

        debugMsg(F("FW-Date:  "));
        debugMsg((const char*) fwInfo.BuildDateStr);
        debugMsg(F("\n"));

        debugMsg(F("FW-Ver:   "));
        debugMsg(fwInfo.FirmwareMayorVersion);
        debugMsg(F("."));
        debugMsg(fwInfo.FirmwareMinorVersion);
        debugMsg(F("\n"));
        debugMsg(F("BuildCnt: "));
        debugMsg((int) fwInfo.BuildCount);
        debugMsg(F("\n"));
    }
}

//-----------------------------------------------------------------------------
// section code
//-----------------------------------------------------------------------------



/*****************************************************************************
 * function for transmitting a single radio message via RadioLink service
 ****************************************************************************/

void sendRadioMessage(char* buffer, int length)
{
    // check if there is data to send
    if (buffer && (length > 0)) {

        // setup destination address information for the RF message
        radioTxMsg.DestinationGroupAddress = 0x10;                            // use default dst group adr
        radioTxMsg.DestinationDeviceAddress = RADIOLINK_BROADCAST_DEVICE_ADR; // broadcast to every device
                                                                              // within the group
        // setup payload of RF message
        radioTxMsg.Length = length;
        memcpy(radioTxMsg.Payload, buffer, length);

      	debugMsg(F("Starting transmission... \r\n"));

        // send the RF message out (using the non-confirmed (aka. unreliable) transmission service
        // note: the confirmed service does NOT support broadcast addresses!!!!
        if (true == wimod.SendUData(&radioTxMsg)) {
            debugMsg(F("RF-Message has been send\n"));
        } else {
        	// error
        	debugMsg(F("Error sending message! "));
        	debugMsg(F("HCI result code: "));
        	debugMsgHex((int) wimod.GetLastHciResult());
          debugMsg(F("; RSP status code: "));
          debugMsgHex((int)wimod.GetLastResponseStatus());
          debugMsg(F("\r\n"));
        }

    }
}

void processSerialInputByte(const byte inByte)
{

    switch (inByte) {
        case '\n':   // end of line
        case '\r':   // carriage return
            userInputData[inputPos] = 0;  // terminating null byte

            // terminator reached; process userInputData here ...
            sendRadioMessage(userInputData, inputPos);

            // reset buffer for next time
            inputPos = 0;
            showInputPrompt = true;
            break;

        default:
            // add data to buffer
            if (inputPos < (MAX_USER_INPUT_LEN - 1))
                userInputData[inputPos++] = inByte;
            break;
    }
}

/*****************************************************************************
 * function reading a user string while not blocking the main loop
 ****************************************************************************/

void debugReadData_ORIGINAL()
{
    // show the input prompt only at "start"
    if (showInputPrompt) {
        debugMsg(F("Enter Tx-Message: "));
        showInputPrompt = false;
    }

    // check of the user as entered something on the "debug" serial interface
    if (PC_IF.available()) {
        // -> yes: process the input data
        processSerialInputByte(PC_IF.read());
    }
}

/*****************************************************************************
 * send a counter every 30 seconds
 ****************************************************************************/

#define TX_PERIOD 30000
long nextTxTimestamp = 0;
long fCnt = 0;

void periodicPing()
{
  unsigned long time = millis();
  
  if(time > nextTxTimestamp) {
    debugMsg(F("Sending fCnt="));
    debugMsg(fCnt);
    debugMsg(F(" at "));
    debugMsg(time/1000);
    debugMsg(F(" sec. ...\n"));
    sendRadioMessage((char*)&fCnt, sizeof(fCnt));
    fCnt++;
    nextTxTimestamp = time + TX_PERIOD;
  }
}

void debugReadData() {
  periodicPing();
}

/*****************************************************************************
 * Callback function for processing incomming RF messages
 ****************************************************************************/

void onRxData(TWiMODLR_HCIMessage& rxMsg) {
    int i;

    // convert/copy the raw message to RX radio buffer
    wimod.convert(rxMsg, &radioRxMsg);

    // print out the received message as hex string
    if (radioRxMsg.Length > 0) {
        // print out the length
        debugMsg(F("\nRx-Message: ["));
        debugMsg(radioRxMsg.Length);
        debugMsg(F("]: "));

        // print out the payload
        for (i = 0; i < radioRxMsg.Length; i++) {
            debugMsgHex(radioRxMsg.Payload[i]);
            debugMsg(F(" "));
        }

        debugMsg(F(", Opt="));
        debugMsg(radioRxMsg.OptionalInfoAvaiable);
        debugMsg(F(", RSSI="));
        debugMsg(radioRxMsg.RSSI);
        debugMsg(F(", SNR="));
        debugMsg(radioRxMsg.SNR);
        debugMsg(F(", RxTime="));
        debugMsg(radioRxMsg.RxTime);
        debugMsg(F(", MIC="));
        debugMsg(radioRxMsg.MIC);

        debugMsg(F("\n"));

    }
}


/*****************************************************************************
 * Arduino setup function
 ****************************************************************************/

void setup()
{
    // wait for the PC interface to be ready (max 10 sec); usefull for USB
    while (!PC_IF && millis() < 10000 ){}

    // init / setup the serial interface connected to WiMOD
    WIMOD_IF.begin(WIMOD_LR_BASE_PLUS_SERIAL_BAUDRATE);
    // init the communication stack
    wimod.begin();

    // debug interface
    while(!PC_IF);
    PC_IF.begin(115200);
    
    printConfigurationMsg();

    printWimdRadioConfig();

    printWimodFirmwareInfos();

    printListeningAndSendingMsg();

    // register callbacks for incommig RF messages
    wimod.RegisterUDataRxClient(onRxData);
    wimod.RegisterCDataRxClient(onRxData);

    /*****************
     * Reset the radio configuration to factory settings in order
     * to get a "clean" setup.
     *  (disable the next line if you whish to use other settings.)
     *  note: the radio settings must be the same on both peers.
     ****************/
    wimod.ResetRadioConfig();

}

void loop()
{
    // try to read a user message (non-blocking)
    debugReadData();

    // check for any pending data of the WiMOD
    wimod.Process();

    delay(500);
}

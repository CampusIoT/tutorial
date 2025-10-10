# Meshtastic

Meshtastic is an off-grid messaging system using [affortable LoRa endpoints](https://meshtastic.org/docs/hardware/devices) for building dynamic mesh networks over kilometers. LoRa endpoints (aka nodes) [forward messages to the next node](https://meshtastic.org/blog/why-meshtastic-uses-managed-flood-routing/) to distribute them over the network. Messages can be encrypted using [AES256-CTR](https://meshtastic.org/docs/overview/encryption/) expect from radio-amateur bands. Internet-connected relay nodes enable the conversation to move online too using MQTT brokers.

https://meshtastic.org


## Message Routing

When you send a message on your Meshtastic companion app, it is relayed to the radio using Bluetooth, Wi-Fi/Ethernet or serial connection. That message is then broadcasted by the radio. If it hasn't received a confirmation from any other device after a certain timeout, it will retransmit the message up to three times.

When a receiving radio captures a packet, it checks to see if it has heard that message before. If it has it ignores the message. If it hasn't heard the message, it will rebroadcast it.

For each message a radio rebroadcasts, it marks the "hop limit" down by one. When a radio receives a packet with a hop limit of zero, it will not rebroadcast the message.

The radio will store a small amount of packets (around 30) in its memory for when it's not connected to a client app. If it's full, it will replace the oldest packets with newly incoming text messages only.

Be sure to also check out this blog post about why the current protocol is used: https://meshtastic.org/blog/why-meshtastic-uses-managed-flood-routing/

While simplistic, it has been proven to be successful, e.g. at DEFCON with a mesh of over 700 nodes. Doing proper listen-before-talk with collision avoidance is already half of the work to get a mesh going.

## Physical layer

The physical layer of Meshtastic uses the LoRa modulation.

The SyncWord for Meshtastic LoRa frames is `0x2B` in order to separate the traffic with LoRaWAN endpoints (SyncWord = `0x34`)

Meshtastic adopts CSMA/CA, similar as to what is used in WiFi. This means that all transmitters must perform Channel Activity Detection (CAD). The amount of slot times to wait is randomly picked from a contention window (CW)

## Message format

![Mestastic Full Frame Format](Mestastic_Full_Frame_Format.png)

## Payload encoding

Message payloads are serialized using Protobuf. `.proto` definitions are listed [here](https://github.com/meshtastic/protobufs/tree/master/meshtastic) and documented [here](https://buf.build/meshtastic/protobufs/docs/main:meshtastic#) 

[Online proto decoder](https://map.gaulix.fr/proto-decoder)

## Payload encryption

https://meshtastic.org/docs/overview/encryption

`None`, `8 bits`, `128 bits`, `256 bits`

Message payloads can be encrypted using [AES256-CTR](https://meshtastic.org/docs/overview/encryption/).

> NB: encryption is not allowed on radio-amateur bands

## Bands in Europe

### 433 MHz

The maximum power allowed for Europe is +10 dBm ERP (Effective Radiated Power).

The band range is from 433 to 434 MHz.

There are four frequency slots defined with the standard radio preset LongFast. After factory reset the radio will be set to frequency slot 4 with a center frequency of 433.875 MHz.

### 868 MHz

The maximum power allowed for Europe is +27 dBm ERP (Effective Radiated Power).

The band range is from 869.40 to 869.65 MHz. This is less than the 863–870 MHz range defined as SRD (Short Range Devices) Band, but allows for a higher ERP and a duty cycle of 10%.

There is one frequency slot defined with the standard radio preset LongFast. After factory reset the radio will be set to frequency slot 1 with a center frequency of 869.525 MHz.

It is worth noting that 868 MHz is generally the most popular frequency band for Meshtastic in Europe.

Datarates is community-dependent

For instance: Gaulix in France (Long Moderate, Long Fast)

### 2400-2483 MHz

TODO

### Radio-amateur bands

TODO

## Supported Devices

https://meshtastic.org/docs/hardware/devices/

### @Fablab FabMaSTIC

* [WisBlock with RAK11300 RP2040 SX1262](../wisblock-rak11300-lpwan) + [RAK1910 GPS MAX-7Q](https://store.rakwireless.com/collections/wisblock-sensor/products/rak1910-max-7q-gnss-location-sensor?variant=35614325964958)
* [LILYGO T-Beam SUPREME 868 MHz](https://lilygo.cc/products/t-beam-supreme-meshtastic)
* [LILYGO T-Beam SUPREME 433 MHz](https://lilygo.cc/products/t-beam-supreme-meshtastic)
* [Seeedstudio Wio-WM1110](https://wiki.seeedstudio.com/Wio-WM/Introduction/) https://meshtastic.org/docs/hardware/devices/seeed-studio/wm1110/
* https://www.seeedstudio.com/SenseCAP-Solar-Node-P1-Pro-for-Meshtastic-LoRa-p-6412.html

## Produits distribués en France

* https://www.gotronic.fr/art-xiao-esp32s3-mash-lora-40055.htm
* https://www.gotronic.fr/art-carte-seeed-xiao-rp2350-39742.htm + [Xiao SX1262](https://www.gotronic.fr/art-shield-xiao-wio-sx1262-47632.htm)
* https://www.gotronic.fr/art-carte-xiao-esp32s3-36954.htm + [Xiao SX1262](https://www.gotronic.fr/art-shield-xiao-wio-sx1262-47632.htm)
* https://www.gotronic.fr/art-carte-xiao-ble-sense-soud--47617.htm + [Xiao SX1262](https://www.gotronic.fr/art-shield-xiao-wio-sx1262-47632.htm)
* https://www.gotronic.fr/art-sensecap-tracker-t1000-e-40059.htm
* https://www.passion-radio.fr/module/twatch-868-3044.html (la Classe à Dallas)

## Firmware

* https://github.com/meshtastic/firmware

## Flasher

* https://flasher.meshtastic.org/

Requires a compatible browser, such as Chrome or Edge for serial flashing

## Serial console

```bash
brew install tio
tio -L
tio -b 115200 -m INLCRNL /dev/tty.usbXXXXX
```

## Meshtastic Python CLI

* https://meshtastic.org/docs/software/python/cli/

### Install

```bash
pip3 install --upgrade pytap2
pip3 install --upgrade meshtastic
meshtastic --help
```

> if error `AttributeError: module 'serial' has no attribute 'Serial'` occurs :
```bash
pip uninstall serial
pip uninstall pyserial
pip3 uninstall serial
pip3 uninstall pyserial
pip3 install pyserial
```

```bash
meshtastic --help
usage: meshtastic [-h | --version | --support] [--port [PORT] | --host [HOST]
                  | --ble [BLE]] [--ble-scan] [--dest !xxxxxxxx]
                  [--ch-index INDEX] [--configure CONFIGURE]
                  [--export-config [FILE]] [--get FIELD] [--set FIELD VALUE]
                  [--begin-edit] [--commit-edit] [--get-canned-message]
                  [--set-canned-message SET_CANNED_MESSAGE] [--get-ringtone]
                  [--set-ringtone RINGTONE] [--ch-vlongslow] [--ch-longslow]
                  [--ch-longfast] [--ch-medslow] [--ch-medfast]
                  [--ch-shortslow] [--ch-shortfast] [--set-owner SET_OWNER]
                  [--set-owner-short SET_OWNER_SHORT] [--set-ham SET_HAM]
                  [--set-is-unmessageable SET_IS_UNMESSAGEABLE]
                  [--ch-set-url URL] [--ch-add-url URL] [--setalt SETALT]
                  [--setlat SETLAT] [--setlon SETLON] [--remove-position]
                  [--pos-fields [POS_FIELDS ...]] [--ch-add CH_ADD] [--ch-del]
                  [--ch-set FIELD VALUE] [--channel-fetch-attempts ATTEMPTS]
                  [--qr] [--qr-all] [--ch-enable] [--ch-disable] [--info]
                  [--nodes] [--show-fields SHOW_FIELDS] [--sendtext TEXT]
                  [--private] [--traceroute !xxxxxxxx]
                  [--request-telemetry [TYPE]] [--request-position] [--reply]
                  [--reboot | --reboot-ota | --enter-dfu | --shutdown | --device-metadata | --factory-reset | --factory-reset-device | --remove-node !xxxxxxxx | --set-favorite-node !xxxxxxxx | --remove-favorite-node !xxxxxxxx | --set-ignored-node !xxxxxxxx | --remove-ignored-node !xxxxxxxx | --reset-nodedb | --set-time [TIMESTAMP]]
                  [--seriallog [LOG_DESTINATION]] [--ack] [--timeout SECONDS]
                  [--no-nodes] [--debug] [--test]
                  [--wait-to-disconnect [SECONDS]] [--noproto] [--listen]
                  [--no-time]
                  [--power-riden POWER_RIDEN | --power-ppk2-meter | --power-ppk2-supply | --power-sim]
                  [--power-voltage POWER_VOLTAGE] [--power-stress]
                  [--power-wait] [--slog [SLOG]]
                  [--gpio-wrb GPIO_WRB GPIO_WRB] [--gpio-rd GPIO_RD]
                  [--gpio-watch GPIO_WATCH]

Help:
  -h, --help            show this help message and exit
  --version             show program's version number and exit
  --support             Show support info (useful when troubleshooting an
                        issue)

Connection:
  Optional arguments that specify how to connect to a Meshtastic device.

  --port [PORT], --serial [PORT], -s [PORT]
                        The port of the device to connect to using serial,
                        e.g. /dev/ttyUSB0. (defaults to trying to detect a
                        port)
  --host [HOST], --tcp [HOST], -t [HOST]
                        Connect to a device using TCP, optionally passing
                        hostname or IP address to use. (defaults to
                        'localhost')
  --ble [BLE], -b [BLE]
                        Connect to a BLE device, optionally specifying a
                        device name (defaults to 'any')
  --ble-scan            Scan for Meshtastic BLE devices that may be available
                        to connect to

Selection:
  Arguments that select channels to use, destination nodes, etc.

  --dest !xxxxxxxx      The destination node id for any sent commands. If not
                        set '^all' or '^local' is assumed.Use the node ID with
                        a '!' or '0x' prefix or the node number.
  --ch-index INDEX      Set the specified channel index for channel-specific
                        commands. Channels start at 0 (0 is the PRIMARY
                        channel).

Import/Export:
  Arguments that concern importing and exporting configuration of Meshtastic
  devices

  --configure CONFIGURE
                        Specify a path to a yaml(.yml) file containing the
                        desired settings for the connected device.
  --export-config [FILE]
                        Export device config as YAML (to stdout if no file
                        given)

Configuration:
  Arguments that concern general configuration of Meshtastic devices

  --get FIELD           Get a preferences field. Use an invalid field such as
                        '0' to get a list of all fields. Can use either
                        snake_case or camelCase format. (ex: 'power.ls_secs'
                        or 'power.lsSecs')
  --set FIELD VALUE     Set a preferences field. Can use either snake_case or
                        camelCase format. (ex: 'power.ls_secs' or
                        'power.lsSecs'). May be less reliable when setting
                        properties from more than one configuration section.
  --begin-edit          Tell the node to open a transaction to edit settings
  --commit-edit         Tell the node to commit open settings transaction
  --get-canned-message  Show the canned message plugin message
  --set-canned-message SET_CANNED_MESSAGE
                        Set the canned messages plugin message (up to 200
                        characters).
  --get-ringtone        Show the stored ringtone
  --set-ringtone RINGTONE
                        Set the Notification Ringtone (up to 230 characters).
  --ch-vlongslow        Change to the very long-range and slow modem preset
  --ch-longslow         Change to the long-range and slow modem preset
  --ch-longfast         Change to the long-range and fast modem preset
  --ch-medslow          Change to the med-range and slow modem preset
  --ch-medfast          Change to the med-range and fast modem preset
  --ch-shortslow        Change to the short-range and slow modem preset
  --ch-shortfast        Change to the short-range and fast modem preset
  --set-owner SET_OWNER
                        Set device owner name
  --set-owner-short SET_OWNER_SHORT
                        Set device owner short name
  --set-ham SET_HAM     Set licensed Ham ID and turn off encryption
  --set-is-unmessageable SET_IS_UNMESSAGEABLE, --set-is-unmessagable SET_IS_UNMESSAGEABLE
                        Set if a node is messageable or not
  --ch-set-url URL, --seturl URL
                        Set all channels and set LoRa config from a supplied
                        URL
  --ch-add-url URL      Add secondary channels and set LoRa config from a
                        supplied URL

Position Configuration:
  Arguments that modify fixed position and other position-related
  configuration.

  --setalt SETALT       Set device altitude in meters (allows use without
                        GPS), and enable fixed position. When providing
                        positions with `--setlat`, `--setlon`, and `--setalt`,
                        missing values will be set to 0.
  --setlat SETLAT       Set device latitude (allows use without GPS), and
                        enable fixed position. Accepts a decimal value or an
                        integer premultiplied by 1e7. When providing positions
                        with `--setlat`, `--setlon`, and `--setalt`, missing
                        values will be set to 0.
  --setlon SETLON       Set device longitude (allows use without GPS), and
                        enable fixed position. Accepts a decimal value or an
                        integer premultiplied by 1e7. When providing positions
                        with `--setlat`, `--setlon`, and `--setalt`, missing
                        values will be set to 0.
  --remove-position     Clear any existing fixed position and disable fixed
                        position.
  --pos-fields [POS_FIELDS ...]
                        Specify fields to send when sending a position. Use no
                        argument for a list of valid values. Can pass multiple
                        values as a space separated list like this: '--pos-
                        fields ALTITUDE HEADING SPEED'

Channel Configuration:
  Arguments that concern configuration of channels

  --ch-add CH_ADD       Add a secondary channel, you must specify a channel
                        name
  --ch-del              Delete the ch-index channel
  --ch-set FIELD VALUE  Set a channel parameter. To see channel settings
                        available:'--ch-set all all --ch-index 0'. Can set the
                        'psk' using this command. To disable encryption on
                        primary channel:'--ch-set psk none --ch-index 0'. To
                        set encryption with a new random key on second
                        channel:'--ch-set psk random --ch-index 1'. To set
                        encryption back to the default:'--ch-set psk default
                        --ch-index 0'. To set encryption with your own key: '
                        --ch-set psk 0x1a1a1a1a2b2b2b2b1a1a1a1a2b2b2b2b1a1a1a1
                        a2b2b2b2b1a1a1a1a2b2b2b2b --ch-index 0'.
  --channel-fetch-attempts ATTEMPTS
                        Attempt to retrieve channel settings for --ch-set this
                        many times before giving up. Default 3.
  --qr                  Display a QR code for the node's primary channel (or
                        all channels with --qr-all). Also shows the shareable
                        channel URL.
  --qr-all              Display a QR code and URL for all of the node's
                        channels.
  --ch-enable           Enable the specified channel. Use --ch-add instead
                        whenever possible.
  --ch-disable          Disable the specified channel Use --ch-del instead
                        whenever possible.

Local Actions:
  Arguments that take actions or request information from the local node
  only.

  --info                Read and display the radio config information
  --nodes               Print Node List in a pretty formatted table
  --show-fields SHOW_FIELDS
                        Specify fields to show (comma-separated) when using
                        --nodes

Remote Actions:
  Arguments that take actions or request information from either the local
  node or remote nodes via the mesh.

  --sendtext TEXT       Send a text message. Can specify a destination '--
                        dest', use of PRIVATE_APP port '--private', and/or
                        channel index '--ch-index'.
  --private             Optional argument for sending text messages to the
                        PRIVATE_APP port. Use in combination with --sendtext.
  --traceroute !xxxxxxxx
                        Traceroute from connected node to a destination. You
                        need pass the destination ID as argument, like this: '
                        --traceroute !ba4bf9d0' | '--traceroute
                        0xba4bf9d0'Only nodes with a shared channel can be
                        traced.
  --request-telemetry [TYPE]
                        Request telemetry from a node. With an argument,
                        requests that specific type of telemetry. You need to
                        pass the destination ID as argument with '--dest'. For
                        repeaters, the nodeNum is required.
  --request-position    Request the position from a node. You need to pass the
                        destination ID as an argument with '--dest'. For
                        repeaters, the nodeNum is required.
  --reply               Reply to received messages

Remote Admin Actions:
  Arguments that interact with local node or remote nodes via the mesh,
  requiring admin access.

  --reboot              Tell the destination node to reboot
  --reboot-ota          Tell the destination node to reboot into factory
                        firmware (ESP32)
  --enter-dfu           Tell the destination node to enter DFU mode (NRF52)
  --shutdown            Tell the destination node to shutdown
  --device-metadata     Get the device metadata from the node
  --factory-reset, --factory-reset-config
                        Tell the destination node to install the default
                        config, preserving BLE bonds & PKI keys
  --factory-reset-device
                        Tell the destination node to install the default
                        config and clear BLE bonds & PKI keys
  --remove-node !xxxxxxxx
                        Tell the destination node to remove a specific node
                        from its NodeDB. Use the node ID with a '!' or '0x'
                        prefix or the node number.
  --set-favorite-node !xxxxxxxx
                        Tell the destination node to set the specified node to
                        be favorited on the NodeDB. Use the node ID with a '!'
                        or '0x' prefix or the node number.
  --remove-favorite-node !xxxxxxxx
                        Tell the destination node to set the specified node to
                        be un-favorited on the NodeDB. Use the node ID with a
                        '!' or '0x' prefix or the node number.
  --set-ignored-node !xxxxxxxx
                        Tell the destination node to set the specified node to
                        be ignored on the NodeDB. Use the node ID with a '!'
                        or '0x' prefix or the node number.
  --remove-ignored-node !xxxxxxxx
                        Tell the destination node to set the specified node to
                        be un-ignored on the NodeDB. Use the node ID with a
                        '!' or '0x' prefix or the node number.
  --reset-nodedb        Tell the destination node to clear its list of nodes
  --set-time [TIMESTAMP]
                        Set the time to the provided unix epoch timestamp, or
                        the system's current time if omitted or 0.

Miscellaneous arguments:
  --seriallog [LOG_DESTINATION]
                        Log device serial output to either 'none' or a
                        filename to append to. Defaults to 'stdout' if no
                        filename specified.
  --ack                 Use in combination with compatible actions (e.g.
                        --sendtext) to wait for an acknowledgment.
  --timeout SECONDS     How long to wait for replies. Default 300s.
  --no-nodes            Request that the node not send node info to the
                        client. Will break things that depend on the nodedb,
                        but will speed up startup. Requires 2.3.11+ firmware.
  --debug               Show API library debug log messages
  --test                Run stress test against all connected Meshtastic
                        devices
  --wait-to-disconnect [SECONDS]
                        How many seconds to wait before disconnecting from the
                        device.
  --noproto             Don't start the API, just function as a dumb serial
                        terminal.
  --listen              Just stay open and listen to the protobuf stream.
                        Enables debug logging.
  --no-time             Deprecated. Retained for backwards compatibility in
                        scripts, but is a no-op.

Power Testing:
  Options for power testing/logging.

  --power-riden POWER_RIDEN
                        Talk to a Riden power-supply. You must specify the
                        device path, i.e. /dev/ttyUSBxxx
  --power-ppk2-meter    Talk to a Nordic Power Profiler Kit 2 (in meter mode)
  --power-ppk2-supply   Talk to a Nordic Power Profiler Kit 2 (in supply mode)
  --power-sim           Use a simulated power meter (for development)
  --power-voltage POWER_VOLTAGE
                        Set the specified voltage on the power-supply. Be VERY
                        careful, you can burn things up.
  --power-stress        Perform power monitor stress testing, to capture a
                        power consumption profile for the device (also
                        requires --power-mon)
  --power-wait          Prompt the user to wait for device reset before
                        looking for device serial ports (some boards kill
                        power to USB serial port)
  --slog [SLOG]         Store structured-logs (slogs) for this run, optionally
                        you can specify a destination directory

Remote Hardware:
  Arguments related to the Remote Hardware module

  --gpio-wrb GPIO_WRB GPIO_WRB
                        Set a particular GPIO # to 1 or 0
  --gpio-rd GPIO_RD     Read from a GPIO mask (ex: '0x10')
  --gpio-watch GPIO_WATCH
                        Start watching a GPIO mask for changes (ex: '0x10')

If no connection arguments are specified, we search for a compatible serial
device, and if none is found, then attempt a TCP connection to localhost.
```




### Serial

> `--seriallog` into the command line enables to trace the program during the execution of the console

```bash
ls -al /dev/tty.*
PORT=/dev/ttyUSB0
PORT=/dev/tty.usbmodem48CA435B98B41
meshtastic --port $PORT --info

meshtastic --export-config --port $PORT > example_config.yaml

meshtastic --port /dev/ttyUSB0 --seriallog

meshtastic -t meshtastic.local --seriallog log.txt
```


### [CLI thru BLE](https://meshtastic.org/docs/software/python/cli/usage/#utilizing-ble-via-the-python-cli)

```bash
meshtastic --ble-scan
```

```
INFO file:ble_interface.py scan line:127 Scanning for BLE devices (takes 10 seconds)...
Found: name='LIG1_230f' address='XXXX-7BC9-4A3F-D452-XXXX'
BLE scan finished
```

```bash
BLENAME=LIG1_230f
BLEADDRESS=XXXX-7BC9-4A3F-D452-XXXX
meshtastic --ble $BLENAME --info
meshtastic --ble $BLENAME --info > $BLENAME.config.txt
cat $BLENAME.config.txt
meshtastic --ble $BLENAME --export-config > $BLENAME.config.yml
cat $BLENAME.config.yml
meshtastic --ble $BLEADDRESS --nodes
```

### Remote Admin

https://meshtastic.org/docs/configuration/remote-admin/

```bash
meshtastic --set security.admin_key "base64:PASTEPUBLICKEYHERE"
```


### Configuration

set a node at a fixed position and never power up the GPS.
```bash
meshtastic --setlat 45.19025 --setlon 5.7674068 --setalt 240
```
```console
Connected to radio
Fixing altitude at 240 meters
Fixing latitude at 45.19025 degrees
Fixing longitude at 5.7674068 degrees
Setting device position and enabling fixed position setting
```



set a ringtone
```bash
meshtastic --set-ringtone "LeisureSuit:d=16,o=6,b=56:f.5,f#.5,g.5,g#5,32a#5,f5,g#.5,a#.5,32f5,g#5,32a#5,g#5,8c#.,a#5,32c#,a5,a#.5,c#.,32a5,a#5,32c#,d#,8e,c#.,f.,f.,f.,f.,f,32e,d#,8d,a#.5,e,32f,e,32f,c#,d#.,c#"
```

### Config a batch of boards

* https://meshtastic.org/docs/software/python/cli/
* meshtastic.org/docs/configuration/radio/channels/
* https://meshtastic.org/docs/configuration/radio/lora/

```bash
# https://meshtastic.org/docs/software/python/cli/
# meshtastic.org/docs/configuration/radio/channels/
# https://meshtastic.org/docs/configuration/radio/lora/

meshtastic_config_owner(){
OWNER=$1
meshtastic \
--set-owner 38GRENLM8ClN_CS$OWNER \
--set-owner-short CS$OWNER \
--seriallog
meshtastic --info  --seriallog | grep CS$OWNER
}

meshtastic_config_location(){
meshtastic \
--setlat 45.19373 --setlon 5.76514 --setalt 220 \
--seriallog
meshtastic --info  --seriallog | grep 45.19373
}

meshtastic_config_radio(){
meshtastic \
--set lora.region EU_868 \
--set lora.modem_preset LONG_MODERATE \
--seriallog
meshtastic --info  --seriallog | grep LONG_MODERATE
# meshtastic --set lora.override_duty_cycle true
# meshtastic --set lora.hop_limit 2
}

meshtastic_config_channels(){
meshtastic --ch-set name "Fr_Balise" --ch-set psk default --ch-set uplink_enabled true --ch-index 0  --seriallog
meshtastic --ch-set name "Fr_EMCOM" --ch-set psk default --ch-set uplink_enabled true --ch-index 1  --seriallog
meshtastic --ch-set name "Fr_BlaBla" --ch-set psk default --ch-set uplink_enabled true --ch-index 2  --seriallog
meshtastic --ch-set name "Fr_Tech" --ch-set psk default --ch-set uplink_enabled true --ch-index 3  --seriallog
meshtastic --ch-set name "JNR2025" --ch-set psk default --ch-set uplink_enabled true --ch-index 4  --seriallog
}

meshtastic_info(){
meshtastic --info  --seriallog
}

meshtastic_config() {
OWNER=$1
meshtastic_config_owner $OWNER
meshtastic_config_location
sleep 2
meshtastic_config_radio
sleep 2
meshtastic_config_channels
sleep 2
meshtastic_info
}

meshtastic_config 31
...
meshtastic_config 44

```

### Stress test

```bash
meshtastic --test  --seriallog
```
```console
INFO file:test.py openDebugLog line:152 Writing serial debugging to log_dev_cu.usbserial-110
INFO file:test.py openDebugLog line:152 Writing serial debugging to log_dev_cu.usbserial-140
Connection changed: meshtastic.connection.established
INFO file:test.py testAll line:181 Ports opened, starting test
INFO file:test.py testThread line:135 Found devices, starting tests...
INFO file:test.py runTests line:102 Running 5 tests with wantAck=True
Connection changed: meshtastic.connection.established
INFO file:test.py runTests line:121 Test 1 succeeded 1 successes 0 failures so far
INFO file:test.py runTests line:121 Test 2 succeeded 2 successes 0 failures so far
INFO file:test.py runTests line:121 Test 3 succeeded 3 successes 0 failures so far
INFO file:test.py runTests line:121 Test 4 succeeded 4 successes 0 failures so far
INFO file:test.py runTests line:121 Test 5 succeeded 5 successes 0 failures so far
INFO file:test.py runTests line:102 Running 5 tests with wantAck=False
INFO file:test.py runTests line:121 Test 6 succeeded 1 successes 0 failures so far
INFO file:test.py runTests line:121 Test 7 succeeded 2 successes 0 failures so far
INFO file:test.py runTests line:121 Test 8 succeeded 3 successes 0 failures so far
INFO file:test.py runTests line:121 Test 9 succeeded 4 successes 0 failures so far
INFO file:test.py runTests line:121 Test 10 succeeded 5 successes 0 failures so far
Connection changed: meshtastic.connection.lost
Connection changed: meshtastic.connection.lost
Test was a success.
```




## Meshtastic Web

[Meshtastic Web](https://client.meshtastic.org/) is a Meshtastic client that runs directly in your browser (Chrome). There are three ways of accessing the app: Served directly from an ESP32 based node via meshtastic.local or the device's IP Address.

https://github.com/lyusupov/SoftRF/wiki/Prime-Edition-MkIII#quick-start

## Integrations

### MQTT


### NodeRED

https://meshtastic.org/docs/software/integrations/mqtt/nodered/


## Misc

### WebClient

https://client.meshtastic.org/

Self hosting https://github.com/meshtastic/web

```bash
docker run -d -p 8080:8080 --restart always --name Meshtastic-Web ghcr.io/meshtastic/web
```

> Remark: Refresh the console after rebooting the node

### Meshtastic site planner

https://site.meshtastic.org/

### Mesh-metrics

https://github.com/cordelster/mesh-metrics

### Meshtastic routing simulator (Discrete Event)

https://github.com/meshtastic/Meshtasticator

### Meshtastic network visualization

https://github.com/filipsPL/meshtastic-network-visualization/

### meshtastic-map

https://github.com/liamcottle/meshtastic-map

```bash
MQTT_BROKER=mqtt.meshtastic.org
MQTT_PORT=8883
MQTT_USERNAME=meshdev
MQTT_PASSWORD=large4cats
TOPIC="msh/#"
  
mqtt subscribe -v -h $MQTT_BROKER -p 1883  $TOPIC

mqtt subscribe --insecure -v -h $MQTT_BROKER -p $MQTT_PORT -u $MQTT_USERNAME -P $MQTT_PASSWORD -l mqtts $TOPIC

mqtt subscribe -v -h $MQTT_BROKER -p $MQTT_PORT -u $MQTT_USERNAME -P $MQTT_PASSWORD  $TOPIC
```

## Communities

### Gaulix (France)

#### Map

https://map.gaulix.fr/

#### MQTT

https://map.gaulix.fr/channel/6/messages

https://gaulix.fr/1100-mqtt-config-v25x/

## Glossary

* ATAK : [Android Tactical Awareness Kit](https://en.wikipedia.org/wiki/Android_Team_Awareness_Kit) ([more ...](https://freetakteam.github.io/FreeTAKServer-User-Docs/)), [Comparing Meshtastic, Beartooth MkII, and goTenna Pro Radios for ATAK (video)](https://www.youtube.com/watch?v=b8bVSwhYt8U)
* CoT : [Cursor on Target](https://pmc.ncbi.nlm.nih.gov/articles/PMC3615829/)

## Projects @ UGA

* https://gricad-gitlab.univ-grenoble-alpes.fr/Projets-INFO4/24-25/18/docs
* https://gricad-gitlab.univ-grenoble-alpes.fr/thingsat/public/-/blob/master/balloons/2025-05/README.md

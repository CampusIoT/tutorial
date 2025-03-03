# LPP Cayenne decoding / encoding

Cayenne Low Power Payload is a format for encoding and decoding sensor measurements in message payloads for the Internet of Things.

The format is a sequence of tuples &lt;`channel`, `type`, `value`&gt;:

* `channel` : size is 1 byte
* `type`: [type of the data value](https://docs.mydevices.com/docs/lorawan/cayenne-lpp#data-types) (temperature, analog, gps location, accelerometer ...). The size is 1 byte.
* `value` : size depends of `type`

This format can be used for encoding commands (digital input, analog input).

## Node.JS

```bash
npm i @crapougnax/cayennelpp
node decode.js 006700E20002015C
```

```json
{
  "0": {
    "temperature": 22.6,
    "analog": 3.48
  }
}
```

## Python

TODO

* https://github.com/jojo-/py-cayenne-lpp
* https://github.com/smlng/pycayennelpp

## C/C++

TODO

* RIOT OS https://api.riot-os.org/group__pkg__cayenne-lpp.html
* Arduino https://github.com/ElectronicCats/CayenneLPP

## RUST

TODO

* https://github.com/Octoate/CayenneLPP-rs
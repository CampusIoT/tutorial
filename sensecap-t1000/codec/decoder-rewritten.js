// WIP Didier DONSEZ 08/04/2026
// Origin https://raw.githubusercontent.com/Seeed-Solution/SenseCAP-Decoder/refs/heads/main/T1000/TTN/SenseCAP_T1000E_TTN_Decoder.js

// https://github.com/CampusIoT/payload-codec/blob/master/src/main/ttn_chirpstack/buf.js

// Javascript functions for décoding and encoding the frame payloads
// From https://github.com/feross/buffer/blob/master/index.js

function readUInt16LE(buf, offset) {
    offset = offset >>> 0;
    return buf[offset] | (buf[offset + 1] << 8);
}

function readUInt16BE(buf, offset) {
    offset = offset >>> 0;
    return (buf[offset] << 8) | buf[offset + 1];
}

function readInt16LE(buf, offset) {
    offset = offset >>> 0;
    var val = buf[offset] | (buf[offset + 1] << 8);
    return (val & 0x8000) ? val | 0xFFFF0000 : val;
}

function readInt16BE(buf, offset) {
    offset = offset >>> 0;
    var val = buf[offset + 1] | (buf[offset] << 8);
    return (val & 0x8000) ? val | 0xFFFF0000 : val;
}

function readUInt32LE(buf, offset) {
    offset = offset >>> 0;

    return ((buf[offset]) |
        (buf[offset + 1] << 8) |
        (buf[offset + 2] << 16)) +
        (buf[offset + 3] * 0x1000000);
}

function readUInt32BE(buf, offset) {
    offset = offset >>> 0;

    return (buf[offset] * 0x1000000) +
        ((buf[offset + 1] << 16) |
            (buf[offset + 2] << 8) |
            buf[offset + 3]);
}

function readIntLE(buf, offset, byteLength) {
    offset = offset >>> 0;
    byteLength = byteLength >>> 0;

    var val = buf[offset];
    var mul = 1;
    var i = 0;
    while (++i < byteLength && (mul *= 0x100)) {
        val += buf[offset + i] * mul;
    }
    mul *= 0x80;

    if (val >= mul) val -= Math.pow(2, 8 * byteLength);

    return val;
}

function readIntBE(buf, offset, byteLength) {
    offset = offset >>> 0;
    byteLength = byteLength >>> 0;

    var i = byteLength;
    var mul = 1;
    var val = buf[offset + --i];
    while (i > 0 && (mul *= 0x100)) {
        val += buf[offset + --i] * mul;
    }
    mul *= 0x80;

    if (val >= mul) val -= Math.pow(2, 8 * byteLength);

    return val;
}

function readInt8(buf, offset) {
    offset = offset >>> 0;
    if (!(buf[offset] & 0x80)) return (buf[offset]);
    return ((0xff - buf[offset] + 1) * -1);
}

function readUInt8(buf, offset) {
    offset = offset >>> 0;
    return (buf[offset]);
}


/*
*  Usage: decodeFloat32(readUInt32BE (buf, offset))
*/
function decodeFloat32(bytes) {
    var sign = (bytes & 0x80000000) ? -1 : 1;
    var exponent = ((bytes >> 23) & 0xFF) - 127;
    var significand = (bytes & ~(-1 << 23));

    if (exponent == 128)
        return sign * ((significand) ? Number.NaN : Number.POSITIVE_INFINITY);

    if (exponent == -127) {
        if (significand == 0) return sign * 0.0;
        exponent = -126;
        significand /= (1 << 22);
    } else significand = (significand | (1 << 23)) / (1 << 23);

    return sign * significand * Math.pow(2, exponent);
}

// For debug
function bytes2HexString(arrBytes) {
    var str = ''
    for (var i = 0; i < arrBytes.length; i++) {
        var tmp
        var num = arrBytes[i]
        if (num < 0) {
            tmp = (255 + num + 1).toString(16)
        } else {
            tmp = num.toString(16)
        }
        if (tmp.length === 1) {
            tmp = '0' + tmp
        }
        str += tmp
    }
    return str
}


// Sensor


function getBattery(buf, idx) {
    return readUInt8(buf, idx);
}

// dig can be integer or float
function getSensorValue(buf, idx, dig) {
    var value = readUInt16BE(buf, idx);
    if (value === 0x8000) {
        return null;
    } else {
        if (dig === 1) {
            return value;
        } else {
            return value / dig;
        }
    }
}

function getSignSensorValue(buf, idx, dig) {
    var value = readInt16BE(buf, idx);
    if (dig === 1) {
        return value;
    } else {
        return value / dig;
    }
}

function getEventStatus(status) {
    var event = []
    if ((status & 0x01) === 0x01) {
        event.push({ id: 1, eventName: "Start moving event." })
    }
    if ((status & 0x02) === 0x02) {
        event.push({ id: 2, eventName: "End movement event." })
    }
    if ((status & 0x04) === 0x04) {
        event.push({ id: 3, eventName: "Motionless event." })
    }
    if ((status & 0x08) === 0x08) {
        event.push({ id: 4, eventName: "Shock event." })
    }
    if ((status & 0x10) === 0x10) {
        event.push({ id: 5, eventName: "Temperature event." })
    }
    if ((status & 0x20) === 0x20) {
        event.push({ id: 6, eventName: "Light event." })
    }
    if ((status & 0x40) === 0x40) {
        event.push({ id: 7, eventName: "SOS event." })
    }
    if ((status & 0x80) === 0x80) {
        event.push({ id: 8, eventName: "Press once event." })
    }
    return event
}

function getT1000EUplinkHeader(dataValue, idx, collectTime) {

    var measurementArray = []

    // Event at 0 size 1
    var eventList = getEventStatus(dataValue[idx])
    measurementArray.push({
        measurementId: '5003',
        measureTime: collectTime,
        value: eventList
    })

    // 3000 at 1 size 1
    measurementArray.push({
        measurementId: '3000',
        measureTime: collectTime,
        value: getBattery(dataValue, idx + 1)
    })
    return measurementArray
}

function getT1000EUplinkHeaderWithSensor(dataValue, idx, collectTime) {

    // Uplink Sensor @ 0 size 2
    var measurementArray = getT1000EUplinkHeader(dataValue, idx, collectTime)

    //  Sensor 4097 @ 2 size 2 (divisor 10)
    measurementArray.push({
        measurementId: '4097',
        measureTime: collectTime,
        value: getSensorValue(dataValue, idx + 1, 10.0)
    })
    //  Sensor 4199 @ 2 size 2
    measurementArray.push({
        measurementId: '4199',
        measureTime: collectTime,
        value: getSensorValue(dataValue, idx + 4, 1)
    })
    return measurementArray
}

function getT1000EUplinkHeaderWithSensorAnd3Axis(dataValue, idx, collectTime) {

    // Uplink Sensor @ 0 size 6
    var measurementArray = getT1000EUplinkHeaderWithSensor(dataValue, idx, collectTime)

    // SignSensor 4210 @ 6 size 2
    var value = getSignSensorValue(dataValue, idx + 6, 1)
    if (value !== null) {
        measurementArray.push({
            measurementId: '4210',
            measureTime: collectTime,
            value: value
        })
    }
    // SignSensor 4211 @ 8 size 2
    alue = getSignSensorValue(dataValue, idx + 8, 1)
    if (value !== null) {
        measurementArray.push({
            measurementId: '4211',
            measureTime: collectTime,
            value: value
        })
    }
    // SignSensor 4212 @ 10 size 2
    alue = getSignSensorValue(dataValue, idx + 10, 1)
    if (value !== null) {
        measurementArray.push({
            measurementId: '4212',
            measureTime: collectTime,
            value: value
        })
    }
    return measurementArray
}


// Decode decodes an array in bytes into an object.
//  - fPort contains the LoRaWAN fPort number
//  - bytes is an array in bytes, e.g. [225, 230, 255, 0]
//  - variables contains the device variables e.g. {"calibration": "3.5"} (both the key / value are in type string)
// The function must return an object, e.g. {"temperature": 22.5}
function Decode(fPort, bytes, variables) {
    var fport = fPort;
    var bytesString = bytes2HexString(bytes).toLocaleUpperCase();
    var originMessage = bytesString.toLocaleUpperCase();
    var decoded = {
        valid: true,
        err: 0,
        payload: bytesString,
        debug: bytesString.toLocaleUpperCase(),
        messages: []
    }

    decoded.messages.push({ fport: fport, payload: bytesString })


    var measurementArray = []
    var collectTime = (new Date()).getTime() / 1000

    var idx = 0;
    if (bytes[idx] == 0x20) {
        var messageLen = 16;
        if (idx + messageLen <= bytes.length) {
            measurementArray = getT1000EUplinkHeaderWithSensorAnd3Axis(bytes, idx + 1, collectTime)
            /*
                scanMax = readInt8(idx+12)
            if (!scanMax || scanMax === 0) {
                break
            }
            */
           /*
            measurementArray.push({
                measurementId: '5001',
                measureTime: collectTime,
                value: getMacAndRssiObj(dataValue.substring(26))
            });
            */
        }

    }

    decoded.messages.push(measurementArray);

    return { data: decoded }
}

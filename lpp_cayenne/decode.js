/**
 * Simple CLI for decoding LPP Cayenne payload
 * Author: Didier DONSEZ, 2025
 */

const cayennelpp = require('@crapougnax/cayennelpp');

let str = process.argv[2];

let buf = Buffer.from(str, "hex");
const decoder = new cayennelpp.LPPDecoder(buf)
decoder.decode();
console.log(JSON.stringify(decoder.channels,undefined,2));

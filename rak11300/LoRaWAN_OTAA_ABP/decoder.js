// Author: Didier DONSEZ

// For Chirpstack v3.x
// Decode decodes an array of bytes into an object.
//  - fPort contains the LoRaWAN fPort number
//  - bytes is an array of bytes, e.g. [225, 230, 255, 0]
//  - variables contains the device variables e.g. {"calibration": "3.5"} (both the key / value are of type string)
// The function must return an object, e.g. {"temperature": 22.5}
function Decode(fPort, bytes, variables) {
  	var result = "";
	for(var i = 0; i < bytes.length; ++i){
		result+= (String.fromCharCode(bytes[i]));
	}
	var decoded = { text: result };
  	return decoded;
}

// For LNS compliant with TS013-1.0.0 Payload Codec API
// https://resources.lora-alliance.org/technical-specifications/ts013-1-0-0-payload-codec-api
function decodeUplink(input){
  return{
    data: Decode(input.fPort, input.bytes, input.variables)
  };
}


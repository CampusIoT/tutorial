function readInt16BE (buf, offset) {
    offset = offset >>> 0
    var val = buf[offset + 1] | (buf[offset] << 8)
    return (val & 0x8000) ? val | 0xFFFF0000 : val
  }

// For Helium et TTNv2
function Decode(fPort, bytes, variables) {
      var o = {};  
      o.co = readInt16BE(bytes,0);
      o.c2h5ch = readInt16BE(bytes,2);
      o.no2 = readInt16BE(bytes,4);
      o.voc = readInt16BE(bytes,6);
    
        return o;
}

// For Helium et TTNv2
function Decoder(bytes, fPort) {
    return Decode(fPort, bytes, undefined);
}

// For  TTNv3 TODO

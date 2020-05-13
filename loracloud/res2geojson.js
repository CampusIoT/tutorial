// Copyright 2020, Université Grenoble Alpes, LIG, ERODS

// Author : Didier DONSEZ

// TODO List
// [ ] add line between point and gateways
// [ ] add metrics into gateways properties (flight time, rssi, ...) for futur popups
// [ ] remove the gateways which are not into the frames

var fs = require('fs');

var frames = JSON.parse(fs.readFileSync(process.argv[2], 'utf8'));
var result = JSON.parse(fs.readFileSync(process.argv[3], 'utf8'));

var features = [];

frames.gateways.forEach(g => {

    // TODO remove the gateways which are not into the frames

    features.push({
        "type": "Feature",
        "properties": {
          "marker-color": "#0432ff",
          "marker-size": "medium",
          "marker-symbol": "circle",
          "gatewayId": g.gatewayId,
          "altitude": g.altitude
        },
        "geometry": {
          "type": "Point",
          "coordinates": [
            g.longitude,
            g.latitude
          ]
        }
      });
});

result.result.forEach(r => {
    features.push({
    "type": "Feature",
    "properties": {
      "marker-color": "#ff2600",
      "marker-size": "medium",
      "marker-symbol": "",
      "numUsedGateways": r.numUsedGateways,
      "toleranceHoriz": r.locationEst.toleranceHoriz,
      "HDOP": r.HDOP,
      "algorithmType": r.algorithmType

    },
    "geometry": {
      "type": "Point",
      "coordinates": [
        r.locationEst.longitude,
        r.locationEst.latitude
      ]
    }
  });
});

var geojson = {
    "type": "FeatureCollection",
    "features": features
}

console.log(JSON.stringify(geojson,null,2));

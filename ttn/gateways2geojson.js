#!/usr/bin/env node

// Reads the JSON representation of the TTN gateways from stdin
// and writes the GeoJSON representation on stdout.
// GeoJSON can be vizualized with http://geojson.io

// Author: Didier DONSEZ, 2020.

const DEFAULT_PLACEMENT_COLOR = "#fefb00"; // yellow (as default color)
const INDOOR_PLACEMENT_COLOR = "#ff2600"; // red
const OUTDOOR_PLACEMENT_COLOR = "#0432ff"; // blue
const MARKER_SYMBOL = "marker";

var stdin = process.stdin,
    stdout = process.stdout,
    inputChunks = [];

stdin.resume();
stdin.setEncoding('utf8');

stdin.on('data', function (chunk) {
    inputChunks.push(chunk);
});

var geojson = {
    "type": "FeatureCollection",
    "features": [
    ]
  };

stdin.on('end', function () {
    var inputJSON = inputChunks.join(),
        gateways = JSON.parse(inputJSON);
        
        Object.keys(gateways).forEach(function(key,index) {
            var g = gateways[key];
            var location = g.location;
            var attributes = g.attributes;

            if(location) {
                var feature =       {
                    "type": "Feature",
                    "properties": {
                        "marker-color": DEFAULT_PLACEMENT_COLOR,
                        "marker-size": "medium",
                        "marker-symbol": MARKER_SYMBOL,
                        "id": g.id,
                        "owner": g.owner,
                        "description": g.description
                    },
                    "geometry": {
                    "type": "Point",
                    "coordinates": [
                        location.longitude,
                        location.latitude
                    ]
                    }
                };
                var properties = feature.properties;

                if(attributes) {
                    if(attributes.brand) {
                        properties.brand = attributes.brand;
                    }
                    if(attributes.frequency_plan) {
                        properties.frequency_plan = attributes.frequency_plan;
                    }
                    if(attributes.model) {
                        properties.model = attributes.model;
                    }
                    if(attributes.antenna_model) {
                        properties.antenna_model = attributes.antenna_model;
                    }
                    if(attributes.version) {
                        properties.version = attributes.version;
                    }              
                    if(attributes.placement) {
                        properties.placement = attributes.placement;
                        if(attributes.placement === "outdoor") {
                            properties["marker-color"] = OUTDOOR_PLACEMENT_COLOR;
                        } else if(attributes.placement === "indoor") {
                            properties["marker-color"] = INDOOR_PLACEMENT_COLOR;
                        }
                    }
                    if(g.last_seen) {
                        properties.last_seen = g.last_seen;
                    }
                }

                if(location.altitude) {
                    properties.altitude = location.altitude;
                }

                geojson.features.push(feature);  
            }   
        });
 
    stdout.write(JSON.stringify(geojson, null, 2));
    stdout.write('\n');
});

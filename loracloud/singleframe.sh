#!/bin/bash

if [ -z ${GLS_TOKEN+x} ]; then echo "The variable GLS_TOKEN should be set and exported"; else echo "GLS_TOKEN is set to '$GLS_TOKEN'"; fi

SRVURI=https://mgs.loracloud.com

curl -k --request POST -H "Ocp-Apim-Subscription-Key: $GLS_TOKEN" \
     -H "Content-Type: application/json" -d @singleframe.json \
     $SRVURI/api/v3/solve/singleframe

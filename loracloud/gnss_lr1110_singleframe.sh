
SRVURI=https://gls.loracloud.com
TOKEN="YOUR TOKEN"

curl -k --request POST -H "Ocp-Apim-Subscription-Key: $TOKEN" \
     -H "Content-Type: application/json" -d @gnss_lr1110_singleframe.json \
     $SRVURI/api/v3/solve/gnss_lr1110_singleframe



SRVURI=https://gls.loracloud.com
TOKEN="YOUR_TOKEN"

curl -k --request POST -H "Ocp-Apim-Subscription-Key: $TOKEN" \
     -H "Content-Type: application/json" -d @multiframes.json \
     $SRVURI/api/v3/solve/multiframes

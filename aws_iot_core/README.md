# AWS IoT Core for LoRaWAN

AWS IoT Core for LoRaWAN is a part of AWS IoT Core for operating a LoRaWAN (low-power long-range Wide Area Network) private network operates by a private LNS (LoRa Network Server). Devices and gateways can connect to AWS IoT Core by using AWS IoT Core for LoRaWAN. Gateways should use the Basic Station firmware.

https://docs.aws.amazon.com/iot/latest/developerguide/connect-iot-lorawan-getting-started.html


## Getting started

Install the CLI for AWS IoT https://docs.aws.amazon.com/cli/latest/reference/iotwireless/index.html 

## Create a LNS

TODO

## Connect LoRa gateways

https://docs.aws.amazon.com/iot/latest/developerguide/connect-iot-lorawan-onboard-gateway-add.html 

`gateway_a1b2c3d4567890ab.json`:
```json
TODO
```

```bash
aws iotwireless create-wireless-gateway \
    --lorawan GatewayEui="a1b2c3d4567890ab",RfRegion="EU868" \
    --name "myFirstLoRaWANGateway" \
    --description "Using my first LoRaWAN gateway"
    --cli-input-json file://gateway_a1b2c3d4567890ab.json
```

## Get gateways stat

## Register LoRaWAN endpoints

TODO

## Get uplink messages from endpoints

## Send downlink messages to endpoints

## Misc

### Location services

https://docs.aws.amazon.com/cli/latest/reference/iotwireless/get-position-estimate.html 

```bash
aws iotwireless get-position-estimate --cli-input-json file://location.json
```

### Nodered
* https://flows.nodered.org/node/node-red-contrib-aws

### AWS SQS Simple Queue Service

#### Javascript
* https://docs.aws.amazon.com/AWSJavaScriptSDK/latest/AWS.html 
* https://docs.aws.amazon.com/code-library/latest/ug/sqs_example_sqs_ReceiveMessage_section.html
* https://github.com/awsdocs/aws-doc-sdk-examples/blob/main/javascriptv3/example_code/sqs/src/sqs_longpolling_receivemessage.js 

# CampusIoT :: MQTT Logger :: Tutorial :us:
[mqtt-logger](https://github.com/campusiot/mqtt-logger) is an utility for logging several MQTT messages flows for several topics and brokers into a single logfile.

## Step 0: Requirements
Install Docker CE and Docker Compose on your host
* https://docs.docker.com/install/
* https://docs.docker.com/compose/install/

## Step 1: Build the container image
```bash
git clone https://github.com/campusiot/mqtt-logger.git mqtt-logger
cd mqtt-logger
docker build -f Dockerfile -t campusiot/mqtt-logger:latest .
```

## Step 2: Configure
```bash
mkdir -p ~/configuration/mqtt-logger/
mkdir -p ~/data/mqtt-logger/
cp settings.CAMPUSIOT_MQTTS.json ~/configuration/mqtt-logger/settings.json
(cd ~/configuration/mqtt-logger ; wget https://raw.githubusercontent.com/CampusIoT/campusiot-certs/master/mqtt/ca.crt)
touch  ~/data/mqtt-logger/msg.log

# Edit topic, username and password
vi ~/configuration/mqtt-logger/settings.json
```

## Step 3: Run the container
```bash
docker run -d \
  -v ~/configuration/mqtt-logger/settings.json:/usr/src/app/settings.json:ro \
  -v ~/configuration/mqtt-logger/ca.crt:/usr/src/app/ca.crt:ro \
  -v ~/data/mqtt-logger/:/data/ \
  --name mqtt-logger campusiot/mqtt-logger:latest
```

## Step 4: Display the tail of the logfile
```bash
tailf ~/data/mqtt-logger/msg.log
```

# CampusIoT :: Tutoriel Eclipse Kura

[Eclipse Kura™](https://www.eclipse.org/kura/)  is an extensible open source IoT Edge Framework based on Java/OSGi. Kura offers API access to the hardware interfaces of IoT Gateways (serial ports, GPS, watchdog, GPIOs, I2C, etc.). It features ready-to-use field protocols (including Modbus, OPC-UA, S7), an application container, and a web-based visual data flow programming to acquire data from the field, process it at the edge, and publish it to leading IoT Cloud Platforms through MQTT connectivity.


## Démarrage
```bash
docker run -d -p 8080:8080 -t eclipse/kura
```

open http://localhost:8080

Le username/password est `admin` `admin`

## Programmation d'un Dataflow avec Kura Wires

https://eclipse.github.io/kura/wires/kura-wires-intro.html
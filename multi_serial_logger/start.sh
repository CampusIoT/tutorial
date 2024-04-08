#!/bin/bash

PORT_PREFIX_NAME=usbmodem
BAUDRATE=115200

for m in $(tio -L | grep $PORT_PREFIX_NAME)
do
	echo Logging $m
	nohup python serial_logger.py -d $m -s $BAUDRATE  >> nohup.out 2>&1 &
	echo $! > "${m##*/}".pid
done

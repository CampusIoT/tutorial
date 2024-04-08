#!/usr/bin/env python
# Log data from serial port

# Author: Diego Herranz

import argparse
import serial
import datetime
import time
import os

parser = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter)
parser.add_argument("-d", "--device", help="device to read from", default="/dev/ttyUSB0")
parser.add_argument("-s", "--speed", help="speed in bps", default=9600, type=int)
args = parser.parse_args()

base=os.path.basename(args.device)

outputFilePath = os.path.join(os.path.dirname(__file__),
                 base + "-" + datetime.datetime.now().strftime("%Y-%m-%dT%H%M%S") + ".log")
with serial.Serial(args.device, args.speed) as ser, open(outputFilePath, mode='wb') as outputFile:
#    print("Logging started. Ctrl-C to stop.") 
    try:
        while True:
            line = ser.readline()
            prefix = datetime.datetime.now().isoformat(timespec='milliseconds') + "> "
            outputFile.write(prefix.encode('utf-8'))
            outputFile.write(line)
            outputFile.flush()
    except KeyboardInterrupt:
        print("Logging stopped")


#!/bin/bash
avrdude -v -c arduino -P /dev/ttyACM0  -p atmega328p -U flash:w:build-uno/transmit_serial.bin 

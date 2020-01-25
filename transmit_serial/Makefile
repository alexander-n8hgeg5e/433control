# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile
ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = /code/arduino/Arduino-Makefile
AVRDUDE = /usr/bin/avrdude
BOARDS_TXT = /usr/share/arduino/hardware/arduino/avr/boards.txt
ARDUINO_CORE_PATH = /usr/share/arduino/hardware/arduino/avr/cores/arduino
ARDUINO_VAR_PATH  = /usr/share/arduino/hardware/arduino/avr/variants
BOARD_TAG    = uno
USER_LIB_PATH = ../libs
ARDUINO_LIBS = RFReceiver PinChangeInterruptHandler RFTransmitter
ARDUINO_HEADER = Arduino.h
OVERRIDE_EXECUTABLES = 1
CC      = $(CC_NAME)
CXX     = $(CXX_NAME)
AS      = $(AS_NAME)
OBJCOPY = $(OBJCOPY_NAME)
OBJDUMP = $(OBJDUMP_NAME)
AR      = $(AR_NAME)
SIZE    = $(SIZE_NAME)
NM      = $(NM_NAME)
ARDUINO_VERSION = $(shell arduino --version 2>/dev/null| cut -d " " -f2 |tr -d '.' )
include /code/arduino/Arduino-Makefile/Arduino.mk

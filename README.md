 Control some simple 433Mhz light switches.
 Control infrared controllable devices.
 Transmit data via 433Mhz rf.
 Control stuff arround you.

Warning: All instructions are only proposals and are
         for experienced people that have enough knowlege on the subject
         in order to ensure the safety,
         and the compliance with applicable law,
         while taking actions described in this document. 
         You are responsible for all consequences
         that result from following any instructions,
         suggestions or advice, described in this document.
         It is stated with this sentence, that
         this document does not claim to be compliant in
         terms of safety, morality, applicable law.
         Because of this there is no warranty for any
         of the mentioned things, nor for anything.
         Further is this document unfinished and
         work in progress.

Features:
    * bin size 7k
    * can send arbitrary on/off keyed 433MHz codes
    * can send arbitrary ir-codes with aprox 32khz modulation
    * codes are send over usb-serial and so need no space on the microcontroller
    * sender/receiver implementation to transmit arbitrary ascii chars
        with error correction/redundancy
    * gpio pin control
        * read/write gpio
        * pullup selectable
    * only simple hardware requirements:
        * arduino/avr with usbserial (optional receiver needs no usbserial)
        * transistor ir-led attachment (can be desoldered from old remote control)
        * some cheap 433Mhz modules
        * some jumper wires
        * optional: materials to encase the electronics and secure the wires

Dependencys:
    * Arduino-Makefile ( included as git submodule)
    * 3 small libs that are included as git submodules
    * avrdude
    * avr toolchain (arduino installation is suitable)
        this part has to be adjusted in the makefile
        see Arduino-Makefile/arduino-mk-vars.md
Usage:
  * fix/adjust the makefiles by comparing them.
    Latest one is probably "transmitter/Makefile".
  * connect the rf/ir modules with jumper wires to the arduino
  * load the firmware with "make upload"
  * use oszilloscope and/or logic analyser to capture some codes
  * add your codes and control stuff

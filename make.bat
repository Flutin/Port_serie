avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o SerialPort.o SerialPort.c
avr-gcc -mmcu=atmega328p SerialPort.o -o SerialPort
avr-objcopy -O ihex -R .eeprom SerialPort SerialPort.hex
avrdude -F -V -c arduino -p ATMEGA328P -P COM4 -b 115200 -U flash:w:SerialPort.hex
pause
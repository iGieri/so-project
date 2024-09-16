# Receiver

This directory contains all the code that will run on the receiver.

## File structure

In `avr_common/` we have useful functions for the avr like:
- the makefile to compile and write the code on the arduino
- UART initialize function
- Baudrate parameter

`arduino.c`:
- retrieve data from the joystick on 2 analog ports and 1 digital ports.
- save the data on a struct, this struct will be converted to an array of bytes called buffer.
- write the data on the buffer on the UART, using the USART_UDRE_vect interrupt that occurs anytime we write on the UART

## Compile and upload

Compile the code:

```
make
````

Upload to the arduino:

```
make arduino.hex
```

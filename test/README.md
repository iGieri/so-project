# Test

This is a minigame to test if the joystick is working and is calibrated

## File structure

`test.c`:
- creates a matrix
- read the joystick using joystick.h
- if there is an event we check the direction and move the character

## Compile, calibrate and run

Compile

```
make
```

Calibrate the joystick with

```
jstest-gtk
```

Run

```
./test
```

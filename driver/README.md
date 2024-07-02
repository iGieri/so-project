# Driver

This directory contains all the code that will run on pc.

## File structure

`serial/`:
- contains all the functions to open the serial file descriptor

`driver.c`:
- creates a virtual joystick using the ioctl systemcall
- retrieves data from the serial port
- creates a joystick event using the ioctl systemcall

`driver_mouse.c`:
- funny experiment to use the joystick as mouse (you should calibrate the joystick first!)

## Compile and run

Compile

```
make
```

Run

```
sudo ./driver
```

Check if it's working with `test/` section or `jstest-gtk`

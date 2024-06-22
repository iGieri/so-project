#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/uinput.h>
#include "driver.h"


void handle_error(const char* error) {
    perror(error);
    exit(-1);
}

void joystick_init(int fd, struct uinput_setup* usetup) {
    int ret;
    
    // Event ABS
    ret = ioctl(fd, UI_SET_EVBIT, EV_ABS);
    if (ret == -1) handle_error("Error ioctl EV_ABS");

    ret = ioctl(fd, UI_SET_ABSBIT, ABS_X);
    if (ret == -1) handle_error("Error ioctl ABS_X");

    ret = ioctl(fd, UI_SET_ABSBIT, ABS_Y);
    if (ret == -1) handle_error("Error ioctl ABS_Y");

    // Event button
    ret = ioctl(fd, UI_SET_EVBIT, EV_KEY);
    if (ret == -1) handle_error("Error ioctl EV_KEY");

    ret = ioctl(fd, UI_SET_KEYBIT, BTN_JOYSTICK);
    if (ret == -1) handle_error("Error ioctl BTN_JOYSTICK");

    

    // Configuration
    memset(usetup, 0, sizeof(struct uinput_setup));
    usetup->id.bustype = BUS_USB;
    usetup->id.vendor = 0x0198;      // My student ID as vendor/product id XD
    usetup->id.product = 0x2783; 
    strcpy(usetup->name, "Gieristick");

    ret = ioctl(fd, UI_DEV_SETUP, usetup);
    if (ret == -1) handle_error("Error ioctl DEV_SETUP");


    // Virtual joystick creation
    ret = ioctl(fd, UI_DEV_CREATE);
    if (ret == -1) handle_error("Error ioctl DEV_CREATE");
}

void joystick_destroy(fd) {
    int ret;
    ret = ioctl(fd, UI_DEV_DESTROY);
    if (ret == -1) handle_error("Error ioctl DEV_DESTROY");

    close(fd);
}

int main() {
    int fd;
    struct uinput_setup usetup;
    int ret;

    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd == -1) handle_error("Error on opening file descriptor");

    joystick_init(fd, &usetup);

    sleep(10);

    joystick_destroy(fd);

    return 0;
}

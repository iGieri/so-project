#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/uinput.h>
#include <errno.h>
#include "driver.h"
#include "serial/serial_linux.h"


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

void joystick_destroy(int fd) {
    int ret;
    ret = ioctl(fd, UI_DEV_DESTROY);
    if (ret == -1) handle_error("Error ioctl DEV_DESTROY");

    close(fd);
}

int main() {
    int joystick_fd;
    int serial_fd;
    struct uinput_setup usetup;
    int ret;

    serial_fd = serial_open(SERIAL_DEVICE);
    if (serial_fd == -1) handle_error("Error on opening serial file descriptor");

    serial_set_interface_attribs(serial_fd, SERIAL_BAUDRATE, 0);
    serial_set_blocking(serial_fd, 1);

    joystick_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (joystick_fd == -1) handle_error("Error on opening joystick file descriptor");

    joystick_init(joystick_fd, &usetup);

    while(1) {
        // read from serial
        char buf[1024];
        memset(buf, 0, 1024);

        int bytes_read = 0;
        do {
            ret = read(serial_fd, buf+bytes_read, 1);
            if (ret == -1) {
                if (errno == EINTR) continue;
                else handle_error("Error reading serial");
            }
        } while(buf[bytes_read++] != '\n');

        int x, y;
        sscanf(buf, "%d,%d\n", &x, &y);

        printf("x: %d\ty: %d\tbuf: %s", x, y, buf);
    }

    joystick_destroy(joystick_fd);

    return 0;
}

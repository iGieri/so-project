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

void mouse_init(int fd, struct uinput_setup* usetup) {
    int ret;
    
    // Event ABS
    ret = ioctl(fd, UI_SET_EVBIT, EV_REL);
    if (ret == -1) handle_error("Error ioctl EV_ABS");

    ret = ioctl(fd, UI_SET_RELBIT, REL_X);
    if (ret == -1) handle_error("Error ioctl REL_X");

    ret = ioctl(fd, UI_SET_RELBIT, REL_Y);
    if (ret == -1) handle_error("Error ioctl REL_Y");

    ret = ioctl(fd, UI_SET_RELBIT, REL_WHEEL);
    if (ret == -1) handle_error("Error ioctl REL_WHEEL");

    // Event button
    ret = ioctl(fd, UI_SET_EVBIT, EV_KEY);
    if (ret == -1) handle_error("Error ioctl EV_KEY");

    ret = ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
    if (ret == -1) handle_error("Error ioctl BTN_LEFT");

    ret = ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT);
    if (ret == -1) handle_error("Error ioctl BTN_RIGHT");

    ret = ioctl(fd, UI_SET_KEYBIT, BTN_MIDDLE);
    if (ret == -1) handle_error("Error ioctl BTN_MIDDLE");

    // Configuration
    memset(usetup, 0, sizeof(struct uinput_setup));
    usetup->id.bustype = BUS_USB;
    usetup->id.vendor = 0x0198;      // My student ID as vendor/product id XD
    usetup->id.product = 0x2780; 
    strcpy(usetup->name, "Gierimouse");

    ret = ioctl(fd, UI_DEV_SETUP, usetup);
    if (ret == -1) handle_error("Error ioctl DEV_SETUP");


    // Virtual mouse creation
    ret = ioctl(fd, UI_DEV_CREATE);
    if (ret == -1) handle_error("Error ioctl DEV_CREATE");
}

void mouse_event(int fd, int x, int y, int btn) {
    struct input_event event;
    int ret;
    memset(&event, 0, sizeof(struct input_event));
    event.type = EV_REL;
    
    event.code = REL_X;
    event.value = x;
    ret = write(fd, &event, sizeof(struct input_event));
    if (ret == -1) handle_error("Error write X");

    event.code = REL_Y;
    event.value = y;
    ret = write(fd, &event, sizeof(struct input_event));
    if (ret == -1) handle_error("Error write Y");

    event.type = EV_KEY;
    event.code = BTN_LEFT;
    event.value = btn;
    ret = write(fd, &event, sizeof(struct input_event));
    if (ret == -1) handle_error("Error write button");
}

void mouse_destroy(int fd) {
    int ret;
    ret = ioctl(fd, UI_DEV_DESTROY);
    if (ret == -1) handle_error("Error ioctl DEV_DESTROY");

    close(fd);
}

int main() {
    int mouse_fd;
    int serial_fd;
    struct uinput_setup usetup;
    int ret;

    serial_fd = serial_open(SERIAL_DEVICE);
    if (serial_fd == -1) handle_error("Error on opening serial file descriptor");

    serial_set_interface_attribs(serial_fd, SERIAL_BAUDRATE, 0);
    serial_set_blocking(serial_fd, 1);

    mouse_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (mouse_fd == -1) handle_error("Error on opening mouse file descriptor");

    mouse_init(mouse_fd, &usetup);

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

        int x, y, button;
        sscanf(buf, "%d,%d,%d\n", &x, &y, &button);

        printf("x: %d\ty: %d\tbut: %d\n", x, y, button);

        if (x<1024 && y<1024)
        mouse_event(mouse_fd, x-509, y-534, button);
    }

    mouse_destroy(mouse_fd);

    return 0;
}


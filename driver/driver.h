#define SERIAL_DEVICE "/dev/ttyACM0"
#define SERIAL_BAUDRATE 19200

void handle_error(const char* error);

void joystick_init(int fd, struct uinput_setup* usetup);

void joystick_destroy();
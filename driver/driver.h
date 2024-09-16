#define SERIAL_DEVICE "/dev/ttyUSB0"
#define SERIAL_BAUDRATE 9600

void handle_error(const char* error);

void joystick_init(int fd, struct uinput_setup* usetup);
void joystick_event(int fd, int x, int y, int btn);
void joystick_destroy();

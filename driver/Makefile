CC = gcc

CFLAGS = -Wall -Wextra -I. -Iserial

OBJ_DRIVER = driver.o serial/serial_linux.o
OBJ_DRIVER_MOUSE = driver_mouse.o serial/serial_linux.o

TARGET_DRIVER = driver
TARGET_DRIVER_MOUSE = driver_mouse

all: $(TARGET_DRIVER) $(TARGET_DRIVER_MOUSE)

$(TARGET_DRIVER): $(OBJ_DRIVER)
	$(CC) -o $@ $^

$(TARGET_DRIVER_MOUSE): $(OBJ_DRIVER_MOUSE)
	$(CC) -o $@ $^

driver.o: driver.c driver.h serial/serial_linux.h
	$(CC) $(CFLAGS) -c $< -o $@

driver_mouse.o: driver_mouse.c driver.h serial/serial_linux.h
	$(CC) $(CFLAGS) -c $< -o $@

serial/serial_linux.o: serial/serial_linux.c serial/serial_linux.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DRIVER) $(OBJ_DRIVER_MOUSE) $(TARGET_DRIVER) $(TARGET_DRIVER_MOUSE)

.PHONY: all clean run_driver run_driver_mouse

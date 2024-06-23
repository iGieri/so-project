# Nome del compilatore
CC = gcc

# Opzioni di compilazione
CFLAGS = -Wall -Wextra -I. -Iserial

# File oggetto
OBJ_DRIVER = driver.o serial/serial_linux.o
OBJ_DRIVER_MOUSE = driver_mouse.o serial/serial_linux.o

# Nomi degli eseguibili
TARGET_DRIVER = driver
TARGET_DRIVER_MOUSE = driver_mouse

# Regola di default
all: $(TARGET_DRIVER) $(TARGET_DRIVER_MOUSE)

# Regola per creare l'eseguibile driver
$(TARGET_DRIVER): $(OBJ_DRIVER)
	$(CC) -o $@ $^

# Regola per creare l'eseguibile driver_mouse
$(TARGET_DRIVER_MOUSE): $(OBJ_DRIVER_MOUSE)
	$(CC) -o $@ $^

# Regola per compilare driver.o
driver.o: driver.c driver.h serial/serial_linux.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per compilare driver_mouse.o
driver_mouse.o: driver_mouse.c driver.h serial/serial_linux.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per compilare serial_linux.o
serial/serial_linux.o: serial/serial_linux.c serial/serial_linux.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per pulire i file generati
clean:
	rm -f $(OBJ_DRIVER) $(OBJ_DRIVER_MOUSE) $(TARGET_DRIVER) $(TARGET_DRIVER_MOUSE)

# Regola per eseguire l'eseguibile driver
run_driver: $(TARGET_DRIVER)
	./$(TARGET_DRIVER)

# Regola per eseguire l'eseguibile driver_mouse
run_driver_mouse: $(TARGET_DRIVER_MOUSE)
	./$(TARGET_DRIVER_MOUSE)

.PHONY: all clean run_driver run_driver_mouse

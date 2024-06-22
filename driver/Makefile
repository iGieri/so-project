# Nome del compilatore
CC = gcc

# Opzioni di compilazione
CFLAGS = -Wall -Wextra -I. -Iserial

# File oggetto
OBJ = driver.o serial/serial_linux.o

# Nome dell'eseguibile
TARGET = driver

# Regola di default
all: $(TARGET)

# Regola per creare l'eseguibile
$(TARGET): $(OBJ)
	$(CC) -o $@ $^

# Regola per compilare driver.o
driver.o: driver.c driver.h serial/serial_linux.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per compilare serial_linux.o
serial/serial_linux.o: serial/serial_linux.c serial/serial_linux.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per pulire i file generati
clean:
	rm -f $(OBJ) $(TARGET)

# Regola per eseguire l'eseguibile
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

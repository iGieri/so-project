# Nome del compilatore
CC = gcc

# Opzioni del compilatore
CFLAGS = -Wall -Wextra -O2

# Nome del file sorgente e dell'eseguibile
SRC = test.c
TARGET = test

# Obiettivo principale: compila l'eseguibile
all: $(TARGET)

# Regola per compilare l'eseguibile
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Obiettivo per la pulizia dei file compilati
clean:
	rm -f $(TARGET)

# Obiettivo per ricompilare tutto
rebuild: clean all

# Indica che clean e rebuild non sono file
.PHONY: all clean rebuild

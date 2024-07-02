CC = gcc

CFLAGS = -Wall -Wextra -O2

SRC = test.c
TARGET = test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild

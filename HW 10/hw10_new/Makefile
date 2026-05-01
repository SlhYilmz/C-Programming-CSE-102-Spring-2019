CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -D_POSIX_C_SOURCE=200809L -I inc -I src
TARGET = hw10
SRC = main.c src/part1.c src/part2.c src/part3.c src/part4.c src/ds_utils.c src/time_utils.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

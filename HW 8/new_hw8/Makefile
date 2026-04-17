CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Wpedantic -Wshadow -Wconversion \
          -fno-common -I inc -finput-charset=UTF-8 -fexec-charset=UTF-8
TARGET  = monopoly
LIB_SRCS = src/board.c src/display.c src/property.c src/gameplay.c
LIB_OBJS = $(LIB_SRCS:src/%.c=build/%.o)
MAIN_OBJ = build/main.o
OBJS     = $(MAIN_OBJ) $(LIB_OBJS)

.PHONY: all run clean

all: build $(TARGET)

build:
	mkdir -p build

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN_OBJ): main.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: all
	./$(TARGET)

clean:
	rm -rf build $(TARGET)

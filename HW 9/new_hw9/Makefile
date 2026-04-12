CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Wpedantic -Wshadow -Wconversion \
          -fno-common
TARGET  = hw9.exe
SRCS    = main.c person.c
OBJS    = $(patsubst %.c,build/%.o,$(SRCS))

.PHONY: all clean run

all: build $(TARGET)

build:
	mkdir -p build

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) -r build $(TARGET)

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
TARGET = new_hw6.exe
TEST_TARGET = test_hw6.exe
SRCS = main.c part1.c part2.c part3.c part4.c part5.c
OBJS = $(SRCS:.c=.o)
TEST_SRC = test_hw6.c

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $@ $(TEST_SRC)

clean:
	$(RM) $(OBJS) $(TARGET) $(TEST_TARGET) NUL

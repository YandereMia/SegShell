SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
CC := gcc
CFLAGS := -Wall -Wextra -O3

TARGET := SegShell

# Source files (core + utils + commands)
SRCS := $(wildcard $(SRC_DIR)/core/*.c) \
        $(wildcard $(SRC_DIR)/utils/*.c) \
        $(wildcard $(SRC_DIR)/commands/internal/*.c)

OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(TARGET)

# Build SegShell (everything in one binary)
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^

# Compile all source files into .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run:
	./$(TARGET)

.PHONY: all clean install run

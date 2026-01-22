SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
CC := gcc
CFLAGS := -Wall -Wextra -O3
#LDFLAGS := -ljansson -lm -ldl `pkg-config --libs gtk4`

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

# Install binary to ~/.myshellos/bin
INSTALL_DIR := $(HOME)/.myshellos/bin
install: $(TARGET)
	@mkdir -p $(INSTALL_DIR)
	cp $(TARGET) $(INSTALL_DIR)/
	@echo "✅ Installed $(TARGET) to $(INSTALL_DIR)"

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run:
	./$(TARGET)

.PHONY: all clean install run

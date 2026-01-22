# Minimal Makefile for SegShell modules

# Modules (all standalone commands)
MODULES = about cat calc clear echo help rm touch time whoami write ls
# Directories
BUILD_DIR = build
INSTALL_DIR ?= /home/$(USER)/segshell/bin

# Compiler settings
CC = gcc
CFLAGS = -Wall -O2 -I../inc  # include headers if needed

# Automatically add cmd_ prefix to sources
SOURCES = $(addprefix cmd_, $(addsuffix .c, $(MODULES)))
TARGETS = $(addprefix $(BUILD_DIR)/, $(MODULES))

# Default: build all modules
all: $(TARGETS)

# Pattern rule: build each command
$(BUILD_DIR)/%: cmd_%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Clean build directory
clean:
	rm -f $(BUILD_DIR)/*

# Install modules safely
install: all
	@mkdir -p $(INSTALL_DIR)
	cp $(TARGETS) $(INSTALL_DIR)/
	chmod +x $(INSTALL_DIR)/*

.PHONY: all clean install

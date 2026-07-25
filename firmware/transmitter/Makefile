# Compilers
HOST_CC := gcc
AVR_CC  := avr-gcc

# ELF -> HEX conversion
AVR_OBJCOPY := avr-objcopy

# MCU config
MCU   := atmega328p
F_CPU := 16000000UL

# Directories
SRC_DIR   := src
TEST_DIR  := tests
BUILD_DIR := build

HOST_BUILD_DIR := $(BUILD_DIR)/host
AVR_BUILD_DIR  := $(BUILD_DIR)/avr

# Sources
COMMON_SOURCES := $(SRC_DIR)/settings.c
TEST_SOURCES   := $(TEST_DIR)/main.c $(COMMON_SOURCES)

# TODO
FIRMWARE_SOURCES := $(SRC_DIR)/main.c $(COMMON_SOURCES)

# Generated files
TEST_EXECUTABLE := $(HOST_BUILD_DIR)/tests

FIRMWARE_ELF := $(AVR_BUILD_DIR)/transmitter.elf
FIRMWARE_HEX := $(AVR_BUILD_DIR)/transmitter.hex

# Common options
COMMON_WARNINGS := -Wall -Wextra -Wpedantic

# gcc options
HOST_CFLAGS := \
	-std=c11 \
	$(COMMON_WARNINGS) \
	-g \
	-O0 \
	-I$(SRC_DIR) \
	-DUNIT_TEST

# avr-gcc options
AVR_CFLAGS := \
	-std=c11 \
	$(COMMON_WARNINGS) \
	-Os \
	-mmcu=$(MCU) \
	-DF_CPU=$(F_CPU) \
	-I$(SRC_DIR)

AVR_LDFLAGS := -mmcu=$(MCU)

.PHONY: all test run firmware clean

all: test

test: $(TEST_EXECUTABLE)

run: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(TEST_SOURCES) | $(HOST_BUILD_DIR)
	$(HOST_CC) $(HOST_CFLAGS) $(TEST_SOURCES) -o $@

firmware: $(FIRMWARE_HEX)

$(FIRMWARE_ELF): $(FIRMWARE_SOURCES) | $(AVR_BUILD_DIR)
	$(AVR_CC) $(AVR_CFLAGS) $(FIRMWARE_SOURCES) \
		$(AVR_LDFLAGS) -o $@

$(FIRMWARE_HEX): $(FIRMWARE_ELF)
	$(AVR_OBJCOPY) \
		-O ihex \
		-R .eeprom \
		$< $@

# Making build dirs
$(HOST_BUILD_DIR):
	mkdir -p $@

$(AVR_BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

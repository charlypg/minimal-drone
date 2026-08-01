# Config

PROJECT := test_atmega328p
MCU := atmega328p
F_CPU := 16000000UL

# ArduinoISP programmer (Arduino example)
PROGRAMMER := stk500v1
PORT := /dev/ttyACM0
BAUD := 19200

LFUSE := 0xFF

# Tools
CC := avr-gcc
OBJCOPY := avr-objcopy
SIZE := avr-size
AVRDUDE := avrdude

# Files & dirs
BUILD_DIR := build

SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPENDS := $(OBJECTS:.o=.d)

ELF := $(BUILD_DIR)/$(PROJECT).elf
HEX := $(BUILD_DIR)/$(PROJECT).hex

# Compiler options
CPPFLAGS := -DF_CPU=$(F_CPU)

CFLAGS := \
    -mmcu=$(MCU) \
    -std=c11 \
    -Os \
    -Wall \
    -Wextra \
    -Wpedantic \
    -ffunction-sections \
    -fdata-sections \
    -MMD \
    -MP

LDFLAGS := \
    -mmcu=$(MCU) \
    -Wl,--gc-sections


# Rules
.PHONY: all clean flash lfuse size

all: $(HEX)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(ELF): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

flash: $(HEX)
	$(AVRDUDE) \
		-p $(MCU) \
		-c $(PROGRAMMER) \
		-P $(PORT) \
		-b $(BAUD) \
		-U flash:w:$(HEX):i

lfuse:
	$(AVRDUDE) \
		-p $(MCU) \
		-c $(PROGRAMMER) \
		-P $(PORT) \
		-b $(BAUD) \
		-U lfuse:w:$(LFUSE):m


size: $(ELF)
	$(SIZE) --mcu=$(MCU) --format=avr $(ELF)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPENDS)

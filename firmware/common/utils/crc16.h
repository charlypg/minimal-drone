#ifndef CRC16_H
#define CRC16_H

#include <stdint.h>
#include <stddef.h>

uint16_t crc16_update(uint16_t crc, uint8_t data);

uint16_t crc16_compute(
    const void *data,
    size_t length,
    uint16_t initial_value
);

#endif /* CRC16_H */
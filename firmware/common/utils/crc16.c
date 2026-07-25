#include "crc16.h"

uint16_t crc16_update(uint16_t crc, uint8_t data)
{
    crc ^= data;

    for (uint8_t i = 0; i < 8; ++i)
    {
        if ((crc & 1U) != 0U)
        {
            crc = (crc >> 1U) ^ 0xA001U;
        }
        else
        {
            crc >>= 1U;
        }
    }

    return crc;
}

uint16_t crc16_compute(
    const void *data,
    size_t length,
    uint16_t initial_value
)
{
    const uint8_t *bytes = data;
    uint16_t crc = initial_value;

    for (size_t i = 0; i < length; ++i)
    {
        crc = crc16_update(crc, bytes[i]);
    }

    return crc;
}

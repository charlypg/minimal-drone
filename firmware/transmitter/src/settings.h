#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdbool.h>
#include <stdint.h>

#define SETTINGS_MAGIC   0xCAFEu
#define SETTINGS_VERSION 1u

typedef enum
{
    SETTINGS_AXIS_ROLL = 0,
    SETTINGS_AXIS_PITCH,
    SETTINGS_AXIS_YAW,
    SETTINGS_AXIS_THROTTLE,
    SETTINGS_AXIS_COUNT
} SettingsAxis;

typedef struct
{
    uint16_t min;
    uint16_t center;
    uint16_t max;
} AxisCalibration;

typedef struct
{
    AxisCalibration axis[SETTINGS_AXIS_COUNT];
} JoystickCalibration;

typedef struct
{
    uint16_t magic;
    uint8_t version;
    JoystickCalibration joystick;
    uint16_t crc;
} Settings;

#endif /* SETTINGS_H */

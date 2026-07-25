#include "settings.h"

#include <stddef.h>

/* Working copy used by the firmware, stored in RAM. */
// TODO
// static Settings settings_data;

// TODO
// static bool axis_is_valid(const AxisCalibration *axis)
bool axis_is_valid(const AxisCalibration *axis)
{
    if (axis == NULL) {
        return false;
    }

    return axis->min < axis->center &&
           axis->center < axis->max &&
           axis->max <= 1023u;
}

#include <stdio.h>
#include <stdbool.h>

#include "settings.h"

/* Temporarily remove the 'static' keyword from settings.c
 * and add this declaration here.
 */
bool axis_is_valid(const AxisCalibration *axis);

static void print_result(const AxisCalibration *axis)
{
    printf("min=%4u  center=%4u  max=%4u  --> %s\n",
           axis->min,
           axis->center,
           axis->max,
           axis_is_valid(axis) ? "VALID" : "INVALID");
}

int main(void)
{
    AxisCalibration axis;

    /* Cas valide */
    axis.min = 0;
    axis.center = 512;
    axis.max = 1023;
    print_result(&axis);

    /* min == center */
    axis.min = 512;
    axis.center = 512;
    axis.max = 1023;
    print_result(&axis);

    /* center == max */
    axis.min = 0;
    axis.center = 1023;
    axis.max = 1023;
    print_result(&axis);

    /* min > center */
    axis.min = 600;
    axis.center = 500;
    axis.max = 1023;
    print_result(&axis);

    /* max > ADC */
    axis.min = 0;
    axis.center = 512;
    axis.max = 1200;
    print_result(&axis);

    return 0;
}

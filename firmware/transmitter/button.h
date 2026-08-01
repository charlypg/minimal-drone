#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

// #define BUTTON_DEBOUNCE_TIME 20 // 20 ms

typedef enum {
    BUTTON_PRESSED,
    BUTTON_DEBOUNCE_P,
    BUTTON_RELEASED,
    BUTTON_DEBOUNCE_R
} ButtonState;

typedef struct {
    ButtonState state;
    uint8_t counter;
    uint8_t debounce_ticks;
} Button;

typedef enum {
    BUTTON_EVENT_NONE,
    BUTTON_EVENT_PRESSED,
    BUTTON_EVENT_RELEASED
} ButtonEvent;

void button_init(Button * button, uint8_t debounce_ticks);
ButtonEvent button_update(Button * button, uint8_t raw_pressed);

#endif

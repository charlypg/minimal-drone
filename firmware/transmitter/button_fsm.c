#include "button_fsm.h"

void button_init(Button * button, uint8_t debounce_ticks) {
    button->state = BUTTON_RELEASED;
    button->counter = 0;
    button->debounce_ticks = debounce_ticks;
}

ButtonEvent button_update(Button * button, uint8_t raw_pressed) {
    switch (button->state) {
    case BUTTON_RELEASED:
        // Wait for a possible button press.
        if (raw_pressed) {
            button->counter = 0;
            button->state = BUTTON_DEBOUNCE_P;
        }
        break;
    case BUTTON_DEBOUNCE_P:
        // Confirm that the button remains pressed during the debounce period.
        if (!raw_pressed) {
            button->state = BUTTON_RELEASED;
        }
        else if (++button->counter >= button->debounce_ticks) {
            button->state = BUTTON_PRESSED;
            return BUTTON_EVENT_PRESSED;
        }
        break;
    case BUTTON_PRESSED:
        // Wait for a possible button release.
        if (!raw_pressed) {
            button->counter = 0;
            button->state = BUTTON_DEBOUNCE_R;
        }
        break;
    case BUTTON_DEBOUNCE_R:
        // Confirm that the button remains released during the debounce period.
        if (raw_pressed) {
            button->state = BUTTON_PRESSED;
        }
        else if (++button->counter >= button->debounce_ticks) {
            button->state = BUTTON_RELEASED;
            return BUTTON_EVENT_RELEASED;
        }
        break;
    
    default:
        break;
    }

    return BUTTON_EVENT_NONE;
}

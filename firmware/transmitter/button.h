#ifndef BUTTON_H
#define BUTTON_H

#define DDR_SW DDRD
#define PORT_SW PORTD
#define LOGIC_STATE_SW PIND

#define THRUST_YAW_SW_PIN PD3
#define THRUST_YAW_SW_LOGIC PIND3

#define ROLL_PITCH_SW_PIN PD4
#define ROLL_PITCH_SW_LOGIC PIND4

#define CALIB_SW_PIN PD5
#define CALIB_SW_LOGIC PIND5

#define BUTTON_INIT(pin)            (DDR_SW &= ~(1 << (pin)))
#define BUTTON_ACTIVATE_PULLUP(pin) (PORT_SW |= (1 << (pin)))
#define BUTTON_STATE(bit)           (LOGIC_STATE_SW & (1 << (bit)))

#endif

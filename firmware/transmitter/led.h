#ifndef LED_H
#define LED_H

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_BLUE_PIN PB0
#define LED_GREEN_PIN PB1

#define LED_BLUE_INIT()    (LED_DDR |=  (1U << LED_BLUE_PIN))
#define LED_BLUE_ON()      (LED_PORT |=  (1U << LED_BLUE_PIN))
#define LED_BLUE_OFF()     (LED_PORT &= ~(1U << LED_BLUE_PIN))
#define LED_BLUE_TOGGLE()  (LED_PORT ^=  (1U << LED_BLUE_PIN))

#define LED_GREEN_INIT()    (LED_DDR |=  (1U << LED_GREEN_PIN))
#define LED_GREEN_ON()      (LED_PORT |=  (1U << LED_GREEN_PIN))
#define LED_GREEN_OFF()     (LED_PORT &= ~(1U << LED_GREEN_PIN))
#define LED_GREEN_TOGGLE()  (LED_PORT ^=  (1U << LED_GREEN_PIN))

#endif

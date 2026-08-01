#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "button_fsm.h"
#include "led.h"
#include "uart.h"


volatile uint8_t button_update_pending = 0;
volatile uint16_t tx_counter = 0;
volatile uint8_t tx_pending = 0;
volatile uint16_t adc0_value = 0;
volatile uint16_t adc1_value = 0;
volatile uint8_t adc_channel = 0;
volatile uint8_t adc_counter = 0;
volatile uint8_t adc_ready = 0;

ISR(TIMER0_COMPA_vect)
{
    button_update_pending = 1;

    tx_counter++;
    if (tx_counter >= 1000) {
        tx_counter = 0;
        tx_pending = 1;
    }

    adc_counter++;
    if (adc_counter >= 10) {
        adc_counter = 0;

        /*
         * Commencer la séquence par ADC0.
         */
        adc_channel = 0;

        /*
         * Sélection d'ADC0.
         * On conserve les bits de référence REFS1:0.
         */
        ADMUX = (ADMUX & 0xF0) | 0;

        /*
         * Démarrage de la conversion.
         */
        ADCSRA |= (1 << ADSC);
    }
}

ISR(ADC_vect)
{
    if (adc_channel == 0)
    {
        /*
         * La conversion d'ADC0 vient de se terminer.
         */
        adc0_value = ADC;

        /*
         * Sélection d'ADC1.
         */
        adc_channel = 1;
        ADMUX = (ADMUX & 0xF0) | 1;

        /*
         * Démarrage de la conversion d'ADC1.
         */
        ADCSRA |= (1 << ADSC);
    }
    else
    {
        /*
         * La conversion d'ADC1 vient de se terminer.
         */
        adc1_value = ADC;

        /*
         * Les deux nouvelles valeurs sont disponibles.
         */
        adc_ready = 1;
    }
}


Button button_middle;
ButtonEvent button_middle_event = BUTTON_EVENT_NONE;
uint8_t button_middle_raw;

char tx_buffer[64];

uint16_t value_0;
uint16_t value_1;

int main(void)
{
    button_init(&button_middle, 20);

    // LEDs
    LED_BLUE_INIT();
    LED_BLUE_OFF();
    LED_GREEN_INIT();
    LED_GREEN_OFF();

    // Input button_middle
    DDRD &= ~(1 << DDD5); // PD5 input
    PORTD |= (1 << PD5); // activate pull-up resistor

    // Init timer
    TCCR0A = (1 << WGM01); // CTC
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler
    OCR0A = 249; // devided again by 249+1
    TIMSK0 = (1 << OCIE0A); // Interrupt

    uart_init(); // Initialize UART
    

    // Init ADC
        /*
     * PC0/ADC0 et PC1/ADC1 en entrée, sans pull-up.
     */
    DDRC &= ~((1 << DDC0) | (1 << DDC1));
    PORTC &= ~((1 << PC0) | (1 << PC1));

    /*
     * Désactivation des entrées numériques sur ADC0 et ADC1.
     */
    DIDR0 = (1 << ADC0D) | (1 << ADC1D);

    /*
     * Référence ADC = AVCC.
     * Résultat aligné à droite.
     * Canal initial = ADC0.
     */
    ADMUX = (1 << REFS0);

    /*
     * Activation de l'ADC.
     * Activation de son interruption.
     * Prescaler ADC = 128.
     *
     * Avec F_CPU = 16 MHz :
     * 16 MHz / 128 = 125 kHz.
     */
    ADCSRA =
        (1 << ADEN)  |
        (1 << ADIE)  |
        (1 << ADPS2) |
        (1 << ADPS1) |
        (1 << ADPS0); 
    

    // enable interrupts
    sei();

    while (1) {
        // Button state
        if (button_update_pending) {
            button_middle_raw = (PIND & (1 << PIND5));
            button_middle_event = button_update(&button_middle, button_middle_raw);
            if (button_middle_event == BUTTON_EVENT_PRESSED) {
                LED_BLUE_TOGGLE();
                uart_puts("PRESSED!\r\n");
            }
            button_update_pending = 0;
        }

        // ADC
        if (adc_ready) {
            /*
             * Éviter que l'ISR ADC modifie une valeur pendant
             * sa copie. L'AVR étant un processeur 8 bits,
             * la copie d'un uint16_t n'est pas atomique.
             */
            cli();

            value_0 = adc0_value;
            value_1 = adc1_value;
            adc_ready = 0;

            sei();
        }

        // TX
        if (tx_pending) {
            sprintf(tx_buffer, "x=%u y=%u\r\n", value_0, value_1);
            uart_puts(tx_buffer);
            tx_pending = 0;
        }

    }

    return 0;
}


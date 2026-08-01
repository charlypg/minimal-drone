#include <avr/io.h>

void uart_init() {
    UBRR0 = 8; // 115200 baud
    UCSR0B =
        (1 << RXEN0) |
        (1 << TXEN0); // enable TX & RX
    UCSR0C =
        (1 << UCSZ01) |
        (1 << UCSZ00); // 8 bits, 1 stop, no parity
}

void uart_putchar(char c) {
    // Wait emission register
    while (!(UCSR0A & (1 << UDRE0))){}
    UDR0 = c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_putchar(*s++);
    }
}
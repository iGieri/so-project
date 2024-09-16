#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void UART_init(uint16_t baudrate) {
  uint16_t ubrr_value = (F_CPU / 16 / baudrate) - 1;

  UBRR0H = (uint8_t)(ubrr_value >> 8);
  UBRR0L = (uint8_t)ubrr_value;

  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  // Activating UART interrupts
  UCSR0B |= (1 << UDRIE0);
}

 
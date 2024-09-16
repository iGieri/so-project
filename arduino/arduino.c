#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include "../avr_common/uart.h" // this includes the printf and initializes it
#include <avr/io.h>
#include <avr/interrupt.h>

#define TX_BUFFER_SIZE 256

long map(long value, long input_min, long input_max, long output_min, long output_max) {
  return (value - input_min) * (output_max - output_min) / (input_max - input_min) + output_min;
}


typedef struct __attribute__((packed)) {
  uint16_t x_axis;
  uint16_t y_axis;
  uint8_t button;
} joystick_event;

uint8_t tx_buffer[TX_BUFFER_SIZE];
uint8_t tx_index = 0;
uint8_t tx_read_index = 0;

void adc_init() {
  // Setting ADC Prescaler to 128
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  
  // Set voltage to AVcc with an extern capacitory on AREF pin
  ADMUX |= (1 << REFS0);
  
  // Activate ADC
  ADCSRA |= (1 << ADEN);
}

void digital_init() {
  // Setting port as input
  DDRB &= ~(1 << 0); 

  // Activating pull up resistor
  PORTB |= (1 << 0);
}

uint16_t adc_read(uint8_t ch) {
  // Select ADC channel
  ch &= 0b00000111;
  ADMUX = (ADMUX & 0xF8) | ch;
  
  // Start conversion
  ADCSRA |= (1 << ADSC);
  
  // Wait for the conversion to complete
  while (ADCSRA & (1 << ADSC));
  
  return (ADC);
}

uint8_t digital_read() {
  return (PINB&(1 << 0))==0;
}

void UART_transmit_struct(joystick_event* ev) {
  uint8_t* byte = (uint8_t*) ev;
  uint8_t size = sizeof(joystick_event);

  for (uint8_t i = 0; i < size; i++) {
    uint8_t next = (tx_index + 1) % TX_BUFFER_SIZE;
    while (next == tx_read_index);  // Spinlock buffer full
    tx_buffer[tx_index] = byte[i];
    tx_index = next;
  }

  // Activating Transmition Interrupt
  UCSR0B |= (1 << UDRIE0);
}


ISR(USART_UDRE_vect) {
  if (tx_read_index != tx_index) {
    UDR0 = tx_buffer[tx_read_index];
    tx_read_index = (tx_read_index + 1) % TX_BUFFER_SIZE;
  } else {
    UDR0 = '\n';
    UCSR0B &= ~(1 << UDRIE0);  // Send \n and stop transmission if the buffer is empty 
  }
}

int main(void){
  // initializations
  UART_init(BAUD);
  
  adc_init();

  digital_init();

  sei();

  while(1){
    uint16_t x_value = map(adc_read(0), 0, 1024, 0, 700);
    uint16_t y_value = map(adc_read(1), 0, 1024, 0, 700); 
    uint8_t button = digital_read();

    joystick_event ev;
    ev.x_axis = x_value;
    ev.y_axis = y_value;
    ev.button = button;

    UART_transmit_struct(&ev);

    _delay_ms(50);
  }
  
}

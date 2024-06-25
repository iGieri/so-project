#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include "../avr_common/uart.h" // this includes the printf and initializes it
#include <avr/io.h>


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

int main(void){
  // this initializes the printf/uart thingies
  printf_init(); 
  
  adc_init();

  digital_init();

  while(1){
    uint16_t x_value = adc_read(0);
    uint16_t y_value = adc_read(1); 
    uint8_t button = digital_read();

    printf("%d,%d,%d\n",x_value, y_value, button);
  }
  
}

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

int main(void){
  // this initializes the printf/uart thingies
  printf_init(); 
  
  adc_init();

  while(1){
    uint16_t x_value = adc_read(0);
    uint16_t y_value = adc_read(1); 

    printf("%d,%d\n",x_value, y_value);
  }
  
}

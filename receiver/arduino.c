#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void uart1_init(void) {
    uint16_t ubrr_value = 103;  // Baud rate 9600 per 16 MHz
    UBRR1H = (unsigned char)(ubrr_value >> 8);
    UBRR1L = (unsigned char)ubrr_value;
    UCSR1B = (1 << RXEN1) | (1 << TXEN1); // Abilita ricezione e trasmissione
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); // 8 bit di dati, 1 bit di stop
}

unsigned char uart1_receive(void) {
    while (!(UCSR1A & (1 << RXC1))); // Attendi che ci siano dati ricevuti
    return UDR1; // Leggi il dato ricevuto
}

void uart0_init(void) {
    uint16_t ubrr_value = 103;  // Baud rate 9600 per 16 MHz
    UBRR0H = (unsigned char)(ubrr_value >> 8);
    UBRR0L = (unsigned char)ubrr_value;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Abilita ricezione e trasmissione
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bit di dati, 1 bit di stop
}

void uart0_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0))); // Attendi che il buffer di trasmissione sia vuoto
    UDR0 = data; // Trasmetti i dati
}

int main(void) {
    uart1_init();  // Inizializza UART1 per comunicazione con HC-12
    uart0_init();  // Inizializza UART0 per inviare i dati ricevuti al PC

    while (1) {
        unsigned char data = uart1_receive(); // Ricevi i dati da HC-12
        uart0_transmit(data); // Invia i dati ricevuti alla seriale (PC)
    }

    return 0;
}

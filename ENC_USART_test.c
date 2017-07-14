#define F_CPU 20000000UL

#include <avr/io.h>
#include <ENC28J60_functions.h>

// USART1 goes to ENC, USART0 goes to RS232
void initENC(void)
{
  DDRA = 0;
  DDRB = 0b01000000; // MISO output
  DDRC = 0;
  DDRD = 0b10111010;// TX0, TX1, XCK1, CS, and reset output
  PORTA = 255;
  PORTB = 0b00000000;
  PORTC = 255;
  PORTD = 0b10100000; // CS and reset start high
  
  UBRR0L = 129; // 9600bps for 20MHz
  UBRR0H = 0;
  UCSR0A = 0;
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  UBRR1L = 0; // 10Mbps for 20MHz
  UBRR1H = 0;
  UCSR1A = 0;
  UCSR1C = (1 << UMSEL11) | (1 << UMSEL10); // USART in SPI mode
  UCSR1B = (1 << RXEN1) | (1 << TXEN1);
 
}

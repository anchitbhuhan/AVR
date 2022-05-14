/*
Q) Assuming that XTAL = 8MHz. Write a program to generate a square wave with a period of 2ms in pin PB3.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_init()
{
	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00);
	TCNT0 = 0;
	
	OCR0 = 124;

}

void delay()
{
	while((TIFR&(1<<OCF0)) == 0);
	//TCCR0 = 0;
	TIFR = (1 << OCF0);
}

int main(void)
{	
    DDRC |= (1 << 0);
	timer0_init();
	
    while (1)
    {
		PORTC ^= (1 << 0);
		delay();
    }
}


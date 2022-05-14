/*
Q) Assuming that XTAL = 8MHz. Write a program to generate a square wave with a period of 2ms in pin PB3.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_init()
{
	TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00) | (1 << COM00);

	TCNT0 = 0;
	OCR0 = 124;

}


int main(void)
{	
    DDRB |= (1 << PB3);
	timer0_init();
	
    while (1)
    {
    }
}


/*
Let’s define a problem statement for us. The simplest one being the LED flasher.
Let’s say, we need to flash an LED every 6 ms and we are have a CPU clock frequency of 32 kHz.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_init()
{
	TCCR0 |= (1 << CS00);
	TCNT0 = 0;
}

int main(void)
{	
    DDRC |= (1 << 0);
	timer0_init();
	
    while (1)
    {
		if(TCNT0 >= 191)
		{
			PORTC ^= (1 << 0);
			TCNT0	= 0;
		}
    }
}


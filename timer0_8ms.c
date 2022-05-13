/*
Now let’s change the above problem statement to the following. We need to flash an LED every 8 ms and we have an XTAL of 16 MHz.
Well, 8 ms is still low, but it’s good enough for the following illustration.
*/

#include <avr/io.h>
#include <avr/interrupt.h>

void timer0_init()
{
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TCNT0 = 0;
}

int main(void)
{	
    DDRC |= (1 << 0);
	timer0_init();
	
    while (1)
    {
		if(TCNT0 >= 124)
		{
			PORTC ^= (1 << 0);
			TCNT0	= 0;
		}
    }
}


#include <avr/io.h>
#include <avr/interrupt.h>

// initialize timer, interrupt and variable
void timer1_init()
{
	// set up timer with prescaler = 64 and CTC mode
	TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
	
	TCCR1A |= (1 << COM1A0);
	
	// initialize counter
	TCNT1 = 0;
	
	// initialize compare value
	OCR1A = 24999;
	
}

// this ISR is fired whenever a match occurs
// hence, toggle led here itself..

int main(void)
{	
	// initialize timer
	
	DDRD |= (1 << 5);
	timer1_init();
			
	// loop forever
	while(1)
	{
		// do nothing
		// whenever a match occurs, ISR is fired
		// toggle the led in the ISR itself
		// no need to keep track of any flag bits here
		// done!
	}
}
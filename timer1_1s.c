/*
 Okay, let’s make it loud and clear. We need to flash an LED every 2 seconds, i.e. at a frequency of 0.5 Hz. We have an XTAL of 16 MHz.
*/



#include <avr/io.h>
#include <avr/interrupt.h>

// global variable to count the number of overflows
volatile int tot_overflow;

// initialize timer, interrupt and variable
void timer1_init()
{
	// set up timer with prescaler = 8
	TCCR1B |= (1 << CS11);
	
	// initialize counter
	TCNT1 = 0;
	
	// enable overflow interrupt
	TIMSK |= (1 << TOIE1);
	
	// enable global interrupts
	sei();
	
	// initialize overflow counter variable
	tot_overflow = 0;
}

// TIMER1 overflow interrupt service routine
// called whenever TCNT1 overflows
ISR(TIMER1_OVF_vect)
{
	// keep a track of number of overflows
	tot_overflow++;
	
	// check for number of overflows here itself
	// 61 overflows = 2 seconds delay (approx.)
	if (tot_overflow >= 61) // NOTE: '>=' used instead of '=='
	{
		PORTC ^= (1 << 0);  // toggles the led
		// no timer reset required here as the timer
		// is reset every time it overflows
		
		tot_overflow = 0;   // reset overflow counter
	}
}

int main(void)
{
	// connect led to pin PC0
	DDRC |= (1 << 0);
	
	// initialize timer
	timer1_init();
	
	// loop forever
	while(1)
	{
		// do nothing
		// comparison is done in the ISR itself
	}
}

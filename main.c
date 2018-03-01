#include <msp430g2553.h>

/*
 * main.c
 */
int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR|=BIT0;

	while(1)
	{

		P1OUT|=BIT0;
		__delay_cycles(100000);
		P1OUT&=~BIT0;
		__delay_cycles(100000);

	}
	return 0;
}

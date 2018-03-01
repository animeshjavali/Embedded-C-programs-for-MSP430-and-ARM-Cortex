#include <msp430g2553.h>

/*
 * main.c
 */
int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR|=BIT0;
	P1DIR&=~BIT3;
	P1OUT&=~BIT0;
	P1REN|=BIT3;
	P1OUT|=BIT3;

	while(1)
	{
		if((P1IN&BIT3)==0)
		{
			P1OUT|=BIT0;
		}
		else
		{
			P1OUT&=~BIT0;
					__delay_cycles(100000);

		}


	}
	return 0;
}






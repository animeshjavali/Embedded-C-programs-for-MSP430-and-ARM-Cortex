#include <msp430g2553.h>

/*
 * main.c
 */
int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR=0XFF;
	P2DIR|=BIT0;

    P1OUT&=~0XFF;

	while(1)
	{

		P1OUT=~0X40;
		P2OUT|=BIT0;

	}
	return 0;
}




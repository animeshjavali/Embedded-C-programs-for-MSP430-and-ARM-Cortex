#include <msp430g2553.h>

/*
 * main.c
 */

int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR|=BIT1;
	P1DIR|=BIT2;
	P1DIR&=~BIT3;
    P1REN|=BIT3;
    P1OUT|=BIT3;
    P1DIR|=BIT0;
    P1DIR|=BIT6;
    P1OUT&=~BIT0;
    P1OUT&=~BIT6;
	while(1)
	{
		if((P1IN&BIT3)==0)
		{
			__delay_cycles(100000);
		P1OUT|=BIT1;//IN1=1
		P1OUT&=~BIT2;//IN2=0
		P1OUT|=BIT0;
		P1OUT&=~BIT6;
		//P1OUT|=BIT2;
		}
		else
		{
			P1OUT&=~BIT1;//IN1=0
		    P1OUT|=BIT2;//IN2=1
		    P1OUT&=~BIT0;

		    P1OUT|=BIT6;
		}

	}
	return 0;
}






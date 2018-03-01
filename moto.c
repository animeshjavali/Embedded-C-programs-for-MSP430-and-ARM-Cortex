#include <msp430g2553.h>

/*
 * main.c
 */
unsigned int count=0;
int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR|=BIT1;
	P1DIR|=BIT2;
	P1REN|=BIT3;
	P1OUT|=BIT3;
	P1DIR|=BIT0;
	P1DIR|=BIT6;
	while(1)
	{

		if((P1IN&BIT3)==0)
		{count++;
		if(count%2==0)
		{
         P1OUT|=BIT1;
         P1OUT&=~BIT2;
         P1OUT|=BIT0;
         P1OUT&=~BIT6;
		}
		else
		{
			P1OUT&=~BIT1;
			 P1OUT|=BIT2;
	         P1OUT|=BIT6;
	         P1OUT&=~BIT0;
		}}
		else
		{

		}

		}




}






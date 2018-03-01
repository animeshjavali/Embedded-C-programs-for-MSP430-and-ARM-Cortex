#include <msp430g2553.h>

/*
 * main.c
 */
void main(void) {
int i;

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	TA0CTL|=TASSEL_2
			+MC_1;//timer control register
    TA0CCR0=1000-1;

    P1SEL|=BIT2;
	P1DIR|=BIT2;
	TA0CCTL1=OUTMOD_7;
	while(1)
	{
		for(i=100;i<=1000;i++)
		{
			TA0CCR1=i;
			__delay_cycles(500);
		}
		for(i=999;i>=100;i--)
				{
					TA0CCR1=i;
					__delay_cycles(500);
				}
	}


}






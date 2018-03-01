#include <msp430g2553.h>

/*
 * main.c
 */
void main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	TA0CTL|=TASSEL_1+MC_1+TACLR;//timer control register
	TACCTL0|=CCIE;//timer capture control register
	TA0CCR0=32767;
	P1DIR|=BIT0;
	__bis_SR_register(GIE) ;
	while(1);

}

#pragma vector= TIMER0_A0_VECTOR
__interrupt void Timer(void)
{

	P1OUT^=BIT0;
}


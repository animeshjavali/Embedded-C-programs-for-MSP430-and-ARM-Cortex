#include <msp430g2553.h>


int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1IE|=BIT3;//ENABLE
	__bis_SR_register(GIE) ;// GIE WILL BE SET
	P1IES|=BIT3;//HIGH TO LOW TRANSITION
	P1DIR|=BIT6;
	P1OUT&=~BIT6;
	P1REN|=BIT3;
	P1OUT|=BIT3;
    while(1);

}

#pragma vector=PORT1_VECTOR
__interrupt void button(void)
{
	P1IES^=BIT3;
P1IFG&=~BIT3;//CLEAR INTERRUPT FLAG
P1OUT^=BIT6;//xor toggle
__delay_cycles(200000);

}




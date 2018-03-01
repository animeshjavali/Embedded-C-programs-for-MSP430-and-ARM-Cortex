#include <msp430g2553.h>

/*
 * main.c
 */
int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR|=BIT0;
	ADC10CTL0|=ADC10ON +ADC10IE +ADC10SHT_2 ;
	ADC10CTL1|=INCH_1 +	ADC10SSEL_3 ;
	ADC10AE0|=BIT1;//ANALOG CHANNEL 1(INCH_1)
	P1DIR|=BIT0;
	while(1)
	{
		ADC10CTL0|=ENC+ADC10SC;//start conversion
		__bis_SR_register(GIE);

	}
	return 0;
}

#pragma vector=ADC10_VECTOR

__interrupt void ADC(void)
{
	if(ADC10MEM>=512)
	{
		P1OUT|=BIT0;
		__delay_cycles(100000);
	}
	else
	{
		P1OUT&=~BIT0;
	__delay_cycles(100000);
	}
}



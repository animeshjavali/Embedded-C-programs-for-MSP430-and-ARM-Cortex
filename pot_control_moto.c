#include <msp430g2553.h>

/*
 * main.c
 */
void main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P1DIR|=BIT2;
	ADC10CTL0|=ADC10ON +ADC10IE +ADC10SHT_2 ;
	ADC10CTL1|=INCH_1 +	ADC10SSEL_3 ;
	ADC10AE0|=BIT1;//ANALOG CHANNEL 1(INCH_1)
	TA0CTL|=TASSEL_2+MC_1;//timer control register
	    TA0CCR0=723;

	    P1SEL|=BIT2;

		TA0CCTL1=OUTMOD_7;
	while(1)
		{
			ADC10CTL0|=ENC+ADC10SC;//start conversion
			__bis_SR_register(GIE);

		}

}
#pragma vector=ADC10_VECTOR

__interrupt void ADC(void)
{
	TA0CCR1=ADC10MEM;
}

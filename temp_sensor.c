#include <msp430g2553.h>

/*
 * main.c
 */
int volt;
int temp;
int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	ADC10CTL0|=ADC10ON +ADC10IE +ADC10SHT_2 ;
	ADC10CTL1|=INCH_10 +	ADC10SSEL_3 ; //input channel 1
	//ADC10AE0|=BIT1;//ANALOG CHANNEL 1(INCH_1)

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
	volt=ADC10MEM;
	temp=((ADC10MEM-673)*423)/1024;

	__no_operation();
}



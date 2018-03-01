#include  "msp430g2553.h"
#include <stdio.h>

#define     LCM_DIR               P1DIR
#define     LCM_OUT               P1OUT
char t[6]="0";
long IntDegC;
int temp;
//
// Define symbolic LCM - MCU pin mappings
// We've set DATA PIN TO 4,5,6,7 for easy translation
//
#define     LCM_PIN_RS            BIT0          // P1.0
#define     LCM_PIN_EN            BIT1          // P1.1
#define     LCM_PIN_D7            BIT7          // P1.7
#define     LCM_PIN_D6            BIT6          // P1.6
#define     LCM_PIN_D5            BIT5          // P1.5
#define     LCM_PIN_D4            BIT4          // P1.4


#define     LCM_PIN_MASK  ((LCM_PIN_RS | LCM_PIN_EN | LCM_PIN_D7 | LCM_PIN_D6 | LCM_PIN_D5 | LCM_PIN_D4))

#define     FALSE                 0
#define     TRUE                  1

void PulseLcm()
{
   // pull EN bit low
   LCM_OUT &= ~LCM_PIN_EN;
    __delay_cycles(200);
	// pull EN bit high
    LCM_OUT |= LCM_PIN_EN;
   __delay_cycles(200);
	// pull EN bit low again
   LCM_OUT &= (~LCM_PIN_EN);
    __delay_cycles(200);
}

// Parameters:
//
//    ByteToSend - the single byte to send
//
//    IsData - set to TRUE if the byte is character data
//                  FALSE if its a command

void SendByte(char ByteToSend, int IsData)
{
    //
    // clear out all pins
    //
    LCM_OUT &= (~LCM_PIN_MASK);
    //
    // set High Nibble (HN) -
    // usefulness of the identity mapping
    // apparent here. We can set the
    // DB7 - DB4 just by setting P1.7 - P1.4
    // using a simple assignment
    //
    LCM_OUT |= (ByteToSend & 0xF0);

    if (IsData == TRUE)
    {
        LCM_OUT |= LCM_PIN_RS;
    }
    else
    {
        LCM_OUT &= ~LCM_PIN_RS;
    }

    // set up the input voltages to the LCM.
  
   
    PulseLcm();
     //
    // set Low Nibble (LN) -
    // usefulness of the identity mapping
    // apparent here. We can set the
    // DB7 - DB4 just by setting P1.7 - P1.4
    // using a simple assignment
    //
    LCM_OUT &= (~LCM_PIN_MASK);
    LCM_OUT |= ((ByteToSend & 0x0F) << 4);

    if (IsData == TRUE)
    {
        LCM_OUT |= LCM_PIN_RS;
    }
    else
    {
        LCM_OUT &= ~LCM_PIN_RS;
    }

    //
    // we've set up the input voltages to the LCM.
    // Now tell it to read them.
    //
    PulseLcm();
}



// Routine Desc:

// Set the position of the cursor on the screen

void LcmSetCursorPosition(char Row, char Col)
{
    char address;

    //
    // construct address from (Row, Col) pair
    //
    if (Row == 0)
    {
        address = 0;
    }
    else
    {
        address = 0x40;
    }

    address |= Col;

    SendByte(0x80 | address, FALSE);
}


//
// Routine Desc:
//
// Clear the screen data and return the
// cursor to home position

void ClearLcmScreen()
{
    //
    // Clear display, return home
    //
    SendByte(0x01, FALSE);
    SendByte(0x02, FALSE);
}


//
// Routine Desc:
//
// Initialize the LCM after power-up.
//
// Note: This routine must not be called twice on the
//           LCM. This is not so uncommon when the power
//           for the MCU and LCM are separate.

void InitializeLcm(void)
{
    //
    // set the MSP pin configurations
    // and bring them to low
    //
    LCM_DIR |= LCM_PIN_MASK;
    LCM_OUT &= ~(LCM_PIN_MASK);


    //
    // wait for the LCM to warm up and reach
    // active regions. Remember MSPs can power
    // up much faster than the LCM.
    //
    __delay_cycles(100000);


    //
    // initialize the LCM module
    //
    // 1. Set 4-bit input
    //
    LCM_OUT &= ~LCM_PIN_RS;
    LCM_OUT &= ~LCM_PIN_EN;

    LCM_OUT = 0x20;
    PulseLcm();

    //
    // set 4-bit input - second time.
    // (as reqd by the spec.)
    //
    SendByte(0x28, FALSE);

    //
    // 2. Display on, cursor on, blink cursor
    //
    SendByte(0x0E, FALSE);

    //
    // 3. Cursor move auto-increment
    //
    SendByte(0x06, FALSE);
}


//
// Routine Desc
//
// Print a string of characters to the screen

void convert_temp(char tempr)
{
	t[0]=(tempr/10)+48;
	t[1]=(tempr%10)+48;
	t[2]='d';
	t[3]='e';
	t[4]='g';
	t[5]='C';
	t[6]='\0';
}
void PrintStr(char *Text)
{
    char *c;

    c = Text;

    while ((c != 0) && (*c != 0))
    {
        SendByte(*c, TRUE);
        c++;
    }
}
// main entry point to the sketch


void main(void)
{
	WDTCTL =WDT_ADLY_1000  ;
    ADC10CTL1 = INCH_10 + ADC10DIV_3;         // Temp Sensor ADC10CLK/4
      ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE;
      __delay_cycles(100000);
    InitializeLcm();

    ClearLcmScreen();


    while (1)
    {


    	    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    	    __bis_SR_register(GIE);        // LPM0 with interrupts enabled


    	    // oC = ((A10/1024)*1500mV)-986mV)*1/3.55mV = A10*423/1024 - 278
    	    temp = ADC10MEM;
    	    IntDegC = ((temp - 673) * 423) / 1024;
    	    convert_temp(IntDegC);
            SendByte(0xC0,FALSE);
            PrintStr(t);
       __delay_cycles(1000);
}

}
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)

{
 // __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}


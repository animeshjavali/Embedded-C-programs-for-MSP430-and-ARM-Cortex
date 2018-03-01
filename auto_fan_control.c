#include <msp430g2553.h>
#define LCD_DIR P1DIR
#define LCD_OUT P1OUT
#define  LCD_RS BIT0
#define  LCD_EN BIT1
#define  LCD_D7 BIT7
#define  LCD_D6 BIT6
#define  LCD_D5 BIT5
#define  LCD_D4 BIT4

#define  LCD_MASK ((LCD_RS| LCD_EN|LCD_D7|LCD_D6|LCD_D5|LCD_D4))
#define TRUE 1
#define FALSE 0
int i=0;
void LCD_PUSH()
{
	LCD_OUT&=~LCD_EN;//enable low
	__delay_cycles(100);
	LCD_OUT|=LCD_EN;//enable high
	__delay_cycles(100);
	LCD_OUT&=~LCD_EN;//enable low
		__delay_cycles(100);
}
void SEND(char data,int type)
{
	LCD_OUT&=~LCD_MASK;
	LCD_OUT|=(data & 0xf0);

	if(type==TRUE)
	{
		LCD_OUT|=LCD_RS;
	}
	else
	{
		LCD_OUT&=~LCD_RS;
	}
	LCD_PUSH();
	LCD_OUT&=~LCD_MASK;//clear again from the pins.
	LCD_OUT|=((data&0x0f)<<4);
	if(type==TRUE)
		{
			LCD_OUT|=LCD_RS;
		}
		else
		{
			LCD_OUT&=~LCD_RS;
		}
		LCD_PUSH();
	}

void LCD_INIT_TEMP()
{
LCD_DIR=0XFF;
LCD_OUT&=~LCD_MASK;
__delay_cycles(100000);
LCD_OUT=0X20;//ENABLE 4 BIT MODE.
LCD_PUSH();
SEND(0X28, FALSE);//COMMANDS
SEND(0X0E,FALSE);
SEND(0X06,FALSE);
}
void LCD_INIT_TIMER()
{
LCD_DIR=0XFF;
LCD_OUT&=~LCD_MASK;
__delay_cycles(100000);
LCD_OUT=0X20;//ENABLE 4 BIT MODE.
LCD_PUSH();
SEND(0X28, FALSE);//COMMANDS
SEND(0X0E,FALSE);
SEND(0X06,FALSE);

}
void LCD_CLEAR()
{
	SEND(0X01,FALSE);//clear lcd.
	SEND(0X02,FALSE);

}
void PRINTTEMP(char c[])
{

	while((c[i] !=0))
	{
		SEND(c[i], TRUE);
		i++;
	}
	}
void PRINTTIMER(char c[])
{

	while((c[i] !=0))
	{
		__delay_cycles(100000);
		c[i]+=1;
		if(c[i]==60)
			c[i]

		SEND(c[i], TRUE);
		i++;
	}
	}




void main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	LCD_INIT_TEMP();
	 LCD_CLEAR();

	 char temp[]="25degC";
__delay_cycles(100000);
     PRINTTEMP(temp);
     char time[]="        15:45:00";
     PRINTTIMER(time);
	 while(1);


}






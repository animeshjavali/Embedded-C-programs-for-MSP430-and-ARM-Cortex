
#include "SPI.h"
#include "LCD_5110_SPI.h"

LCD_5110_SPI myScreen(PA_7,    // Chip Select
                      PA_2,    // Data/Command
                      PB_5,    // Reset
                      PA_6,    // Backlight - not used in my program
                      PUSH2);  // Push Button 2 - not used in my program


void setup()
{
 SPI.setModule(2);      // using the third SPI port
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128); // for LM4F120H5QR DIV2 = 4 MHz !
    
    myScreen.begin();
    myScreen.setContrast(0x48);  // try different values here to suit your display
    myScreen.clear();
    myScreen.setFont(0);
    // myScreen.text(0, 0, "Initializing");
    
   
myScreen.text(0,0,"HELLO,WORLD!"); // put your main code here, to run repeatedly:
 

    delay(1000);

    myScreen.clear();
    
    
  
}

void loop()
{


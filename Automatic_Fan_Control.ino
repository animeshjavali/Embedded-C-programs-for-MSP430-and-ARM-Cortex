int readval,temp,i;

void setup()
{
 Serial.begin(9600);
// pinMode(10,INPUT);
analogReference(INTERNAL1V5);//Refer to internal temperature of MSP430.
pinMode(9,OUTPUT);
}

void loop()
{
readval=analogRead(TEMPSENSOR);// Read the temperature value.
temp=((readval-673)*423)/1024;// Convert tempeartue to degree C.

if(temp>25)// If temperature is greater than 25 degree C, turn on a fan.
{
for(i=2;i<256;i++)
{
  Serial.println(temp,DEC);

analogWrite(9,i);// Speed Modulated DC motor.
delay(100);
}
}
else
analogWrite(9,0);// Turn off the fan.


}

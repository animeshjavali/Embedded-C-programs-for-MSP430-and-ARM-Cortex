int readval;
float readvolt;
float temp;
void setup()
{
  pinMode(A10,INPUT);
  pinMode(2,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
readval=analogRead(A10);
readvolt=(5./1023.)*readval;
temp= readvolt*100;
Serial.print("Sensor data is ");
Serial.println(readvolt);
delay(500);
  
}

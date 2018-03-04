int readval,writeval;
float readvolt,writevolt;
void setup()
{
 pinMode(3,INPUT);
 pinMode(2,OUTPUT);
  
}

void loop()
{
readval=analogRead(3);
writeval=readval;
writevolt=(5./1023.)*writeval;
analogWrite(2,writevolt);

}

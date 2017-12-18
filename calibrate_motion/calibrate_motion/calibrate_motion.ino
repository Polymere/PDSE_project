void setup()
{
  pinMode(5,INPUT);
  pinMode(7,INPUT);
  Serial.begin(9600);
}
boolean d1=false;
boolean d2=false;
void loop()
{
  d1=digitalRead(5)==1;
  d2=digitalRead(7)==1;
  if (d1 && d2)
   Serial.println("Overlap");
  else if (d1)
   Serial.println("Detection on sensor 1");
  else if (d2)
   Serial.println("Detection on sensor 2");
  else 
   Serial.println("No detection");
   delay(500);
}


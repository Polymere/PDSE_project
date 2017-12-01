#include <Servo.h>
Servo servoMain; // Define our Servo

void setup()
{
   servoMain.attach(10); // servo on digital pin 10
   Serial.begin(9600);
 }

void loop()
{
   servoMain.write(135);  // Turn Servo Left to 45 degrees
   delay(10000);
   Serial.println("<3");
}



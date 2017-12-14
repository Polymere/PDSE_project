#include "Arduino.h"
#include "my_motion.h"

 motion::motion(char pin, char id)
 {
     pinMode(pin,INPUT);
    _pin=pin;
    _id=id;
#if DEBUG_MOTION ==1
    if (!Serial)
      Serial.begin(9600);
    Serial.print("Motion sensor \t");
    Serial.print(_id);
    Serial.println("initialized");
#endif


 }
bool motion :: get_motion()
{
#if DEBUG_MOTION==1
      Serial.print("Motion sensor :");
      Serial.print(_id);
      Serial.print(" \t has value :");
      Serial.println(digitalRead(_pin));
#endif
    return digitalRead(_pin)==1;

  }

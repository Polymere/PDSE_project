#include "Arduino.h"
#include "my_prox.h"

prox::prox (char  trig_pin, char echo_pin, char id)
{
    pinMode(trig_pin, OUTPUT);
    digitalWrite(trig_pin, LOW);
    _trig_pin=trig_pin;
    _echo_pin=echo_pin;
    _id=id;
#if DEBUG_PROX==1
    if(!Serial)
      Serial.begin(9600);
    Serial.print("Proximity sensor \t");
    Serial.print(_id);
    Serial.println("initialized");
#endif
}
char prox::get_state(char prev_state)
{
  char state=0;
  int dist=get_dist();
  if(dist==-1 || dist>MAX_DIST)
    return state; //Default case (no user nearby)
  else{
     if (dist>prev_state*WIDTH+THR)
       state= prev_state+1;
     else if (dist<(prev_state-1)*WIDTH-THR)
       state= prev_state-1;
     else
       state= prev_state; //Proof read
  }
#if DEBUG_PROX==1

  Serial.print("From state");
  Serial.print(prev_state);
  Serial.print("to ");
  Serial.print(state);
  Serial.print("on sensor ");
  Serial.println(_id);

#endif
   return state;
}
int prox:: get_dist( )
{
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  int cm;
  digitalWrite(_trig_pin, HIGH);
  delayMicroseconds(PULSE_LENGHT);
  digitalWrite(_trig_pin, LOW);
  while ( digitalRead(_echo_pin) == 0 );
  t1 = micros();
  while ( digitalRead(_echo_pin) == 1);
  t2 = micros();
  pulse_width = t2 - t1;
  cm = pulse_width / 58;
  if(pulse_width>MAX_PULSE_RANGE)
    cm=-1;
#if DEBUG_PROX==1
  if (pulse_width > MAX_PULSE_RANGE )
      Serial.println("Out of range");
  else {
      Serial.print("Proximity on sensor \t");
      Serial.print(_id);
      Serial.print(":\t");
      Serial.print(cm);
      Serial.println(" cm");
  }
#endif
  return cm;
}



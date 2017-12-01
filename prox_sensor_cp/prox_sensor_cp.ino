/**
 * HC-SR04 Demo
 * Demonstration of the HC-SR04 Ultrasonic Sensor
 * Date: August 3, 2016
 * 
 * Description:
 *  Connect the ultrasonic sensor to the Arduino as per the
 *  hardware connections below. Run the sketch and open a serial
 *  monitor. The distance read from the sensor will be displayed
 *  in centimeters and inches.
 * 
 * Hardware Connections:
 *  Arduino | HC-SR04 
 *  -------------------
 *    5V    |   VCC     
 *    7     |   Trig     
 *    8     |   Echo     
 *    GND   |   GND
 *  
 * License:
 *  Public Domain
 */

// Pins

byte trig_pin[1];
byte echo_pin[1];
boolean serial_display[1];

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;
byte st=0;

void setup_prox(boolean my_serial_display, 
                byte my_trig_pin,
                byte my_echo_pin,
                byte id)
{
    pinMode(my_echo_pin, OUTPUT);
    digitalWrite(my_trig_pin, LOW);
    trig_pin[id]=my_trig_pin;
    echo_pin[id]=my_echo_pin;
    serial_display[id]=my_serial_display;
    if(my_serial_display)
      Serial.begin(9600);  
}

float prox_get_dist(byte id)
{
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  digitalWrite(trig_pin[id], HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin[id], LOW);
  while ( digitalRead(echo_pin[id]) == 0 );
  // Measure how long the echo pin was held high (pulse width)
  t1 = micros();
  while ( digitalRead(echo_pin[id]) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  // Print out results
  if(pulse_width>MAX_DIST)
    cm=-1;
   
  if(serial_display[id]==true)
  {
    if (pulse_width > MAX_DIST )
      Serial.println("Out of range");
    else {
      Serial.print("Proximity on sensor \t");
      Serial.print(id);
      Serial.print(":\t");
      Serial.print(cm);
      Serial.println(" cm");
     }
  }
  return cm;
}
byte prox_get_state(byte id, byte n, byte prev_state,
                    int max_dist, int min_dist,int thr)
{
  byte state=0;
  float dist=prox_get_dist(id);
  if(dist==-1 || dist>max_dist)
    return state; //Default case (no user nearby)
  else
  {
     float width=(max_dist-min_dist)/n; //Take care of the conversion
     if (dist>prev_state*width+thr)
       state= prev_state+1;
     else if (dist<(prev_state-1)*width-thr)
       state= prev_state-1;
     else
       state= prev_state; //Proof read
  }
   if(serial_display[id]==true)
   {
     Serial.print("From state");
     Serial.print(prev_state);
     Serial.print("to ");
     Serial.print(state);
     Serial.print("on sensor ");
     Serial.println(id);
   }
     
   return state;
}
void setup()
{
  setup_prox(true,7,8,1);
  st=0;
}
void loop()
{
  st=prox_get_state(1,4,st,350,0,25);
  delay(1);
}


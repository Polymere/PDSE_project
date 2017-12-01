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



// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;
byte st=0;


float prox_get_dist()
{
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  while ( digitalRead(8) == 0 );
  // Measure how long the echo pin was held high (pulse width)
  t1 = micros();
  while ( digitalRead(8) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;
  // Print out results
  if(pulse_width>MAX_DIST)
    cm=-1;
/*
    if (pulse_width > MAX_DIST )
      Serial.println("Out of range");
    else {
      
      Serial.print(cm);
      Serial.print(" cm \t");
     }
     */
  return cm;
}
byte prox_get_state(byte n, byte prev_state,
                    int max_dist, int min_dist,int thr)
{
  byte state=0;
  float dist=prox_get_dist();
  if((dist==-1) || (dist>max_dist))
    return -1; //Default case (no user nearby)
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

   return state;
}
void setup()
{
    pinMode(7, OUTPUT);
    digitalWrite(7, LOW);
    Serial.begin(9600);
    Serial.println("Finished setup");
    st=0;
}
void loop()
{
  Serial.print("Old state");
  Serial.print(st);
  st=prox_get_state(4,st,350,0,25);
  Serial.print("New state");
  Serial.println(st);
  delay(1000);
}


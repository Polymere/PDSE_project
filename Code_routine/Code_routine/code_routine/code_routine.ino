#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
Servo servoMain; // Define our Servo
const int LED_PIN = 4;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, LED_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800); 

int state = 0; // 0=empty, 1 =full, variable d'état dépendant du capteur ultrasonic vertical
int step = 1;  //step dans le processus d'ouverture
int led=0; // état de proximité des gens

const int PIR_PIN = 7; // Input for HC-S501
const int PIR2_PIN = 3;
const int TRIG_PIN = 8;//trash
const int ECHO_PIN = 9;//trash
const int TRIG2_PIN = 5; //people
const int ECHO2_PIN = 6;//people


const byte eye_1[8][8]={{0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {1, 1, 1, 1, 1, 1, 1, 1},
                        {0, 1, 0, 1, 1, 0, 1, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0}};

const byte eye_2[8][8]={{0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 1, 1, 0, 0},
                        {0, 1, 0, 1, 1, 0, 1, 0},
                        {1, 0, 0, 1, 1, 0, 0, 1},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0}};

const byte eye_3[8][8]={{0, 0, 0, 1, 1, 0, 0, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {1, 0, 0, 1, 1, 0, 0, 1},
                        {1, 0, 0, 1, 1, 0, 0, 1},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0}};

const byte cross[8][8]={{1, 0, 0, 0, 0, 0, 0, 1},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {1, 0, 0, 0, 0, 0, 0, 1}};  
                                 
const uint16_t color = matrix.Color(0,150,0);

void setup() {
  // put your setup code here, to run once:
  pinMode(PIR_PIN, INPUT);
  pinMode(PIR2_PIN, INPUT);
  
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  
  pinMode(TRIG2_PIN, OUTPUT);
  digitalWrite(TRIG2_PIN, LOW);

  pinMode(LED_PIN, OUTPUT);
  matrix.setBrightness(10);
  
  servoMain.attach(10); // servo on digital pin 10
  servoMain.write(92);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int pirValue; // Place to store read PIR Value
  int pirValue2;
  pirValue = digitalRead(PIR_PIN);
  Serial.print(pirValue);
  Serial.println(" pyro 1 \t");
  pirValue2 = digitalRead(PIR2_PIN);
  Serial.print(pirValue2);
  Serial.println(" pyro 2 \t");
   pirValue = digitalRead(PIR_PIN);
  
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width; //distance of the trash
  float cm;
  float cm_2; //distance of the people

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN) == 0 );
  
  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  //of sound in air at sea level (~340 m/s).
  cm = pulse_width / 58.0;

  // Print out results
  Serial.print(cm);
  Serial.println(" cm (trash)\t");

//********************* people detection sensor**************************//
  digitalWrite(TRIG2_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2_PIN, LOW);

  while ( digitalRead(ECHO2_PIN) == 0 );
  
  t1 = micros();
  while ( digitalRead(ECHO2_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  cm_2 = pulse_width / 58.0;

  Serial.print(cm_2);
  Serial.println(" cm (people) \t");

  if(state==0)
  {
    if(cm_2 > 200) //mettre different cases
    {
      led=0;
    }
    else if (cm_2 <= 200 && cm_2 > 100)
    {
       led=1;  
    }
    else if (cm_2 <= 100 && cm_2 > 50)
    {
      led =2;
    }
    else
    {
      led =3;
    }
  }
  else if (state==1 && cm_2 <= 200)
  {
    led=4;  
  }
  else
  {
    led=0;  
  }
  Serial.print(led);
  Serial.println(" led \t");
    
  delay(1000);
  
  switch (step)
  {
  case 1: //Etat initial, le moteur est fermé
    if((state==1)&&(pirValue==1 || pirValue2==1))
     {if (cm > 35)    //astucieux!!
      state=0;
      delay(2000);
      }
    
    if((state==0)&&(pirValue==1 || pirValue2==1)) // si la poubelle est vide et que le PIR détecte quelquechose, on passe à la step d'après.
    step=2;
  break;
  case 2:
    Serial.println("Opening");
//    servoMain.attach(10);
//    delay(10);
    servoMain.write(102);
    delay(2200);
    servoMain.write(92);
    step=3;
    break;
  case 3:
    Serial.println("Charbon's hand is stuck");
    if (pirValue==0 && pirValue2==0)
     {delay(2000);
    step=4;}
    break;
  case 4:
    Serial.println("Closing");
    servoMain.write(82);
    delay(2200);
    servoMain.write(92);
//    servoMain.detach();
    delay(3000);
    if (cm < 35)
      state=1;
    step=1;
    break;
  }  

 switch (led) //mettre les changements de led selon l'état
 {
  int i;
  int j;
 case 0:
    for (i=0;i<8;i++)
    {
      for (j=0;j<8;j++)
      {
        matrix.fillScreen(0);
        }
      }
    break;
 case 1:
    matrix.fillScreen(0);
    for (i=0;i<8;i++)
    {
      for (j=0;j<8;j++)
      {
        if (eye_1[i][j]==1)
          matrix.drawPixel(i,j,color);
        }
        matrix.show();
      }
    break;
  case 2:
    matrix.fillScreen(0);
    for (i=0;i<8;i++)
    {
      for (j=0;j<8;j++)
      {
        if (eye_2[i][j]==1)
          matrix.drawPixel(i,j,color);
        }
        matrix.show();
      }
    break; 
  case 3:
    matrix.fillScreen(0);
    for (i=0;i<8;i++)
    {
      for (j=0;j<8;j++)
      {
        if (eye_3[i][j]==1)
          matrix.drawPixel(i,j,matrix.Color(0,150,0));
        }
        matrix.show();
      }
    break;
   case 4:
    matrix.fillScreen(0);
    for (i=0;i<8;i++)
    {
      for (j=0;j<8;j++)
      {
        if (cross[i][j]==1)
          matrix.drawPixel(i,j,color);
        }
        matrix.show();
      }
    break;
 }
}

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>


#define Camilla 0

#if Camilla==1
#include <Wire.h>
#include <UnoWiFiDevEd.h>
#endif


#define DEBUG_PIR 0
#define DEBUG_PROX 0

#define WASTE_ID 0
#define ALU_ID 1
#define GLASS_ID 2
#define PET_ID 3
#define PAPER_ID 4


Servo servoMain; // Define our Servo
const int LED_PIN = 3;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8,1,2, LED_PIN,
    NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS+ NEO_MATRIX_PROGRESSIVE+NEO_TILE_TOP+NEO_TILE_LEFT,
    NEO_GRB            + NEO_KHZ800);

const char signMessage1[] PROGMEM  = {"HTTP/1.1 200 OK"};
const char signMessage2[] PROGMEM  = {"Content-Type: text/html"};
const char signMessage3[] PROGMEM  = {"<html><head></head><body>"};
const char signMessage4[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/1/0','_parent');w.close();\"value='Waste'><br>"};
const char signMessage5[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/1/1','_parent');w.close();\"value='Aluminium'><br>"};
const char signMessage6[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/1/2','_parent');w.close();\"value='Glass'><br>"};
const char signMessage7[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/1/3','_parent');w.close();\"value='PET'><br>"};
const char signMessage8[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/1/4','_parent');w.close();\"value='Paper'><br>"};
const char signMessage9[] PROGMEM  = {"</body></html>"};



const byte PIR_PIN = 11; // Input for HC-S501
const byte PIR2_PIN = 12;
const byte TRIG_PIN = 8;//trash
const byte ECHO_PIN = 9;//trash
const byte TRIG2_PIN = 5; //people
const byte ECHO2_PIN = 4;//people


const byte eye_1[8][8] PROGMEM={{0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {1, 1, 1, 1, 1, 1, 1, 1},
                        {0, 1, 0, 1, 1, 0, 1, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0}};

const byte eye_2[8][8] PROGMEM={{0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 1, 1, 1, 1, 0, 0},
                        {0, 1, 0, 1, 1, 0, 1, 0},
                        {1, 0, 0, 1, 1, 0, 0, 1},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0}};

const byte eye_3[8][8] PROGMEM ={{0, 0, 0, 1, 1, 0, 0, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {1, 0, 0, 1, 1, 0, 0, 1},
                        {1, 0, 0, 1, 1, 0, 0, 1},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0}};

const byte cross[8][8] PROGMEM={{1, 0, 0, 0, 0, 0, 0, 1},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0},
                        {0, 0, 1, 0, 0, 1, 0, 0},
                        {0, 1, 0, 0, 0, 0, 1, 0},
                        {1, 0, 0, 0, 0, 0, 0, 1}};  
                                
st uint16_t colorAlu=matrix.Color(128,128,128);
const uint16_t colorGlass=matrix.Color(34,191,13);
const uint16_t colorPet=matrix.Color(16,55,209);
const uint16_t colorWaste=matrix.Color(216,21,21);
const uint16_t colorPaper=matrix.Color(255,255,0);
const uint16_t color[NUMBER_TYPE] ={colorWaste,colorAlu,colorGlass,colorPet,colorPaper};

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
    matrix.begin();
    servoMain.attach(10); // servo on digital pin 10
    servoMain.write(92);
#if Camilla==1
    Wifi.begin();
    Wifi.println(F("Web Server is up"));
    unsigned long t1=millis()
    
    
  while(t1<10000)
  {
    if(Wifi.available())
      process(Wifi);
     else 
        Serial.println("Not available");
  }
#endif
    Serial.begin(9600);
}

byte pirValue; // Place to store read PIR Value
byte pirValue2;

void update_PIR()
{
    pirValue = digitalRead(PIR_PIN);
    pirValue2 = digitalRead(PIR2_PIN);
#if DEBUG_PIR==1
    Serial.print(pirValue);
    Serial.println(F"( pyro 1 \t"));
    Serial.print(pirValue2);
    Serial.println(F(" pyro 2 \t"));
#endif
    return;
}

int get_dist(byte echo,byte trig)
{
    unsigned long t1;
    unsigned long t2;
    int cm;
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    while ( digitalRead(echo) == 0 );
    t1 = micros();
    while ( digitalRead(echo) == 1);
    t2 = micros();
    cm = (t2 - t1) / 58;
    return cm;
}

void loop() {
    static int level;
    static int people;
    static boolean trash_full = false; // 0=empty, 1 =full, variable d'état dépendant du capteur ultrasonic vertical
    static byte step = 1;  //step dans le processus d'ouverture
    static byte led_state=3; // état de proximité des gens
    static boolean motion_detected=false;

    update_PIR();
    motion_detected=(pirValue==1 || pirValue2==1);
    level=get_dist(ECHO_PIN,TRIG_PIN);

    people=get_dist(ECHO2_PIN,TRIG2_PIN);
    #if DEBUG_PROX ==1
    Serial.print(level);
    Serial.println(F(" cm (level) \t"));
    Serial.print(people);
    Serial.println(F(" cm (people) \t"));
    #endif
    
    led_state=get_led_state(people,trash_full,led_state);

    #if DEBUG_PROX==1
    Serial.print(led_state);
    Serial.println(F(" led \t"));
    #endif
    
    delay(100);
    
    switch (step)
    {
    case 1: //Etat initial, le moteur est fermé
      if( trash_full && motion_detected){
          if (level > 35){    //astucieux!!
            trash_full=false;
            delay(2000);
          }
      if(!trash_full&&motion_detected) // si la poubelle est vide et que le PIR détecte quelquechose, on passe à la step d'après.
        step=2;
      break;
    case 2:
      Serial.println(F("Opening"));
      servoMain.write(102);
      delay(2200);
      servoMain.write(92);
      step=3;
      break;
    case 3:
      Serial.println(F("Charbon's hand is stuck"));
      if (!motion_detected){
        delay(2000);
        step=4;
      }
      break;
    case 4:
      Serial.println(F("Closing"));
      servoMain.write(82);
      delay(2200);
      servoMain.write(92);
      delay(3000);
      if (level < 35)
          trash_full=true;
      step=1;
      break;
    }  

switch (led_state) //mettre les changements de led selon l'état
{
    int i;
    int j;
case 3:
    matrix.fillScreen(0);
    matrix.show();
    break;
case 2:
    matrix.fillScreen(0);
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
        {
        if (eye_1[i][j]==1)
        {
            matrix.drawPixel(i,j,color[trash_type]);
            matrix.drawPixel(i,j+8,color[trash_type]);
        }
        }
        }
        matrix.show();
    break;
    case 1:
    matrix.fillScreen(0);
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
        {
        if (eye_2[i][j]==1)
        {
            matrix.drawPixel(i,j,color[trash_type]);
            matrix.drawPixel(i,j+8,color[trash_type]);
        }
        }
    }
    matrix.show();
    break; 
    case 0:
    matrix.fillScreen(0);
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
        {
        if (eye_3[i][j]==1)
        {
            matrix.drawPixel(i,j,color[trash_type]);
            matrix.drawPixel(i,j+8,color[trash_type]);
        }
        }
    }
    matrix.show();
    break;
    case 4:
    matrix.fillScreen(0);
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
        {
        if (cross[i][j]==1)
        {
            matrix.drawPixel(i,j,colorWaste);
            matrix.drawPixel(i,j+8,colorWaste);
        }
        }
    }
    matrix.show();
    break;
}
}
}

#define WIDTH (200.0-0.0)/(4.0)
#define THR 25

byte get_led_state(int distance,boolean full,byte prev_state)
{
    byte state;
    if(!full)
    {
        if (distance>prev_state*WIDTH+THR)
            state= prev_state+1;
        else if (distance<(prev_state-1)*WIDTH-THR)
            state= prev_state-1;
        else 
            state=prev_state;
    }
    else
        state=4;
    return state;
    
}
#if Camilla==1
/*
void process(WifiData client) 
{
    // read the command
    String command = client.readStringUntil('/');

    // is "digital" command?
    if (command == "webserver") 
    WebServer(client);
    if (command == "digital")
    digitalCommand(client);
}

void WebServer(WifiData client) 
{
    
            client.println(signMessage1);
            client.println(signMessage2);
            client.println(signMessage3);
            
            client.print(signMessage4);
            client.print(signMessage5);
            client.print(signMessage6);
            client.print(signMessage7);
            client.print(signMessage8);

            client.print(signMessage9);
            
            client.print(DELIMITER); // very important to end the communication !!!
        
}
int trash_type;
void digitalCommand(WifiData client) 
{
    int command, trash_type = 0;
    command = client.parseInt();  
    // If the next character is a '/' it means we have an URL
    // with a value like: "/digital/0/1"
    if (client.read() == '/') {
        trash_type = client.parseInt();
    }
}*/
#endif

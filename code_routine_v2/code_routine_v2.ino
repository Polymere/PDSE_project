  #include <Adafruit_GFX.h>
  #include <Adafruit_NeoMatrix.h>
  #include <Adafruit_NeoPixel.h>
  #include <Servo.h>
  #include <Wire.h>
  #include <UnoWiFiDevEd.h>
  #define DEBUG_PIR 0
  #define DEBUG_PROX 1
  Servo servoMain; // Define our Servo
  const int LED_PIN = 3;
  Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8,1,2, LED_PIN,
    NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS+ NEO_MATRIX_PROGRESSIVE+NEO_TILE_TOP+NEO_TILE_LEFT,
    NEO_GRB            + NEO_KHZ800);

  const char signMessage1[] PROGMEM  = {"HTTP/1.1 200 OK"};
  const char signMessage2[] PROGMEM  = {"Content-Type: text/html"};
  const char signMessage3[] PROGMEM  = {"<html><head></head><body>"};
  const char signMessage4[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/1/0','_parent');w.close();\"value='PET'><br>"};
  const char signMessage5[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/1/1','_parent');w.close();\"value='ALU'><br>"};
  const char signMessage6[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/2/0','_parent');w.close();\"value='Reactivate'><br>"};
  const char signMessage7[] PROGMEM  = {"</body></html>"};

  
  
  int state = 0; // 0=empty, 1 =full, variable d'état dépendant du capteur ultrasonic vertical
  int step = 1;  //step dans le processus d'ouverture
  int led=0; // état de proximité des gens
  
  const int PIR_PIN = 11; // Input for HC-S501
  const int PIR2_PIN = 12;
  const int TRIG_PIN = 8;//trash
  const int ECHO_PIN = 9;//trash
  const int TRIG2_PIN = 5; //people
  const int ECHO2_PIN = 4;//people
  
  
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
    matrix.begin();
    servoMain.attach(10); // servo on digital pin 10
    servoMain.write(92);

    Wifi.begin();
    Wifi.println(F("Web Server is up"));

     while(Wifi.available()){
      process(Wifi);
    }
    delay(50);
    
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
    unsigned long pulse_width; //distance of the trash
    float cm;
    
  
    // Hold the trigger pin high for at least 10 us
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
  
    // Wait for pulse on echo pin
    while ( digitalRead(echo) == 0 );
    
    // Measure how long the echo pin was held high (pulse width)
    // Note: the micros() counter will overflow after ~70 min
    t1 = micros();
    while ( digitalRead(echo) == 1);
    t2 = micros();
    pulse_width = t2 - t1;
  
    // Calculate distance in centimeters and inches. The constants
    // are found in the datasheet, and calculated from the assumed speed 
    //of sound in air at sea level (~340 m/s).
    cm = pulse_width / 58;
  
    // Print out results
    return cm;
    
    
    
  }
  int level;
  int people;
  void loop() {
    
    // put your main code here, to run repeatedly:
    update_PIR();
    level=get_dist(ECHO_PIN,TRIG_PIN);
   
    people=get_dist(ECHO2_PIN,TRIG2_PIN);
     #if DEBUG_PROX ==1
    Serial.print(level);
    Serial.println(F(" cm (level) \t"));
    Serial.print(people);
    Serial.println(F(" cm (people) \t"));
    #endif
    
  
  //********************* people detection sensor**************************//
    
    if(state==0)
    {
      if(people > 200) //mettre different cases
      {
        led=0;
      }
      else if (people <= 200 && people > 175)
      {
         led=1;  
      }
      else if (people <= 175 && people > 150)
      {
        led =2;
      }
      else
      {
        led =3;
      }
    }
    else if (state==1 && people <= 200)
    {
      led=4;  
    }
    else
    {
      led=0;  
    }
    Serial.print(led);
    Serial.println(F(" led \t"));
      
    delay(100);
    
    switch (step)
    {
    case 1: //Etat initial, le moteur est fermé
      if((state==1)&&(pirValue==1 || pirValue2==1))
       {if (level > 35)    //astucieux!!
        state=0;
        delay(2000);
        }
      
      if((state==0)&&(pirValue==1 || pirValue2==1)) // si la poubelle est vide et que le PIR détecte quelquechose, on passe à la step d'après.
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
      if (pirValue==0 && pirValue2==0)
       {delay(2000);
      step=4;}
      break;
    case 4:
      Serial.println(F("Closing"));
      servoMain.write(82);
      delay(2200);
      servoMain.write(92);
      delay(3000);
      if (level < 35)
        state=1;
      step=1;
      break;
    }  
  
   switch (led) //mettre les changements de led selon l'état
   {
    int i;
    int j;
   case 0:
      matrix.fillScreen(0);
      matrix.show();
      break;
   case 1:
      matrix.fillScreen(0);
      for (i=0;i<8;i++)
      {
        for (j=0;j<8;j++)
        {
          if (eye_1[i][j]==1)
          {
            matrix.drawPixel(i,j,color);
            matrix.drawPixel(i,j+8,color);
          }
         }
        }
        matrix.show();
      break;
    case 2:
      matrix.fillScreen(0);
      for (i=0;i<8;i++)
      {
        for (j=0;j<8;j++)
        {
          if (eye_2[i][j]==1)
          {
            matrix.drawPixel(i,j,color);
             matrix.drawPixel(i,j+8,color);
          }
        }
       }
      matrix.show();
      break; 
    case 3:
      matrix.fillScreen(0);
      for (i=0;i<8;i++)
      {
        for (j=0;j<8;j++)
        {
          if (eye_3[i][j]==1)
          {
            matrix.drawPixel(i,j,color);
            matrix.drawPixel(i,j+8,color);
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
            matrix.drawPixel(i,j,color);
            matrix.drawPixel(i,j+8,color);
          }
        }
       }
      matrix.show();
      break;
   }
  }

  void process(WifiData client) {
  // read the command
  String command = client.readStringUntil('/');

  // is "digital" command?
  if (command == "webserver") {
    WebServer(client);
  }

  if (command == "digital") {
    digitalCommand(client);
  }
}

void WebServer(WifiData client) {
  
            client.println(signMessage1);
            client.println(signMessage2);
            client.println(signMessage3);
            
            client.print(signMessage4);
            client.print(signMessage5);
            client.print(signMessage6);

            client.print(signMessage7);
          
            client.print(DELIMITER); // very important to end the communication !!!
         
}

void digitalCommand(WifiData client) {
  int command, value = 0;

  command = client.parseInt();  
  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/0/1"
  if (client.read() == '/') {
      value = client.parseInt();
  }
}

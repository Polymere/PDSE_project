//Henry's Bench
// HC-SR501 Motion Detector
// Sample Sketch


int pirPin = 7; // Input for HC-S501

int pirValue; // Place to store read PIR Value


void setup() {
  

    pinMode(pirPin, INPUT);
   Serial.begin(9600);

  
  
  
}

void loop() {
  pirValue = digitalRead(pirPin);
  Serial.println(pirValue);
  delay(100);

}


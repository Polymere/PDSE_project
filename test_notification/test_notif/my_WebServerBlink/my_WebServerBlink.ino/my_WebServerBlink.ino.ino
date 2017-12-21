/*
File: WebServerBlink.ino
This example creates a simple web server on your Arduino Uno WiFi. It serves a
simple web page with 2 buttons that can be used to switch on and off on-board led 13.
Please type on your browser http://<IP>/arduino/webserver/ or http://<hostname>.local/arduino/webserver/

Note: works only with Arduino Uno WiFi Developer Edition.

http://www.arduino.org/learning/tutorials/boards-tutorials/webserverblink
*/

#include <Wire.h>
#include <UnoWiFiDevEd.h>
#include <avr/pgmspace.h>

const char signMessage1[] PROGMEM  = {"HTTP/1.1 200 OK"};
const char signMessage2[] PROGMEM  = {"Content-Type: text/html"};
const char signMessage3[] PROGMEM  = {"<html><head></head><body>"};
const char signMessage4[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/1/0','_parent');w.close();\"value='PET'><br>"};
const char signMessage5[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/1/1','_parent');w.close();\"value='ALU'><br>"};
const char signMessage6[] PROGMEM  = {"<input type=button onClick=\"var w=window.open('/arduino/digital/2/0','_parent');w.close();\"value='Reactivate'><br>"};
const char signMessage7[] PROGMEM  = {"</body></html>"};

void setup() {
    Wifi.begin();
    Wifi.println(F("Web Server is up"));
    Serial.begin(9600);
}

void loop() {

    while(Wifi.available()){
      process(Wifi);
    }
    delay(50);
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

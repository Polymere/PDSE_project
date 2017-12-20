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

void setup() {
    pinMode(13,OUTPUT);
    Wifi.begin();
    Wifi.println("Web Server is up");
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
  
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("<html><head></head><body>");
            client.println();
            
            client.print("<input type=button onClick=\"var w=window.open('/arduino/digital/0/0','_parent');w.close();\"value='PET'><br>");
            client.print("<input type=button onClick=\"var w=window.open('/arduino/digital/0/1','_parent');w.close();\"value='ALU'><br>");
            client.print("<input type=button onClick=\"var w=window.open('/arduino/digital/1/0','_parent');w.close();\"value='Reactivate'><br>");

            client.print("</body>");
            client.println("</html>");
          
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
  // Send feedback to client

  if(command == '0'){
    client.println("Status: 200 OK\n");
    client.print(F("Type of bin set to "));
    client.print(value);
    client.print(EOL);    //char terminator
  }else{
    client.println("Status: 200 OK\n");
    client.print(F("ROBIN was succesfully reactivated!"));
    client.print(EOL);    //char terminator
  }

}

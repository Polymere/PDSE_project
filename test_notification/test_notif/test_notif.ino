#include <WiFi.h>

#include <StandardCplusplus.h>
#include <UniversalTelegramBot.h>

#include <String>
#define BOTtoken "385318893:AAFsNOf8_UX5hQkMdo4Vcu2DI1SFTVp_UvI"
WiFiClient client; //For ESP8266 boards
UniversalTelegramBot bot(BOTtoken, client);

char ssid[] = "AndroidAPjon";            // your network SSID (name)
char pass[] = "aota8028";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {
  Serial.begin(9600);

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
    Serial.println(status);
    Serial.println(WL_CONNECTED);

  }
  
  WiFiServer server(23);
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
  senderTelegram("1","96689970");
}

void loop() {
}

void senderTelegram(String idRobin, String idUser){
  bool isSent = false;
  Serial.println("isSent declared");
  String text = "Test: Bot in action";
  Serial.println("Text");
  isSent = bot.sendMessage(idUser, text);
  Serial.println("Should be sent");
  
  if(isSent)
    Serial.println("Success!");
  else 
    Serial.println("Fail :( ");
    
}

void printWifiStatus() {
  WiFiClass wifi;
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(wifi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = wifi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = wifi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

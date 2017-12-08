#include <WiFiClient.h>

#include <StandardCplusplus.h>
#include <UniversalTelegramBot.h>

#include <String>
#define BOTtoken "385318893:AAFsNOf8_UX5hQkMdo4Vcu2DI1SFTVp_UvI"
WiFiClient client; //For ESP8266 boards
UniversalTelegramBot bot(BOTtoken, client);


void setup() {
  Serial.begin(9600);
  Serial.println("Before");
  senderTelegram("1","96689970");
  Serial.println("After");
}

void loop() {
}

void senderTelegram(String idRobin, String idUser){
  bool isSent = false;
  Serial.println("isSent");
  String text = "Test: Bot in action";
  Serial.println("Text");
  //    bool sendMessage(String chat_id, String text, String parse_mode = "");
  isSent = bot.sendMessage(idUser, text);
  Serial.println("Should be sent");
  
  if(isSent)
    Serial.println("Success!");
  else 
    Serial.println("Fail :( ");
    
}


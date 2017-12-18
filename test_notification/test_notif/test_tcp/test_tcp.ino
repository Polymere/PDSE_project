#include <WiFi.h>
#include <utility/wifi_spi.h>
#include <WiFiClient.h>

char SSID[] = "Camilla's Huawei";
char PSK[] = "HuaweiRulez";

void setup() {

Serial.begin(9600);
Serial << "Setup...\r\n";

uint8_t numNets = WiFi.scanNetworks();
for (uint8_t i=0; i < numNets; i++) {
Serial << WiFi.SSID(i) << '\t' << WiFi.RSSI(i) << "\r\n";
}

do {
Serial << "Try connect to " << SSID << "...";
WiFi.begin(SSID, PSK);
if (WiFi.status() == WL_CONNECTED) {
Serial << " Connected\r\n";
} 
else {
Serial <<  "Failed to connect to " << SSID << "\r\n";
delay(5000);
}
} while (WiFi.status() != WL_CONNECTED);
 
Serial << "End setup\r\n"; 
}

char targetHost[] = "bigmac.mssystems.home";
const uint16_t port = 32123;
WiFiClient client;

void loop()
{
Serial << "\nEnter loop\r\n";

while ( WiFi.status() != WL_CONNECTED ) {
Serial << "Try reconnect to " << SSID << "\r\n";
WiFi.begin(SSID, PSK);
if (WiFi.status() == WL_CONNECTED) {
Serial << "Reconnected to " << SSID << "\r\n";
}
delay(5000);
}
Serial << "client.connected = " << client.connected() << "\r\n";
Serial << "wifi.getSocket = " << WiFi.getSocket() << "\r\n";

IPAddress ip;
WiFi.hostByName(targetHost, ip);

Serial <<"Try connect to " << targetHost << ' ' << ip << "...";
if (! client.connect(ip, port)) {
Serial << "Failed\r\n";
} else Serial << "Connected\r\n";

Serial << "client.connected = " << client.connected() << "\r\n";
Serial << "WiFi.getSocket = " << WiFi.getSocket() << "\r\n";

Serial << "Wait for client.stop...";
delay(3000);

if (client.connected()) {
Serial << "Stop client\r\n";
client.stop();
}
else {
Serial << "Client not connected!\r\nApplication stop\r\n";
while(true);
}

Serial<< "Wait for loop exit...\r\n";
delay(5000);
}

#include <M5Atom.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

const char *ssid     = "WSPT Cam-5bd913";
const char *password = "12345678";

WiFiServer server(5007);

void setup() {
  M5.begin();
  Serial.println("\nWIFI ACCESS POINT");
  Serial.printf("Please connect:%s \nThen access to:", ssid);
  IPAddress local_ip(192, 168, 1, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAP(ssid, password);
  delay(100);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  IPAddress myIP = WiFi.softAPIP();  
  Serial.println(myIP);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.print("New Client:");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (isprint(c)) {
          Serial.printf("%c(%02x)", c, c);
        } else {
          Serial.printf("(%02x)", c);
        }
      }
    }
    client.stop();
    Serial.print("Stop Client:");
  }
}

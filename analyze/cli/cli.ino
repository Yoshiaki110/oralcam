#include <M5Atom.h>
#include <WiFi.h>
#include <WiFiMulti.h>

const char *ssid     = "WSPT Cam-5bd913";
const char *password = "12345678";
WiFiMulti WiFiMulti;

void setup() {
  M5.begin(true, false, true);
  WiFiMulti.addAP(ssid, password);
  Serial.print("\nWaiting connect to WiFi...");
  M5.dis.fillpix(0xff0000);
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  M5.dis.fillpix(0x00ff00);
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
}

void loop() {
  const char *host = "192.168.1.1";
  const uint16_t port = 5007;
  Serial.print("Connecting to: ");
  Serial.println(host);
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("Connection failed.");
    Serial.println("Waiting 5 seconds before retrying...");
    delay(5000);
    return;
  }
  //client.print("GET /index.html HTTP/1.1\n\n");
  int maxloops = 0;
  while (!client.available() && maxloops < 500) {
    maxloops++;
    delay(10);
  }
  if (client.available() > 0) {
    while (client.available()) {
      char c = client.read();
      if (isprint(c)) {
        Serial.printf("%c(%02x)", c, c);
      } else {
        Serial.printf("(%02x)", c);
      }
    }
  } else {
    Serial.println("client.available() timed out ");
  }
  Serial.println("Closing connection.");
  client.stop();
  Serial.println("Waiting 5 seconds before restarting...");
  delay(5000);
}

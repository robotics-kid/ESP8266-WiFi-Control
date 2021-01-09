#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#define APSSID "ESPap"
#define APPSK  "123456789"
int port = 80;  //Port number

IPAddress local_IP(192, 168, 4, 2);
IPAddress subnet(255, 255, 255, 0);

const char *ssid = APSSID;
const char *password = APPSK;

WiFiServer server(port);
WiFiClient serverClients[4];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP_STA);

  Serial.println();
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, local_IP, subnet) ? "Ready" : "Error");

  WiFi.softAP(ssid, password);

  server.begin();
  server.setNoDelay(true);

  Serial.println(); Serial.println();
  Serial.println("ESP ready");
  Serial.print("IP is : "); Serial.println(WiFi.softAPIP());
  Serial.print("IP is : "); Serial.println(WiFi.localIP());
  Serial.println("Port is : 80");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    if (client.connected())
    {
      Serial.println("Client Connected");
    }

    while (client.connected()) {



      while (client.available() > 0) {
        // read data from the connected client
        Serial.write(client.read());
      }
      //Send Data to connected client
      while (Serial.available() > 0)
      {
        char snd[100] = "";
        String tmp = Serial.readStringUntil('\n');
        tmp.toCharArray(snd, 100);
        client.write(snd, 100);
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}

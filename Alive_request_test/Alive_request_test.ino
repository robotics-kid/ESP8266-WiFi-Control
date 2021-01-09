#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <FastLED.h>

#define APSSID                "ESPap"           // SSID of local WiFi Network
#define APPSK                 "1234567890"       // Password of local WiFi Netdwork

#define MAX_CLIENTS           4                 // Maximum clients connection
int port =                    80;               // Port number


IPAddress local_IP = IPAddress(192, 168, 4, 1);
IPAddress subnet = IPAddress(255, 255, 255, 0);

const char *ssid = APSSID;
const char *password = APPSK;

WiFiServer server(port); // Setting up server
WiFiClient serverClients[MAX_CLIENTS]; // Limit num of conected clients

void setup() {
  Serial.begin(115200);
  delay(1000); // Slow power up delay.

  // Seting up network
  //====================
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP);

  // Set up of WiFi configuration like local ip and subnet mask
  Serial.println();
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, local_IP, subnet) ? "Ready" : "Error");

  WiFi.softAP(ssid, password); // Starting Soft AP

  // Starting TCP/IP Server on initialized WiFi Network
  server.begin();
  server.setNoDelay(true);

  Serial.println(); Serial.println();
  Serial.println("ESP ready");
  Serial.print("IP is : "); Serial.println(WiFi.softAPIP());
  Serial.print("IP is : "); Serial.println(WiFi.localIP());
  Serial.print("Port is : "); Serial.println(port);
  //====================

}
bool sendOk(WiFiClient client) {
  Serial.println("SEND OK");
  client.println("ok");

  // Read the first line of the request
  String ok = client.readStringUntil('\r');
  Serial.println(ok);
  client.flush();
  if (ok != "ok") {
    client.stop();
    Serial.println("True");
    return true;
  }
  Serial.println("False");
  return false;
}

void loop() {
  WiFiClient client = server.available();
  if (client) {

    Serial.println("new client");
    while (client.connected()) {
      Serial.print("CONNECTED: ");
      Serial.println(client.connected());

      // Wait until the client sends some data

      while (client.connected() && !client.available() ) {
        delay(1);
      }

      Serial.println();
      // Read the first line of the request
      String req = client.readStringUntil('\r');
      Serial.println(req);
      client.flush();
      
      EVERY_N_MILLISECONDS( 5000 ) {
        if (sendOk(client)) {
          return;
        }
      }


    }
  }
  client.stop();
}

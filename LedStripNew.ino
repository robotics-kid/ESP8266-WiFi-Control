
/* ESP8266 WiFi control

    By: Nikita Klepikov

    Date: 8 December, 2020
*/

//#include <RGBConverter.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <LittleFS.h>

#include <Adafruit_NeoPixel.h>
#include "Settings.h"

// Serial
void setup() {

  strcat(mSend, root_previx);
  strcat(mSend, ";STA:1");

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
  Serial.print("Port is : "); Serial.println(PORT);
  //====================

  // Initializing leds. Based on LEDS TYPE
  strip.begin();
  strip.clear();
  strip.setBrightness(MAX_BRIGHTNESS); // Setting maximum alowed brightness

  //Mounting SPIFFS on ESP
  //====================
  if (!LittleFS.begin()) // Starting SPIFFS
  {
    Serial.println("Error mounting the file system");
    return;
  }
  //====================

  //Checking for saved effect is SPIFFS
  //====================
  ReadSPIFFS(); // Reads from SPIFFS
  if (strcmp(recv_str, "-1"))
  {
    strcpy(preRecv, recv_str);
    strcpy(toSPIFFS, recv_str);
    Serial.println(recv_str);
    Tokenizer(recv_str); // Tokenzie read string and starts effect
  }
  //====================
  Serial.println("Setup ready");
}

void loop() {

  client = server.available(); // Starting WiFi Server

  if (client) // If client is available
  {
    // Printing message of sucefull connection
    if (client.connected())
      Serial.println("Client Connected");

    // Starting client handle(while client is connected)
    while (client.connected())
    {
      memset(recv_str, '\0', sizeof(char)*argsLen);

      /*Serial.println();
      Serial.print("mSend: ");
      Serial.println(mSend);*/

      sendRecieve(); //Function sendRecieve - takes date to send and - return recieved date {String sendRecieve(String, *WiFIClient)}
      /*Serial.print("recv: ");
      Serial.println(recv_str);*/
      //recv_str.toCharArray(recv, argsLen); // Converting tmp string to char array recv

      if (!strcmp(preRecv, recv_str)) {
        Serial.println("Spam");
        continue;
      }
      char recv_tmp[argsLen];
      strncpy(recv_tmp, recv_str, argsLen);
      
      Tokenizer(recv_tmp); // Tokenzie recieved from WiFi string and starts effect*/

      if (!strcmp(mSend, "FoViBalTLight;STA:0"))
      {
        break;
      }
      strcpy(preRecv, toSPIFFS);

    }
    Serial.println("Client disconnected");
    memset(mSend, '\0', sizeof(char)*argsLen);
    strcat(mSend, root_previx);
    strcat(mSend, ";STA:1");
    client.stop();
  }


}

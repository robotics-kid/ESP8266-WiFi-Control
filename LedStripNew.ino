
/* ESP8266 WiFi control

    By: Nikita Klepikov

    Date: 8 December, 2020
*/

#include <RGBConverter.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FS.h>

#include "FastLED.h"
#include "Settings.h"

// Serial
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

  // Initializing leds. Based on LEDS TYPE
#if LEDS_TYPE == 1
  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(ledsRGB, getRGBWsize(NUM_LEDS)); // Set up for SK6812
#else
  FastLED.addLeds<STRIP_NAME, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS); // Set up for all non white leds
#endif

  switch (LEDS_TYPE) {
    case 1:
      FastLED.setCorrection(UncorrectedColor); // SK6812
      FastLED.setCorrection(Typical8mmPixel); // SK6812
    case 2:
      FastLED.setCorrection(TypicalPixelString); //FOR WS2812B
      FastLED.setTemperature(CoolWhiteFluorescent); //FOR WS2812B
    case 3:
    case 4:
      FastLED.setCorrection(UncorrectedColor); // WS2811
      FastLED.setTemperature(CarbonArc); //WS2811
  }

  FastLED.setBrightness(MAX_BRIGHTNESS); // Setting maximum alowed brightness

  //Mounting SPIFFS on ESP
  //====================
  if (!SPIFFS.begin()) // Starting SPIFFS
  {
    Serial.println("Error mounting the file system");
    return;
  }
  //====================

  //Checking for saved effect is SPIFFS
  //====================
  ReadSPIFFS(); // Reads from SPIFFS
  if (recv_str != "-1")
  {
    preRecv = recv_str;
    char effect[argsLen];
    recv_str.toCharArray(effect, argsLen);
    Serial.println(recv_str);
    Tokenizer(); // Tokenzie read string and starts effect
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
      memset(recv, '\0', sizeof(recv));

      Serial.println();
      Serial.print("mSend: ");
      Serial.println(mSend);
      sendRecieve(); //Function sendRecieve - takes date to send and - return recieved date {String sendRecieve(String, *WiFIClient)}
      recv_str.toCharArray(recv, argsLen); // Converting tmp string to char array recv
      if (preRecv == recv_str) {
        //Serial.println("Spam");
        continue;
      }
      Serial.print("recv: ");
      Serial.write(recv);
      Serial.println();

      Tokenizer(); // Tokenzie recieved from WiFi string and starts effect*/
      if (mSend == "FoViBalTLight;STA:0!")
      {
        break;
      }
      preRecv = recv_str;
    }
    Serial.println("Client disconnected");
    mSend = String(root_previx) + ";STA:1!"; // Creating first mSend witch contain handshake: FoViBalTLight;STA:1x
    client.stop();
  }


}

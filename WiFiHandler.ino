#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "Settings.h"
unsigned long starttime = 0;

//Function sendRecieve - takes date to send and - return recieved date
void sendRecieve()
{
  //Serial.println("send recieve enter");
  

  //Send Data to connected client
  char SendBuffer[argsLen];
  memset(SendBuffer, '\0', sizeof(SendBuffer));
  mSend.toCharArray(SendBuffer, argsLen);
  
  client.write(SendBuffer);

  starttime = millis();
  bool recv_flag = false;
  recv_str = "";
  while (true) {
    while (client.available()) {
      recv_str += (char)client.read();

      recv_flag = true;
    }
    if (recv_flag) {
      break;
    }
    if ( millis() - starttime > 5000) {
      client.stop();
      break;
    }
  }
}

//Function turn on special effect proceeding from WiFiHandler array and it's arguments
void effectHandler()
{

  if (!strcmp(WiFiHandler[0].handlerChar, "EFF"))
  {
;
    WriteSPIFFS(&recv_str);
    //Serial.print(millis());

    switch (WiFiHandler[0].handlerVal) // Tutn on effect prepare functions proceeding from WiFiHandler array value
    {
      case 1:
        // Extract from WiFiHandler arguments for SPECIAL EFFECT
        colorEffect(); // Color solid effect
        break;
      case 2:
        //Extract from WiFiHandler arguments for SPECIAL EFFECT
        whiteEffect(); // White solid effect
        break;
      case 3:
        gradientEffect_2Val();
        break;
    }
    mSend = String(root_previx) + ";STA:1!";

  }
  else if (!strcmp(WiFiHandler[0].handlerChar, "STA") and WiFiHandler[0].handlerVal == 1)
  {
    mSend = String(root_previx) + ";LDT:" + String(LEDS_TYPE) + ";STT:" + String(STRIP_TYPE) + '!';
  }
  else
  {
    mSend = String(root_previx) + ";STA:1!";
  }


}

void Tokenizer(char recv[])
{
  if (!strcmp(recv, "")) {
    mSend = "FoViBalTLight;STA:0!";
    return;
  }
  
  memset(WiFiHandler, '\0', sizeof(handler)*argsLen); // Filling WiFiHandler with NULL values

  char* token = strtok(recv, del); // Initialize token to split recv by delimiter
  
  uint16_t i = 0;
  bool flag = false;
  while (token != NULL)
  {
    //Serial.println(token);
    // Checks if token[0] is equal to root_previx
    
    if (i == 0 and strcmp(token, root_previx))
    {
      Serial.println("is NULL");
      mSend = "FoViBalTLight;STA:0!";
      return;
    }
    
    // If it is not first root_previx
    if (flag)
    {
      if ((i % 2) == 0)
      {
        WiFiHandler[i / 2 - 1].handlerVal = atoi(token);
      }
      else if ((i % 2) == 1)
      {
        strcpy(WiFiHandler[(i + 1) / 2 - 1].handlerChar, token);
      }
    }
    
    token = strtok(NULL, del); // Incrementing token
    flag = true;
    i++;
  }

  //Function turn on special effect proceeding from WiFiHandler array and it's arguments {String effectHandler(handler[], String)}
  effectHandler();

}

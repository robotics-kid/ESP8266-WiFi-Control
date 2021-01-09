#pragma once
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "Settings.h"

//Function sendRecieve - takes date to send and - return recieved date
void sendRecieve()
{

  client.setTimeout(5000);
  /*Serial.print("Client available: ");
    Serial.println(client.available());*/

  //Send Data to connected client
  memset(recv, '\0', sizeof(recv));
  mSend += '\n';
  mSend.toCharArray(recv, argsLen);
  client.write(recv);

  /*Serial.print("Sended: ");
    Serial.println(buf);*/

  // read data from the connected client
  //while (true)
  //{
  // if (client.available() > 0)
  //   {
  recv_str = client.readStringUntil('\n');
  //  break;
  //}
  //delay(20);
  //}

}

//Function turn on special effect proceeding from WiFiHandler array and it's arguments
void effectHandler()
{

  if (!strcmp(WiFiHandler[0].handlerChar, "EFF"))
  {
    WriteSPIFFS();

    switch (WiFiHandler[0].handlerVal) // Tutn on effect prepare functions proceeding from WiFiHandler array value
    {
      case 1:
        // Extract from WiFiHandler arguments for SPECIAL EFFECT
        colorEffect(WiFiHandler); // Color solid effect
        break;
      case 2:
        //Extract from WiFiHandler arguments for SPECIAL EFFECT
        whiteEffect(WiFiHandler); // White solid effect
        break;
      case 3:
        gradientEffect_2Val(WiFiHandler);
        break;
    }
    mSend = String(root_previx) + ";STA:1";

  }
  else if (!strcmp(WiFiHandler[0].handlerChar, "STA") and WiFiHandler[0].handlerVal == 1)
  {
    mSend = String(root_previx) + ";LDT:" + String(LEDS_TYPE) + ";STT:" + String(STRIP_TYPE);
  }
  else
  {
    mSend = String(root_previx) + ";STA:1";
  }


}

void Tokenizer()
{

  if (!strcmp(recv, "")) {
    mSend = "FoViBalTLight;STA:0";
    return;
  }

  memset(WiFiHandler, '\0', sizeof(handler)*argsLen); // Filling WiFiHandler with NULL values
  token = "";

  token = strtok(recv, del); // Initialize token to split recv by delimiter

  i = 0;
  flag = false;
  while (token != NULL)
  {
    // Checks if token[0] is equal to root_previx
    if (i == 0 and strcmp(token, root_previx))
    {
      Serial.println("is NULL");
      mSend = "FoViBalTLight;STA:0";
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

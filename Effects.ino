#pragma once
#include "Settings.h"

// Fills led strip with solid color from recieved data
void colorEffect()
{
  /*Serial.print("r: ");
  Serial.println(Wargs[1].handlerVal);
  
  Serial.print("g: ");
  Serial.println(Wargs[2].handlerVal);
  
  Serial.print("b: ");
  Serial.println(Wargs[3].handlerVal);
  
  Serial.print("w: ");
  Serial.println(Wargs[4].handlerVal);*/
  //-1 goes if led strip does not have white leds or if led strip is SK6812
  if (LEDS_TYPE == NEO_RGBW)
  {
    strip.fill(strip.Color(WiFiHandler[1].handlerVal, WiFiHandler[2].handlerVal, WiFiHandler[3].handlerVal, WiFiHandler[4].handlerVal), 0, NUM_LEDS);
  }
  else
  {
    strip.fill(strip.Color(WiFiHandler[1].handlerVal, WiFiHandler[2].handlerVal, WiFiHandler[3].handlerVal), 0, NUM_LEDS);
  }
  
  strip.show();
}

// Fills led strip with white color with adjustable color temperature(SK6812 only)
void whiteEffect()
{

  
}

// Fills led strip with static gradient with recieved colors
void gradientEffect_2Val()
{

  

  //-1 goes if led strip does not have white leds or if led strip is SK6812
  
}

//RGB to HSv conversion using (360*, 100%, 100%) standart

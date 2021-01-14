#pragma once
#include "Settings.h"

// Fills led strip with solid color from recieved data
void colorEffect()
{
  //Serial.print("BEFORE solid: ");       
  //Serial.println(millis()); 
  strip.fill(strip.Color(WiFiHandler[1].handlerVal, WiFiHandler[2].handlerVal, WiFiHandler[3].handlerVal, WiFiHandler[4].handlerVal), 0, NUM_LEDS);
  strip.show();
  //Serial.print("AFTER solid: ");       
  //Serial.println(millis());       
}

// Fills led strip with white color with adjustable color temperature(SK6812 only)
void whiteEffect()
{
  //if (COLOR_ORDER == NEO_RGBW or COLOR_ORDER == NEO_GRBW)
  //{
  
    WiFiHandler[1].handlerVal = map(WiFiHandler[1].handlerVal, 1800, 6500, -255, 765); // Map recieved kelvin values into my pseudo range from 0 - 510
    WiFiHandler[2].handlerVal = map(WiFiHandler[2].handlerVal, 0, 255, 0, MAX_BRIGHTNESS); // Map recieved brightnes value into brightness towards MAX_BRIGHTNES

    strip.setBrightness(WiFiHandler[2].handlerVal);

    if(WiFiHandler[1].handlerVal < 0 && WiFiHandler[1].handlerVal >= -255)
    {
      strip.fill(strip.Color(WiFiHandler[1].handlerVal * -1, 0, 0, 255), 0, NUM_LEDS);
    }
    else if (WiFiHandler[1].handlerVal >= 0 && WiFiHandler[1].handlerVal <= 255)
    {
      strip.fill(strip.Color(WiFiHandler[1].handlerVal, WiFiHandler[1].handlerVal, WiFiHandler[1].handlerVal, 255), 0, NUM_LEDS);
    }
    else if (WiFiHandler[1].handlerVal > 255 && WiFiHandler[1].handlerVal <= 510)
    {
      strip.fill(strip.Color(255, 255, 255, 255 - (WiFiHandler[1].handlerVal - 255)), 0, NUM_LEDS);
    }
    else if(WiFiHandler[1].handlerVal > 510 && WiFiHandler[1].handlerVal <= 765)
    {
      strip.fill(strip.Color(510 - (WiFiHandler[1].handlerVal - 255), 510 - (WiFiHandler[1].handlerVal - 255), 255, 0), 0, NUM_LEDS);  
    }
    strip.show();
  //}
}

// Fills led strip with static gradient with recieved colors
void gradientEffect_2Val()
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    strip.setPixelColor(i,  mix( WiFiHandler[1].handlerVal, WiFiHandler[5].handlerVal, i, NUM_LEDS ),
                            mix( WiFiHandler[2].handlerVal, WiFiHandler[6].handlerVal, i, NUM_LEDS ),
                            mix( WiFiHandler[3].handlerVal, WiFiHandler[7].handlerVal, i, NUM_LEDS ),
                            mix( WiFiHandler[4].handlerVal, WiFiHandler[8].handlerVal, i, NUM_LEDS ));
  }
  strip.show();
}

uint8_t mix(uint8_t a, uint8_t b, uint16_t pct, uint16_t range) {
  if (pct <= 0) return a;
  if (pct >= range) return b;
  return (((uint32_t)a * (range - pct)) / range) + (((uint32_t)b * pct) / range);
}

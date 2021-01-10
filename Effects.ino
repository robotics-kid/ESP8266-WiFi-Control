#pragma once
#include "Settings.h"
RGB_t rgb_2;
int white;
int white_2;
int isWhite;

// Fills led strip with solid color from recieved data
void colorEffect(handler Wargs[])
{
  memset(&rgb, '\0', sizeof rgb);  // OK as well
  rgb.r = Wargs[1].handlerVal;
  rgb.g = Wargs[2].handlerVal;
  rgb.b = Wargs[3].handlerVal;
  white = Wargs[4].handlerVal;
  isWhite = LEDS_TYPE;

  /*
    HSV_t hsv;
    hsv.h = Wargs[1].handlerVal;
    hsv.s = Wargs[2].handlerVal;
    hsv.v = Wargs[3].handlerVal;
    int white = Wargs[4].handlerVal;
    int isWhite = LEDS_TYPE;


    RGB_t rgb = HSV_to_RGB(hsv);
  */
  /*Serial.print("Hue: ");
    Serial.print(hsv.h);
    Serial.print("Sat: ");
    Serial.print(hsv.s);
    Serial.print("Val: ");
    Serial.print(hsv.v);
    Serial.print("White: ");
    Serial.print(white);*/

  //-1 goes if led strip does not have white leds or if led strip is SK6812
  if (isWhite != 1)
  {
    fill_solid(leds, NUM_LEDS, CRGB(rgb.r, rgb.g, rgb.b));
  }
  else
  {
    fill_solid(ledsW, NUM_LEDS, CRGBW(rgb.r, rgb.g, rgb.b, white));
  }
  FastLED.show();
}

// Fills led strip with white color with adjustable color temperature(SK6812 only)
void whiteEffect(handler Wargs[])
{

  /*Serial.print("White Kelvin: ");
    Serial.println(Wargs[1].handlerVal);
    Serial.print("White BRI recieved: ");
    Serial.println(Wargs[2].handlerVal);*/

  Wargs[1].handlerVal = map(Wargs[1].handlerVal, 1800, 6500, 0, 510); // Map recieved kelvin values into my pseudo range from 0 - 510
  Wargs[2].handlerVal = map(Wargs[2].handlerVal, 0, 255, 0, MAX_BRIGHTNESS); // Map recieved brightnes value into brightness towards MAX_BRIGHTNESS

  /*Serial.print("White My pseudo range: ");
    Serial.println(Wargs[1].handlerVal);
    Serial.print("White BRI converted towards MAX_BRI: ");
    Serial.println(Wargs[2].handlerVal);*/

  FastLED.setBrightness(Wargs[2].handlerVal);
  if (Wargs[1].handlerVal >= 0 && Wargs[1].handlerVal <= 255)
  {
    fill_solid(ledsW, NUM_LEDS, CRGBW(Wargs[1].handlerVal, Wargs[1].handlerVal, Wargs[1].handlerVal, 255));
  }
  else if (Wargs[1].handlerVal > 255 && Wargs[1].handlerVal <= 510)
  {
    fill_solid(ledsW, NUM_LEDS, CRGBW(255, 255, 255, 255 - (Wargs[1].handlerVal - 255)));
    // CRGBW(0, 0, 0, 255);        Wram white
    // CRGBW(255, 255, 255, 255);  Neitral white
    // CRGBW(255, 255, 255, 0);    Cold white
  }
  FastLED.show();
}

// Fills led strip with static gradient with recieved colors
void gradientEffect_2Val(handler Wargs[])
{

  memset(&rgb, '\0', sizeof rgb);
  memset(&rgb_2, '\0', sizeof rgb_2);
  rgb.r = Wargs[1].handlerVal;
  rgb.g = Wargs[2].handlerVal;
  rgb.b = Wargs[3].handlerVal;
  white = Wargs[4].handlerVal;

  rgb_2.r = Wargs[5].handlerVal;
  rgb_2.g = Wargs[6].handlerVal;
  rgb_2.b = Wargs[7].handlerVal;
  white_2 = Wargs[8].handlerVal;
  isWhite = LEDS_TYPE;

  //-1 goes if led strip does not have white leds or if led strip is SK6812
  if (isWhite != 1)
  {
    fill_gradient_RGB(leds, NUM_LEDS, CRGB(rgb.r, rgb.g, rgb.b), CRGB(rgb_2.r, rgb_2.g, rgb_2.b));
  }
  else
  {
    fill_gradient_RGBW(ledsW, NUM_LEDS, CRGBW(rgb.r, rgb.g, rgb.b, white_2), CRGBW(rgb_2.r, rgb_2.g, rgb_2.b, white));
  }
  FastLED.show();
}

//RGB to HSv conversion using (360*, 100%, 100%) standart
RGB_t HSV_to_RGB(HSV_t hsv)
{
  float s = hsv.s / 100; //1
  float v = hsv.v / 100; //0.5
  RGB_t rgb;
  float c = v * s; //0.5
  float x = c * (1 - abs(fmod((hsv.h / 60), 2) - 1)); //0.5
  float m = v - c; //0
  if (0 <= hsv.h && hsv.h < 60) {
    rgb = {c, x, 0};
  } else if (60 <= hsv.h && hsv.h < 120) {
    rgb = {x, c, 0};
  } else if (120 <= hsv.h && hsv.h < 180) {
    rgb = {0, c, x};
  } else if (180 <= hsv.h && hsv.h < 240) {
    rgb = {0, x, c};
  } else if (240 <= hsv.h && hsv.h < 300) {
    rgb = {x, 0, c};
  } else if (300 <= hsv.h && hsv.h < 360) {
    rgb = {c, 0, x}; //0.5, 0, 0,5

  }
  rgb = {(rgb.r + m) * 255, (rgb.g + m) * 255, (rgb.b + m) * 255};
  return rgb;
}

#pragma once
#include "Settings.h"
RGB_t rgb_2;
uint16_t white;
uint16_t white_2;
uint8_t isWhite;

uint16_t endpos = NUM_LEDS - 1;
uint16_t startpos = 0;
CRGB startcolor, endcolor, tc;
CRGBW startcolor_W, endcolor_W, tc_W;

uint16_t t, pixeldistance;
saccum87 rdistance87, gdistance87, bdistance87, rdelta87, gdelta87, bdelta87, wdistance87, wdelta87;
accum88 r88, g88, b88, w88;
int16_t divisor;

// Fills led strip with solid color from recieved data
void colorEffect()
{
  memset(&rgb, '\0', sizeof rgb);  // OK as well
  rgb.r = WiFiHandler[1].handlerVal;
  rgb.g = WiFiHandler[2].handlerVal;
  rgb.b = WiFiHandler[3].handlerVal;
  white = WiFiHandler[4].handlerVal;
  isWhite = LEDS_TYPE;

  //-1 goes if led strip does not have white leds or if led strip is SK6812
  if (isWhite != 1)
  { 
    for (i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(rgb.r, rgb.g, rgb.b);
    }
  }
  else
  {
    for (i = 0; i < NUM_LEDS; i++) {
      ledsW[i] = CRGBW(rgb.r, rgb.g, rgb.b, white);
    }
  }
  FastLED.show();
}

// Fills led strip with white color with adjustable color temperature(SK6812 only)
void whiteEffect()
{

  WiFiHandler[1].handlerVal = map(WiFiHandler[1].handlerVal, 1800, 6500, -255, 765); // Map recieved kelvin values into my pseudo range from 0 - 510
  WiFiHandler[2].handlerVal = map(WiFiHandler[2].handlerVal, 0, 255, 0, MAX_BRIGHTNESS); // Map recieved brightnes value into brightness towards MAX_BRIGHTNESS

  FastLED.setBrightness(WiFiHandler[2].handlerVal);

  if (WiFiHandler[1].handlerVal < 0 && WiFiHandler[1].handlerVal >= -255)
  {
    fill_solid(ledsW, NUM_LEDS, CRGBW(WiFiHandler[1].handlerVal * -1, 0, 0, 255));
  }
  else if (WiFiHandler[1].handlerVal >= 0 && WiFiHandler[1].handlerVal <= 255)
  {
    fill_solid(ledsW, NUM_LEDS, CRGBW(WiFiHandler[1].handlerVal, WiFiHandler[1].handlerVal, WiFiHandler[1].handlerVal, 255));
  }
  else if (WiFiHandler[1].handlerVal > 255 && WiFiHandler[1].handlerVal <= 510)
  {
    fill_solid(ledsW, NUM_LEDS, CRGBW(255, 255, 255, 255 - (WiFiHandler[1].handlerVal - 255)));
  }
  else if (WiFiHandler[1].handlerVal > 510 && WiFiHandler[1].handlerVal <= 765)
  {
    fill_solid(ledsW, NUM_LEDS, CRGBW(510 - (WiFiHandler[1].handlerVal - 255), 510 - (WiFiHandler[1].handlerVal - 255), 255, 0));
  }
  FastLED.show();
}

// Fills led strip with static gradient with recieved colors
void gradientEffect_2Val()
{

  memset(&rgb, '\0', sizeof rgb);
  memset(&rgb_2, '\0', sizeof rgb_2);
  rgb.r = WiFiHandler[1].handlerVal;
  rgb.g = WiFiHandler[2].handlerVal;
  rgb.b = WiFiHandler[3].handlerVal;
  white = WiFiHandler[4].handlerVal;

  rgb_2.r = WiFiHandler[5].handlerVal;
  rgb_2.g = WiFiHandler[6].handlerVal;
  rgb_2.b = WiFiHandler[7].handlerVal;
  white_2 = WiFiHandler[8].handlerVal;
  isWhite = LEDS_TYPE;

  //-1 goes if led strip does not have white leds or if led strip is SK6812
  if (isWhite != 1)
  {
    startcolor = CRGB(rgb.r, rgb.g, rgb.b);
    endcolor = CRGB(rgb_2.r, rgb_2.g, rgb_2.b);
    fill_gradient_RGB();
  }
  else
  {
    startcolor_W = CRGBW(rgb.r, rgb.g, rgb.b, white_2);
    endcolor_W = CRGBW(rgb_2.r, rgb_2.g, rgb_2.b, white);
    fill_gradient_RGBW();
    //fill_gradient_RGBW(ledsW, NUM_LEDS, CRGBW(rgb.r, rgb.g, rgb.b, white_2), CRGBW(rgb_2.r, rgb_2.g, rgb_2.b, white));
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

void fill_gradient_RGB()
{
  // if the points are in the wrong order, straighten them
  if ( endpos < startpos ) {
    t = endpos;
    tc = endcolor;
    endcolor = startcolor;
    endpos = startpos;
    startpos = t;
    startcolor = tc;
  }

  rdistance87 = (endcolor.r - startcolor.r) << 7;
  gdistance87 = (endcolor.g - startcolor.g) << 7;
  bdistance87 = (endcolor.b - startcolor.b) << 7;

  pixeldistance = endpos - startpos;
  divisor = pixeldistance ? pixeldistance : 1;

  rdelta87 = rdistance87 / divisor;
  gdelta87 = gdistance87 / divisor;
  bdelta87 = bdistance87 / divisor;

  rdelta87 *= 2;
  gdelta87 *= 2;
  bdelta87 *= 2;

  r88 = startcolor.r << 8;
  g88 = startcolor.g << 8;
  b88 = startcolor.b << 8;
  for ( i = startpos; i <= endpos; i++) {
    leds[i] = CRGB( r88 >> 8, g88 >> 8, b88 >> 8);
    r88 += rdelta87;
    g88 += gdelta87;
    b88 += bdelta87;
  }
}

void fill_gradient_RGBW()
{
  // if the points are in the wrong order, straighten them
  if (endpos < startpos) {
    t = endpos;
    tc_W = endcolor_W;
    endcolor_W = startcolor_W;
    endpos = startpos;
    startpos = t;
    startcolor_W = tc_W;
  }

  rdistance87 = (endcolor_W.r - startcolor_W.r) << 7;
  gdistance87 = (endcolor_W.g - startcolor_W.g) << 7;
  bdistance87 = (endcolor_W.b - startcolor_W.b) << 7;
  wdistance87 = (endcolor_W.w - startcolor_W.w) << 7;

  pixeldistance = endpos - startpos;
  divisor = pixeldistance ? pixeldistance : 1;

  rdelta87 = rdistance87 / divisor;
  gdelta87 = gdistance87 / divisor;
  bdelta87 = bdistance87 / divisor;
  wdelta87 = wdistance87 / divisor;

  rdelta87 *= 2;
  gdelta87 *= 2;
  bdelta87 *= 2;
  wdelta87 *= 2;

  r88 = startcolor_W.r << 8;
  g88 = startcolor_W.g << 8;
  b88 = startcolor_W.b << 8;
  w88 = startcolor_W.w << 8;
  for ( i = startpos; i <= endpos; i++) {
    ledsW[i] = CRGBW(r88 >> 8, g88 >> 8, b88 >> 8, w88 >> 8);
    r88 += rdelta87;
    g88 += gdelta87;
    b88 += bdelta87;
    w88 += wdelta87;
  }
}

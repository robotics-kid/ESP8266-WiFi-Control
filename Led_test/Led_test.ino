#include<FastLED.h>
//#include "FastLED_RGBW.h"
#define NUM_LEDS 40

CRGBW leds[NUM_LEDS];
CRGB* ledsRGB = (CRGB*)&leds[0];
//CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, 6, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));
}

void loop() {
  // put your main code here, to run repeatedly:
  fill_gradient_RGBW(leds, NUM_LEDS, CRGBW(255, 0, 0, 0), CRGBW(0, 255, 0,  0));
  FastLED.show();
  delay(2000);
  
  fill_solid(leds,NUM_LEDS, CRGBW(0,0,0,255));
  FastLED.show();
  delay(2000);
}

#include <FastLED.h>

#define NUM_LEDS  40
#define LED_PIN   6

CRGBW leds[NUM_LEDS];
CRGB* ledsRGB = (CRGB*)&leds[0];
byte inedxPal = 0;

DEFINE_GRADIENT_PALETTE( my_palett ) {
  0,   0, 30, 10,
  2,   1, 50,  3,
  26, 199, 175, 42,
  62,  77, 13,  0,
  88,  73,  0,  0,
  145,  28, 40, 31,
  208, 255, 255, 255,
  255, 255, 255, 255
};

// Gradient palette "DEM_print_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/td/tn/DEM_print.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( DEM_print_gp ) {
  0,   3, 33,  0,
  31,  43, 141,  1,
  63, 255, 255, 145,
  127, 227, 131,  9,
  159,  23,  7,  1,
  191,  23,  7,  0,
  255, 255, 255, 255
};



CRGBPalette16 sourcePal = my_palett;
//CRGBPalette16 tmp;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, 6, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));
  FastLED.setBrightness(100);

}

void loop() {

  //fill_rainbow(leds, NUM_LEDS, hue, 255 / NUM_LEDS);
  //fill_palette(leds, NUM_LEDS, inedxPal, 255 / NUM_LEDS, myPal, 255, LINEARBLEND);
  //leds[random8(0, NUM_LEDS - 1)] = ColorFromPalette(myPal, random8(), 255, LINEARBLEND);
  //fadeToBlackBy(leds, NUM_LEDS, 1);
  fill_palette_RGBW(leds, NUM_LEDS, inedxPal, 255 / NUM_LEDS, sourcePal, 255, LINEARBLEND);

  EVERY_N_MILLISECONDS(50) {
    inedxPal++;
    for (int i = 0; i < 4; i++) {
      blur1d_RGBW(leds, NUM_LEDS, 10);
    }
  }
  FastLED.show();




}

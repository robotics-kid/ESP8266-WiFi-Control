#include <FastLED.h>

#define NUM_LEDS  40
#define LED_PIN   6

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  Serial.begin(115200);
}

void loop() {
  // byte pos_beat = beat8(30, 0);
  byte pos_beat = beatsin8(30, 0, NUM_LEDS - 1, 0, 0);
  byte pos_beat2 = beatsin8(60, 0, NUM_LEDS - 1, 0, 0);
  byte pos_beat3 = beatsin8(45, 0, NUM_LEDS - 1, 0, 0);

  byte pos_beat4 = beatsin8(10, 0, NUM_LEDS - 1, 0, 0);
  byte pos_beat5 = beatsin8(20, 0, NUM_LEDS - 1, 0, 0);

  byte pos_beat6 = beatsin8(35, 0, NUM_LEDS - 1, 0, 0);


  byte color_beat = beatsin8(10, 0, 255, 0, 0);

  leds[(pos_beat + pos_beat2 + pos_beat3) / 3] = CHSV(color_beat, 255, 255);
  leds[(pos_beat5 + pos_beat4) / 2] = CHSV(color_beat + 50, 255, 255);
  leds[(pos_beat6)] = CHSV(color_beat + 100, 255, 255);

  EVERY_N_MILLISECONDS(1) {
    for (int i = 0; i < 4; i++) {
      blur1d(leds, NUM_LEDS, 8 0);
    }
  }

  fadeToBlackBy(leds, NUM_LEDS, 10);



  FastLED.show();
}

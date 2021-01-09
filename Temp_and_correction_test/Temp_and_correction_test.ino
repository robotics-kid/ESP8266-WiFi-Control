
#include <FastLED.h>

#define NUM_LEDS  20
#define LED_PIN   6

CRGB leds[NUM_LEDS];
int i;

void setup() {
  FastLED.setCorrection(UncorrectedColor); // SK6812
  FastLED.setTemperature(ClearBlueSky); //SK6812
  
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
  Serial.begin(115200);

  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(1000);
}

void loop() {
  Temp();
}

void Corrrection() {

  while (Serial.available() == 0) {}
  i = Serial.read();
  i -= 48;
  Serial.println(i);


  switch (i) {

    case 1:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setCorrection(UncorrectedColor); //SK6812
      //leds[0] = CRGB::Red;
      FastLED.show();
      //delay(2000);
      break;

    case 2:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setCorrection(TypicalLEDStrip);
      // leds[0] = CRGB::Green;
      FastLED.show();
      //lay(2000);
      break;

    case 3:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setCorrection(TypicalPixelString); //FOR WS2812B
      //leds[0] = CRGB::Blue;
      FastLED.show();
      //delay(2000);
      break;

    case 4:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setCorrection(TypicalSMD5050); //FOR WS2812B
      // leds[0] = CRGB::Purple;
      FastLED.show();
      //delay(2000);
      break;

    case 5:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setCorrection(Typical8mmPixel); //FOR WS2812B
      // leds[0] = CRGB::Yellow;
      FastLED.show();
      //delay(2000);
      break;
  }
}


void Temp() {
  while (Serial.available() == 0) {}
  i = Serial.read();
  i -= 48;
  Serial.println(i);


  switch (i) {
    case 1:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(Candle); //SK6812
      FastLED.show();
      break;
    case 2:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(Tungsten40W); //SK6812
      FastLED.show();
      break;
    case 3:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(Tungsten100W); //SK6812
      FastLED.show();
      break;
    case 4:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(Halogen); //SK6812
      FastLED.show();
      break;
    case 5:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(CarbonArc); //SK6812
      FastLED.show();
      break;
    case 6:
      fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(HighNoonSun); //SK6812
      FastLED.show();
      break;
    case 7:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(DirectSunlight); //SK6812
      FastLED.show();
      break;
    case 8:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(OvercastSky); //SK6812
      FastLED.show();
      break;
    case 9:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(ClearBlueSky); //SK6812
      FastLED.show();
      break;
    case 10:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(WarmFluorescent); //SK6812
      FastLED.show();
      break;
    case 11:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(StandardFluorescent); //SK6812
      FastLED.show();
      break;
    case 12:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(CoolWhiteFluorescent); //SK6812
      FastLED.show();
      break;
    case 13:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(FullSpectrumFluorescent); //SK6812
      FastLED.show();
      break;
    case 14:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(GrowLightFluorescent); //SK6812
      FastLED.show();
      break;
    case 15:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(BlackLightFluorescent); //SK6812
      FastLED.show();
      break;
    case 16:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(MercuryVapor); //SK6812
      FastLED.show();
      break;
    case 17:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(SodiumVapor); //SK6812
      FastLED.show();
      break;
    case 18:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(MetalHalide); //SK6812
      FastLED.show();
      break;
    case 19:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(HighPressureSodium); //SK6812
      FastLED.show();
      break;
    case 20:
          fill_solid(leds, NUM_LEDS, CRGB::White);
      Serial.println(i);
      FastLED.setTemperature(UncorrectedTemperature); //SK6812
      FastLED.show();
      break;

  }
}

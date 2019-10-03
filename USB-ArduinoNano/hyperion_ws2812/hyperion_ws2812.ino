#include "FastLED.h"
 
// How many leds in your strip?
#define NUM_LEDS 77
 
// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 11
#define CLOCK_PIN 13
 
#define COLOR_ORDER RGB
 
// Adalight sends a "Magic Word" (defined in /etc/boblight.conf) before sending the pixel data
uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;
 
// Baudrate, higher rate allows faster refresh rate and more LEDs (defined in /etc/boblight.conf)
#define serialRate 460800
 
// Define the array of leds
CRGB leds[NUM_LEDS];

void RGBLoop(){
  for(int j = 0; j < 3; j++ ) {
    // Fade IN
    for(int k = 0; k < 256; k=k+3) {
      switch(j) {
        case 0: LEDS.showColor(CRGB(k,0,0)); break;
        case 1: LEDS.showColor(CRGB(0,k,0)); break;
        case 2: LEDS.showColor(CRGB(0,0,k)); break;
      }
      delay(1);
    }
    // Fade OUT
    for(int k = 255; k >= 0; k=k-3) {
      switch(j) {
        case 0: LEDS.showColor(CRGB(k,0,0)); break;
        case 1: LEDS.showColor(CRGB(0,k,0)); break;
        case 2: LEDS.showColor(CRGB(0,0,k)); break;
      }
      delay(1);
    }
  }
  FastLED.show();
  leds[1].r = 254;
  leds[NUM_LEDS-1].r = 254;
  FastLED.show();
  delay(128);
  for(int l = 0; l < NUM_LEDS; l++) {
    leds[l].b = 254;
    FastLED.show();
    delay(2);
    leds[l].b = 0;
   }  
  leds[1].r = 0;
  leds[NUM_LEDS-1].r = 0;
  FastLED.show();
}

void setup() {
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
         FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
     
      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
 
      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
     
        // initial RGB Cycle
        RGBLoop();
       
        Serial.begin(serialRate);
        Serial.print("Ada\n"); // Send "Magic Word" string to host
 
}
 
void loop() {
  // wait for first byte of Magic Word
  for(i = 0; i < sizeof prefix; ++i) {
    waitLoop: while (!Serial.available()) ;;
    // Check next byte in Magic Word
    if(prefix[i] == Serial.read()) continue;
    // otherwise, start over
    i = 0;
    goto waitLoop;
  }
 
  // Hi, Lo, Checksum
 
  while (!Serial.available()) ;;
  hi=Serial.read();
  while (!Serial.available()) ;;
  lo=Serial.read();
  while (!Serial.available()) ;;
  chk=Serial.read();
 
  // if checksum does not match go back to wait
  if (chk != (hi ^ lo ^ 0x55))
  {
    i=0;
    goto waitLoop;
  }
 
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
  // read the transmission data and set LED values
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    byte r, g, b;    
    while(!Serial.available());
    r = Serial.read();
    while(!Serial.available());
    g = Serial.read();
    while(!Serial.available());
    b = Serial.read();
    leds[i].r = r;
    leds[i].g = g;
    leds[i].b = b;
  }
  // shows new values
 FastLED.show();
}

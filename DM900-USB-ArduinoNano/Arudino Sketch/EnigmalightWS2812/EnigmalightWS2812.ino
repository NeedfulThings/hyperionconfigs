/* 
 * Enigmalight WS2812B
 * Talk enigmalight to the Arduino Nano
*/
static const uint8_t 
  Num_Leds   =  62,
  Led_Pin    =  11,
  Brightness =  255;
#define LED_TYPE     WS2812B 
#define COLOR_ORDER  GRB     
static const unsigned long
  SerialSpeed    = 115200, 
  SerialTimeout  = 150000;
#define CLEAR_ON_START
#include <FastLED.h>
CRGB leds[Num_Leds];
uint8_t * ledsRaw = (uint8_t *)leds;
static const uint8_t magic[] = {
  'A','d','a'};
#define MAGICSIZE  sizeof(magic)
#define HICHECK    (MAGICSIZE)
#define LOCHECK    (MAGICSIZE + 1)
#define CHECKSUM   (MAGICSIZE + 2)
#define MODE_HEADER 0
#define MODE_DATA   1
void setup(){
  FastLED.addLeds<LED_TYPE, Led_Pin, COLOR_ORDER>(leds, Num_Leds);
  FastLED.setBrightness(Brightness);
  #ifdef CLEAR_ON_START
    FastLED.show();
  #endif
  Serial.begin(SerialSpeed);
  enigmalight();
}

void enigmalight(){ 
  uint8_t
    mode = MODE_HEADER,
    headPos,
    hi, lo, chk;
  int16_t
    c;
  uint16_t
    outPos;
  uint32_t
    bytesRemaining;
  unsigned long
    lastByteTime,
    lastAckTime,
    t;
  Serial.print("Ada\n");
  lastByteTime = lastAckTime = millis();
  for(;;) {
    t = millis();    
    if((c = Serial.read()) >= 0){
      lastByteTime = lastAckTime = t;       
      switch(mode) {  
      case MODE_HEADER:
        if(headPos < MAGICSIZE){
          if(c == magic[headPos]) headPos++;
          else headPos = 0;
        }
        else{
          switch(headPos){
            case HICHECK:
              hi = c;
              headPos++;
              break;
            case LOCHECK:
              lo = c;
              headPos++;
              break;
            case CHECKSUM:
              chk = c;
              if(chk == (hi ^ lo ^ 0x55)) {
                bytesRemaining = 3L * (256L * (long)hi + (long)lo + 1L);
                outPos = 0;
                memset(leds, 0, Num_Leds * sizeof(struct CRGB));
                mode = MODE_DATA; 
              }
              headPos = 0;
              break;
          }
        }
        break;
        case MODE_DATA:
        if(bytesRemaining > 0) {
          if (outPos < sizeof(leds)){
            #ifdef CALIBRATE
              if(outPos < 3)
                ledsRaw[outPos++] = c;
              else{
                ledsRaw[outPos] = ledsRaw[outPos%3];
                outPos++;
              }
            #else
              ledsRaw[outPos++] = c; 
            #endif
          }
          bytesRemaining--;
        }
        if(bytesRemaining == 0) {
          mode = MODE_HEADER;
          FastLED.show();
        }
        break;
      } 
    } 
    else {
      if((t - lastAckTime) > 1000) {
        Serial.print("Ada\n"); 
        lastAckTime = t; 
      }
      if((t - lastByteTime) > SerialTimeout) {
        memset(leds, 0, Num_Leds * sizeof(struct CRGB)); 
        FastLED.show();
        lastByteTime = t;
      }
    }
  } 
}

void loop()
{}

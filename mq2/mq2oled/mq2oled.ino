
/*  Version 0.01
 *  Just testing the github
 *  comments are missing
 *  final alc level is not valid, but something 
 *  Need more calibration
 */

#include <U8g2lib.h>
#include <FastLED.h>
#include <SPI.h>

CRGB leds[1];

int16_t alc_value = 0;
int16_t basic_value = 25;
int16_t max_sensorvalue = 800;

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void u8g2_prepare() {
  // OLED setup
  u8g2.setFont(u8g2_font_logisoso42_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void u8g2_printnumber(int alc_val) {
  float level = ((alc_val - basic_value) / (max_sensorvalue - basic_value)) * 3.5;   // Calculating from A0 to g/L
  u8g2.setCursor( 1, 5);
  if (level > 0.00) {
    u8g2.print(level, 2);
    u8g2.setFont(u8g2_font_helvB18_tf);
    u8g2.drawStr(105, 25, "%");
  }
  else u8g2.drawStr(1, 5, "0.00%");
  
}
void u8g2_print_int() {
  int16_t  alc_val = analogRead(A0);
  u8g2.setCursor( 1, 5);
  u8g2.setFont(u8g2_font_crox5hb_tr);
  u8g2.print(alc_val);

  u8g2.setCursor( 1, 25);
  float level = (alc_val - basic_value) /450;
  if (level>0.001) u8g2.print(level,3);
  else u8g2.print("No %");
    
}

void u8g2_print_array() {

  int16_t alc_v[300],i,j,swap;
  float level = 0.0;
  for(i=0;i<300;i++) alc_v[i] = analogRead(A0);

  for(i=0;i<299;i++)
      for(j=i+1;j<300;j++)
      {
        if (alc_v[i]>alc_v[j]) {
          swap = alc_v[i];
          alc_v[i] = alc_v[j];
          alc_v[j] = swap;
        }
      }
    for(i=100;i<200;i++)  level += alc_v[i];

    level /= 100.0;

  u8g2.setFont(u8g2_font_crox5hb_tr);
  u8g2.setCursor( 1, 5);
  u8g2.print(level,3);
  //u8g2.setCursor( 1, 25);
  //if (level>0.001) u8g2.print(level,3);
  //else u8g2.drawStr(1,25,"No ALC");
    
}

void setup() {
  u8g2.begin();   // Init of OLED (128x64)
  u8g2_prepare();  
  
  //Serial.begin(9600);
  delay( 3000 );    // Starting delay
  FastLED.addLeds<WS2812, 5, GRB>(leds, 1).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 16 );
  leds[0] = CRGB(0, 0, 255); FastLED.show();  delay(500);
  leds[0] = CRGB(0, 255, 0); FastLED.show();  delay(500);
  leds[0] = CRGB(255, 0, 0); FastLED.show();  delay(500);
  
}

void loop(void) {
  //alc_value = analogRead(A0);
  //Serial.print("A0: "); Serial.println(alc_value); //debug for values
  u8g2.clearBuffer();
  //u8g2_printnumber(alc_value);
  //u8g2_print_int();
  u8g2_print_array();
  u8g2.sendBuffer();
  leds[0] = CRGB(random(0, 255), random(0, 255), random(0, 255));  // 1 led indicator
  FastLED.show();
  delay(100);
}

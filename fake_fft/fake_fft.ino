#include <TFT_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "fix_fft.h" 

#define RGB(r, g, b) (((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3))
#define window 128

TFT_ST7735 tft = TFT_ST7735();

char im[window], data[window];                              //variables for the FFT
char x = 0, ylim = 60;                                //variables for drawing the graphics
int i = 0, val;                                       //counters
float p = 3.1415926;


void setup() {
   Serial.begin(9600);

  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  
  delay(500);
}

void loop() {
  
  int min=1024, max=0;                                //set minumum & maximum ADC values
  for (i = 0; i < 128; i++) {                         //take 128 samples
    val = analogRead(A0);                             //get audio from Analog 0
    data[i] = val / 4 - 128;                          //each element of array is val/4-128
    im[i] = 0;                                        //
    if(val>max) max=val;                              //capture maximum level
    if(val<min) min=val;                              //capture minimum level
  }
  
  fix_fft(data, im, 7, 0);

  for (i = 0; i < 125; i++) {
  float dat = sqrt(data[i] * data[i] + im[i] * im[i]);//filter out noise and hum
  
  tft.drawLine(i, tft.height()-1-dat*3, i, 1, RGB(0,0,0) ); 
  tft.drawLine(i, tft.height()-1, i, tft.height()-1-dat*3, RGB(20,20,20) );
  
  //tft.drawLine(i+1, tft.height()-1-dat, i+1, 1, RGB(0,0,0) ); 
  //tft.drawLine(i+1, tft.height()-1, i+1, tft.height()-1-dat*3, RGB(20,20,20) );
    
  }
  delay(1);
}

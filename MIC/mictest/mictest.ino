/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
unsigned long startMillis= millis();  // Start of sample window


void setup() 
{
   Serial.begin(9600);
}


void loop() 
{
   startMillis= millis();
   while (millis() - startMillis < sampleWindow)
   {
      sample +=  analogRead(A0);
   }
  Serial.println(sample);
  sample = 0;
}

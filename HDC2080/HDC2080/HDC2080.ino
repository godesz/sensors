#include <HDC2080.h>

#define ADDR 0x40
HDC2080 sensor(ADDR);

float temperature = 0, humidity = 0;

void setup() {

  Serial.begin(9600);
  Serial.println("TinkeringTech HDC2080 Test");

  // Initialize I2C communication
  sensor.begin();
    
  // Begin with a device reset
  sensor.reset();
  
  // Set up the comfort zone

  // Configure Measurements
  sensor.setMeasurementMode(TEMP_AND_HUMID);  // Set measurements to temperature and humidity
  sensor.setRate(TEN_SECONDS);                     // Set measurement frequency to 1 Hz
  sensor.setTempRes(FOURTEEN_BIT);
  sensor.setHumidRes(FOURTEEN_BIT);
  
  //begin measuring
  sensor.triggerMeasurement();
}

void loop() {

  Serial.print("Temperature\t"); Serial.print(sensor.readTemp());
  Serial.print("\tHumidity\t"); Serial.println(sensor.readHumidity());
  
  
  delay(1000);
  
}

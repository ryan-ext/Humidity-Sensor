/*************************************************** 
  This code is adapted from the example code provided by Adafruit for
  the SHT40 breakout board to incorporate calibration coeffients for RH.

  Designed specifically to work with the SHT4x sensor from Adafruit
  ----> https://www.adafruit.com/products/4885

  These sensors use I2C to communicate, 2 pins are required to  
  interface
 ****************************************************/

#include "Adafruit_SHT4x.h"

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

//Linear calibration coefficients, slope and y-intercept.
float m;
float b;
float RH;

void setup() {
  Serial.begin(115200);

  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit SHT4x test");
  if (! sht4.begin()) {
    Serial.println("Couldn't find SHT4x");
    while (1) delay(1);
  }
  Serial.println("Found SHT4x sensor");
  Serial.print("Serial number 0x");
  Serial.println(sht4.readSerial(), HEX);

  // You can have 3 different precisions, higher precision takes longer
  sht4.setPrecision(SHT4X_HIGH_PRECISION);

  // You can have 6 different heater settings
  // higher heat and longer times uses more power
  // and reads will take longer too!
  sht4.setHeater(SHT4X_NO_HEATER);
}


void loop() {
  sensors_event_t humidity, temp;
  
  RH = (humidity.relative_humidity - b ) / m;

  uint32_t timestamp = millis();
  sht4.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  timestamp = millis() - timestamp;

  Serial.print("Temperature: "); 
  Serial.print(temp.temperature); 
  Serial.println(" C");
  Serial.print("Humidity: "); 
  Serial.print(RH); 
  Serial.println("% rH");

  Serial.print("Read duration (ms): ");
  Serial.println(timestamp);

  delay(1000);
}
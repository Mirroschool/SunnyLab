#ifndef _SENSORS_H
#define _SENSORS_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define MHZ19_PWM_PIN D3

int previousPPM = -1;

Adafruit_BME280 bme;

void setupSensors(){
  bme.begin(&Wire);
}

int getPreassure(){
  return bme.readPressure() * 0.00750062; // Converts Pascal value to Torr
}

int getHumidity(){
  return bme.readHumidity(); // Converts Pascal value to Torr
}

float getTemperature(){
  return bme.readTemperature();
}

int getPPM(){
  // high and low level output duration in one cycle
  uint32_t highPulseLength = pulseIn(MHZ19_PWM_PIN, HIGH, 1004000) / 1000;
  uint32_t lowPulseLength = 1004 - highPulseLength;
  int16_t ppm = 2000 * (highPulseLength - 2) / (highPulseLength + lowPulseLength - 4);
 
  if (ppm > 0){
    previousPPM = ppm;
  }
  
  return previousPPM;
}

#endif

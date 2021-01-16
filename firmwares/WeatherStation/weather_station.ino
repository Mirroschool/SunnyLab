#include <Arduino.h>
#include <Wire.h>

#include "clock.h"
#include "led.h"
#include "render.h"
#include "sensors.h"
#include "buttonMinim.h"

uint32_t bmePollingTimer, mhzPollingTimer, clockUpdateTimer, dotUpdateTimer;
int humidity, preassure, ppm;
float temperature;
bool showDots;

void updateBMEReadings(){
  temperature = getTemperature();
  preassure = getPreassure();
  humidity = getHumidity();  
}

void renderSensors(){
  drawTemperature(temperature);
  drawPreassure(preassure);
  drawHumidity(humidity);
  drawPPM(ppm);

  if (ppm > 1200){
    setLEDColor(250, 0, 0);
  } else {
    setLEDColor(0, 125, 0);
  }
}

buttonMinim bigDigBtn(D0);

void setup() {
  Serial.begin(115200);
  setupSensors();
  setupLED();
  setupLCD();

  updateBMEReadings();
  ppm = getPPM();
  
  renderSensors();
  now = rtc.GetDateTime();
}

void loop() {
  if (Serial.available() > 0) {
    uint32_t newSecondsFrom2000 = Serial.parseInt();
    if (newSecondsFrom2000 > 315400000){
      now = RtcDateTime(newSecondsFrom2000);
      rtc.SetDateTime(now);
  
      char buf[100];
      snprintf(
        buf, 
        sizeof(buf), 
        "Succesfully set datetime! Date: %d.%d.%d | Time: %d:%d:%d", 
        now.Day(), now.Month(), now.Year(), now.Hour(), now.Minute(), now.Second()
      );
      Serial.println(buf);
    } else {
      Serial.println("Not valid datetime!");
    }
  }

  if (bigDigBtn.holded()){
    bigDig = !bigDig;
    lcd.clear();
    reloadClock();
    drawClock(now.Hour(), now.Minute(), now.Second());
    drawDate(now.Year(), now.Month(), now.Day(), now.DayOfWeek());
    renderSensors();
  }
  
  if (millis() - bmePollingTimer > 5000){
    bmePollingTimer = millis();
    updateBMEReadings();
    renderSensors();
  }

  if (millis() - mhzPollingTimer > 60000){
    mhzPollingTimer = millis();
    ppm = getPPM();
    renderSensors();
  }
  if (millis() - dotUpdateTimer > 500){
    dotUpdateTimer = millis();
    drawDots(showDots);
    showDots = !showDots;
  }
  
  if (millis() - clockUpdateTimer > 1000){
    now += (millis() - clockUpdateTimer) / 1000;
    clockUpdateTimer = millis();
    drawClock(now.Hour(), now.Minute(), now.Second());
    drawDate(now.Year(), now.Month(), now.Day(), now.DayOfWeek());
  }
}

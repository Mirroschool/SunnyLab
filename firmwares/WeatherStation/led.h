#ifndef _LED_H
#define _LED_H

#define LED_R_PIN D5
#define LED_G_PIN D6
#define LED_B_PIN D7

void setupLED(){
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
}

void setLEDColor(uint8_t red, uint8_t green, uint8_t blue){
  analogWrite(LED_R_PIN, red);
  analogWrite(LED_G_PIN, green);
  analogWrite(LED_B_PIN, blue);
}

#endif

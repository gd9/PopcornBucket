// Programmable Air
// Author: tinkrmind
// github.com/tinkrmind/programmable-air
//
// PCB v0.3/v0.4
//

#include "programmable_air.h"

#define DEBUG 1

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 8

#define NUMPIXELS 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define trigPin 12
#define echoPin 13

void setup() {
  Serial.begin(115200);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
//  while(1);
//
////  while (!Serial);

  // Initiate with all valve and pumps off
  initializePins();
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  //switch on pumps
//  switchOnPumps(150);

  vent(0);
}

void loop() {
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
  if (distance >= 600 || distance <= 2){
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
//  delay(500);

  if (distance >= 9 && distance <= 45.0){ //air blow out
    switchOnPumps(100);
    setAllValves(0);
    blow(0);
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware
  }
  }
  else if(distance >= 13 || distance >= 600) { //air intake
    switchOnPumps(150);
    setAllValves(0);
    suck(0);
  }
  
//  else {
//    setAllValves(0);
//    switchOffPumps();
//    vent(0);
//  }
  delay(100);
}

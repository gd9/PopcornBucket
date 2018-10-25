// Programmable Air
// Author: tinkrmind
// github.com/tinkrmind/programmable-air
//
// PCB v0.3/v0.4
//

#include "programmable_air.h"

#define DEBUG 1

void setup() {
//  Serial.begin(115200);
//  while (!Serial);

  // Initiate with all valve and pumps off
  initializePins();

  //switch on pumps
//  switchOnPumps(150);

  vent(0);
}

void loop() {
  
  if (readBtn(1)) { //air blow out
    switchOnPumps(150);
    setAllValves(0);
    blow(0);

  }
  else if (readBtn(2)) { //air intake
    switchOnPumps(150);
    setAllValves(0);
    suck(0);
  }
  else {
    setAllValves(0);
    switchOffPumps();
    vent(0);
  }
  delay(100);
}

#include "ENJBUZ_module.h"
#include "temp_module.h"
#include "vel_module.h"
void setup() {
  setupENJBUZGPIO();
  setuptempGPIO();
  setupVELGPIO(); 
}

void loop() {
  loopENJBUZGPIO();
  looptempGPIO(); 
  loopVELGPIO();
}

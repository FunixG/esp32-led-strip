#include "LedController.h"

unsigned int tmp = 0;
bool increase = true;

void setup() {
  setupLeds();
  setupWifiClient();
}

void loop() {
  if (tmp >= MAX_LUMINOSITY) {
    increase = false;
  } else if (tmp <= 0) {
    increase = true;
  }

  tmp = increase ? tmp + 1 : tmp - 1;
  setColor(RED_CHANNEL, 0);
  setColor(GREEN_CHANNEL, 0);
  setColor(BLUE_CHANNEL, 0);
  delay(20);
}

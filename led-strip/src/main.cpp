#include <Arduino.h>
#include "./network/WifiESP.h"

WifiESP *wifi;

void setup() {
    wifi = new WifiESP();
}

void loop() {
    wifi->loop();
}

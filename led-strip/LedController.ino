#include "LedController.h"

void setupLeds() {
  ledcSetup(RED_CHANNEL, FREQUENCY, RESOLUTION);
  ledcSetup(GREEN_CHANNEL, FREQUENCY, RESOLUTION);
  ledcSetup(BLUE_CHANNEL, FREQUENCY, RESOLUTION);

  ledcAttachPin(RED_PIN, RED_CHANNEL);
  ledcAttachPin(GREEN_PIN, GREEN_CHANNEL);
  ledcAttachPin(BLUE_PIN, BLUE_CHANNEL);
}

void setColor(const unsigned int channel, unsigned int luminosity) {
  if (luminosity >= MAX_LUMINOSITY) {
    luminosity = 255;
  } else if (luminosity < 0) {
    luminosity = 0;
  }

  if (channel == RED_CHANNEL || channel == GREEN_CHANNEL || channel == BLUE_CHANNEL) {
    ledcWrite(channel, luminosity);
  }

}
#include "LedController.h"

void setupLeds() {
  ledcSetup(RED_CHANNEL, FREQUENCY, RESOLUTION);
  ledcSetup(GREEN_CHANNEL, FREQUENCY, RESOLUTION);
  ledcSetup(BLUE_CHANNEL, FREQUENCY, RESOLUTION);

  ledcAttachPin(RED_PIN, RED_CHANNEL);
  ledcAttachPin(GREEN_PIN, GREEN_CHANNEL);
  ledcAttachPin(BLUE_PIN, BLUE_CHANNEL);

  pinMode(ALERT_LED_PIN, OUTPUT);
}

void setColor(const unsigned int channel, unsigned int luminosity) {
  if (luminosity >= MAX_LUMINOSITY) {
    luminosity = MAX_LUMINOSITY;
  } else if (luminosity < 0) {
    luminosity = 0;
  }

  if (channel == RED_CHANNEL || channel == GREEN_CHANNEL || channel == BLUE_CHANNEL) {
    ledcWrite(channel, luminosity);
  }

}

void switchOff() {
  ledcWrite(RED_CHANNEL, 0);
  ledcWrite(GREEN_CHANNEL, 0);
  ledcWrite(BLUE_CHANNEL, 0);
}
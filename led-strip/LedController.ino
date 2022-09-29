#define RED_PIN 27
#define GREEN_PIN 12
#define BLUE_PIN 14
#define ALERT_LED_PIN 18

#define FREQUENCY 5000
#define RESOLUTION 8

#define MAX_LUMINOSITY 255

void setupLeds() {
  ledcSetup(RED_CHANNEL, FREQUENCY, RESOLUTION);
  ledcSetup(GREEN_CHANNEL, FREQUENCY, RESOLUTION);
  ledcSetup(BLUE_CHANNEL, FREQUENCY, RESOLUTION);

  ledcAttachPin(RED_PIN, RED_CHANNEL);
  ledcAttachPin(GREEN_PIN, GREEN_CHANNEL);
  ledcAttachPin(BLUE_PIN, BLUE_CHANNEL);

  pinMode(ALERT_LED_PIN, OUTPUT);
}

void setColor(const unsigned int channel, int luminosity) {
  if (luminosity >= MAX_LUMINOSITY) {
    luminosity = MAX_LUMINOSITY;
  } else if (luminosity < 0) {
    luminosity = 0;
  }

  if (channel == RED_CHANNEL || channel == GREEN_CHANNEL || channel == BLUE_CHANNEL) {
    ledcWrite(channel, luminosity);
  }

}

void setAlert(bool alert) {
  if (alert) {
    digitalWrite(ALERT_LED_PIN, HIGH);
  } else {
    digitalWrite(ALERT_LED_PIN, LOW);
  }
}

void switchOff() {
  ledcWrite(RED_CHANNEL, 0);
  ledcWrite(GREEN_CHANNEL, 0);
  ledcWrite(BLUE_CHANNEL, 0);
}
#include <WiFi.h>

#include "LedController.h"
#include "WifiHandle.h"

WiFiServer server(80);
WiFiClient client;

#define BUTTON_WIFI_RESET_PIN 20

void setup() {
  setupLeds();
  setupWifiClient();

  pinMode(BUTTON_WIFI_RESET_PIN, INPUT);
  disconnectWifi();
}

void loop() {
  if (digitalRead(BUTTON_WIFI_RESET_PIN)) {
    disconnectWifi();
  }

  if (wifiConnected()) {
    digitalWrite(ALERT_LED_PIN, LOW);
  } else {
    digitalWrite(ALERT_LED_PIN, HIGH);
    reconnectWifi();
  }
}

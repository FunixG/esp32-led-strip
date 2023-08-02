#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

#define BUTTON_WIFI_RESET_PIN 33

WiFiClient client;

WebServer server(80);

String red;
String green;
String blue;

void setup() {
  setupLeds();
  setupWifiClient();
  setupConfigWifiRoutes();

  pinMode(BUTTON_WIFI_RESET_PIN, INPUT_PULLDOWN);

  server.on("/led", HTTP_GET, requestLedColor);
  server.on("/led/off", HTTP_GET, turnOffRequest);
  server.begin();
}

void loop() {
  if (digitalRead(BUTTON_WIFI_RESET_PIN) == HIGH) {
    disconnectWifi();
  }

  if (wifiConnected()) {
    setAlert(false);
  } else {
    setAlert(true);
    reconnectWifi();
  }

  server.handleClient();
}

enum parsingColor {
  RED,
  GREEN,
  BLUE,
  NOTHING
};

void requestLedColor() {
  red = server.arg("r");
  green = server.arg("g");
  blue = server.arg("b");

  if (checkIsNumber(red)) {
    setColor(RED_CHANNEL, red.toInt());
  }

  if (checkIsNumber(green)) {
    setColor(GREEN_CHANNEL, green.toInt());
  }

  if (checkIsNumber(blue)) {
    setColor(BLUE_CHANNEL, blue.toInt());
  }

  server.send(200, "text/json", "{success: true}");
}

void turnOffRequest() {
  switchOff();
  server.send(200, "text/json", "{success: true}");
}

bool checkIsNumber(String data) {
  if (data == nullptr) {
    return false;
  }

  const unsigned int size = data.length();
  if (size == 0) {
    return false;
  }

  for (unsigned int i = 0; i < size; ++i) {
    if (data[i] > '9' || data[i] < '0') {
      return false;
    }
  }
  return true;
}

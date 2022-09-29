#include <WiFi.h>
#include <WebServer.h>

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

#define BUTTON_WIFI_RESET_PIN 20

WebServer server(80);

String red;
String green;
String blue;

void setup() {
  setupLeds();
  setupWifiClient();
  setupConfigWifiRoutes();

  pinMode(BUTTON_WIFI_RESET_PIN, INPUT);

  server.on("/led", HTTP_GET, requestLedColor);
  server.on("/led/off", HTTP_GET, turnOffRequest);

  server.begin();
}

void loop() {
  if (digitalRead(BUTTON_WIFI_RESET_PIN)) {
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

void requestLedColor() {
  red = server.arg("r");
  green = server.arg("g");
  blue = server.arg("b");

  setColor(RED_CHANNEL, red.toInt());
  setColor(GREEN_CHANNEL, green.toInt());
  setColor(BLUE_CHANNEL, blue.toInt());
  server.send(200, "text/json", "{succes: true}");
}

void turnOffRequest() {
  switchOff();
  server.send(200, "text/json", "{succes: true}");
}

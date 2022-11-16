#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>

#define RED_CHANNEL 0
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

#define BUTTON_WIFI_RESET_PIN 33

#define MQTT_HOST "broker.emqx.io"
#define MQTT_TOPIC "funix/led/salon"
#define MQTT_PORT 1883
WiFiClient client;
PubSubClient mqttClient(client);

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

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(mqttCallback);
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

  if (!mqttClient.connected()) {
    mqttClient.connect("funix/led/salon/ESP_32");
    mqttClient.subscribe(MQTT_TOPIC);
  } else {
    mqttClient.loop();
  }
}

enum parsingColor {
  RED,
  GREEN,
  BLUE,
  NOTHING
};

void mqttCallback(const char* topic, const byte* message, unsigned int length) {
  red = "";
  green = "";
  blue = "";

  char c = '\0';
  enum parsingColor parsing;

  for (int i = 0; i < length; ++i) {
    c = message[i];

    if (c == 'r') {
      parsing = RED;
    } else if (c == 'g') {
      parsing = GREEN;
    } else if (c == 'b') {
      parsing = BLUE;
    } else if (c >= '0' && c <= '9') {
      if (parsing == RED) {
        red += c;
      } else if (parsing == GREEN) {
        green += c;
      } else if (parsing == BLUE) {
        blue += c;
      }
    }
  }

  if (checkIsNumber(red)) {
    setColor(RED_CHANNEL, red.toInt());
  }
  if (checkIsNumber(green)) {
    setColor(GREEN_CHANNEL, green.toInt());
  }
  if (checkIsNumber(blue)) {
    setColor(BLUE_CHANNEL, blue.toInt());
  }
}

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

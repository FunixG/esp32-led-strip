#include <WiFi.h>

#include "WifiHandle.h"
#include "ConnectToWifi.h"

bool resetWifi = false;

void setupWifiClient() {
  WiFi.setAutoConnect(true);
  WiFi.setHostname(HOSTNAME);
  WiFi.begin();
}

bool wifiConnected() {
  return WiFi.isConnected();
}

void disconnectWifi() {
  resetWifi = true;

  if (wifiConnected()) {
    WiFi.disconnect();
  }
  switchOnAP();
}

void reconnectWifi() {
  if (resetWifi) {
    httpLoopWifiAP();
  } else {
    WiFi.begin();
  }
}

//Connect to netwotrk, true if success false otherwise
bool connectToWifi(char* wifi_ssid_to_connect, char* wifi_password_to_connect) {
  const unsigned long startTime = millis();
  unsigned long actualTime = startTime;

  if (wifi_ssid_to_connect == nullptr || wifi_password_to_connect == nullptr) {
    return false;
  }

  WiFi.begin(wifi_ssid_to_connect, wifi_password_to_connect);

  while (!wifiConnected()) {
    actualTime = millis();
    if (actualTime - startTime > TIME_OUT_WIFI) {
      return false;
    }
  }

  resetWifi = false;
  switchOffAP();
  return true;
}
#include <WiFi.h>

#define TIME_OUT_WIFI 10000

void setupWifiClient() {
  WiFi.setAutoConnect(true);
  WiFi.begin();
}

bool wifiConnected() {
  return WiFi.isConnected();
}

char* getWifiClientIp() {
  if (wifiConnected()) {
    return WiFi.localIP();
  } else {
    return NULL;
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

  while (!WiFi.isConnected()) {
    actualTime = millis();
    if (actualTime - startTime > TIME_OUT_WIFI) {
      return false;
    }
  }

  Serial.println();
  Serial.println("Success: Wifi connected !");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  return true;
}
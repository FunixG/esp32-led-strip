//
// Created by Antoine Pronnier on 04/01/2024.
//

#ifndef LED_STRIP_WIFIESP_H
#define LED_STRIP_WIFIESP_H

#include <Arduino.h>
#include <WiFi.h>
#include "network/WifiAccessPoint.h"

#define BUTTON_WIFI_RESET_PIN 33
#define ALERT_WIFI_LED_PIN 18
#define ALERT_RESET_MODE_LED_PIN 19

#define TIME_OUT_WIFI 10000
#define HOSTNAME "Esp32-LedStripController"

class WifiESP {
private:
    bool resetWifi = false;

    static void reconnect();
    static void setAlert(bool alert);
public:
    WifiESP();

    static bool connect(const String& ssid, const String& password);
    static bool isConnected();
    static void disconnect();
    void loop();
};

#endif //LED_STRIP_WIFIESP_H

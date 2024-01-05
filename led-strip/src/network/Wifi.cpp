//
// Created by Antoine Pronnier on 04/01/2024.
//

#include "network/WifiESP.h"

WifiESP::WifiESP() {
    WiFiClass::setHostname(HOSTNAME);
    WiFiClass::mode(WIFI_STA);
    WiFi.setAutoConnect(true);
    WiFi.begin();

    pinMode(BUTTON_WIFI_RESET_PIN, INPUT_PULLDOWN);
    pinMode(ALERT_WIFI_LED_PIN, OUTPUT);
    pinMode(ALERT_RESET_MODE_LED_PIN, OUTPUT);
}

bool WifiESP::connect(const String& ssid, const String& password) {
    const unsigned long startTime = millis();
    unsigned long actualTime;

    WiFi.begin(ssid.c_str(), password.c_str());
    while (!WifiESP::isConnected()) {
        actualTime = millis();

        if (actualTime - startTime > TIME_OUT_WIFI) {
            WifiESP::disconnect();
            return false;
        }
    }

    return true;
}

void WifiESP::disconnect() {
    if (WifiESP::isConnected()) {
        WiFi.disconnect();
    }
}

bool WifiESP::isConnected() {
    return WiFi.isConnected();
}

void WifiESP::loop() {
    if (digitalRead(BUTTON_WIFI_RESET_PIN) == HIGH) {
        WifiESP::disconnect();
        this->resetWifi = true;
        digitalWrite(ALERT_RESET_MODE_LED_PIN, HIGH);
    }

    if (WifiESP::isConnected()) {
        setAlert(false);
    } else {
        setAlert(true);

        if (this->resetWifi) {
            WifiAccessPoint wifiAccessPoint;
            while (!WifiESP::isConnected()) {
                wifiAccessPoint.loop();
            }
            this->resetWifi = false;
            digitalWrite(ALERT_RESET_MODE_LED_PIN, LOW);
        } else {
            WifiESP::reconnect();
            sleep(10);
        }
    }
}

void WifiESP::reconnect() {
    WiFi.begin();
}

void WifiESP::setAlert(bool alert) {
    if (alert) {
        digitalWrite(ALERT_WIFI_LED_PIN, HIGH);
    } else {
        digitalWrite(ALERT_WIFI_LED_PIN, LOW);
    }
}

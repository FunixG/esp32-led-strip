//
// Created by Antoine Pronnier on 05/01/2024.
//

#ifndef LED_STRIP_WIFIACCESSPOINT_H
#define LED_STRIP_WIFIACCESSPOINT_H

#include <string>
#include <WebServer.h>
#include "network/WifiESP.h"

#define ACCESS_POINT_NAME "ESP32_LedStrip"
#define ACCESS_POINT_PASSWORD "ESP32_SetupNetwork_LedStrip"

class WifiAccessPoint {
private:
    WebServer server;

    static void closeAp();
    void onConnectPageRequest();
    void onConnectRequest(const String &ssid, const String &password);
public:
    explicit WifiAccessPoint();

    void loop();
};


#endif //LED_STRIP_WIFIACCESSPOINT_H

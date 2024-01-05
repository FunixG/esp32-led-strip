//
// Created by Antoine Pronnier on 05/01/2024.
//

#include "network/WifiAccessPoint.h"

WifiAccessPoint::WifiAccessPoint() : server(80) {
    IPAddress localIp(192,168,4,1);
    IPAddress subnet(255,255,255,0);

    WiFi.softAPConfig(localIp, localIp, subnet);
    WiFi.softAP(ACCESS_POINT_NAME, ACCESS_POINT_PASSWORD);
    WiFiClass::mode(WIFI_AP);

    this->server.on("/connect", HTTP_GET, [this]() {
        this->onConnectPageRequest();
    });

    this->server.on("/connect/set", HTTP_GET, [this]() {
        this->onConnectRequest(this->server.arg("ssid"),
                               this->server.arg("password"));
    });

    this->server.begin();
}

void WifiAccessPoint::closeAp() {
    WiFi.softAPdisconnect(true);
    WiFiClass::mode(WIFI_STA);
}

void WifiAccessPoint::onConnectPageRequest() {
    int nbrNetworks = WiFi.scanNetworks();

    String page = "<!DOCTYPE html><html>";
    page += "<head>";
    page += "   <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    page += "   <link rel=\"icon\" href=\"data:,\">";
    page += "   <style>";
    page += "       html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
    page += "       .button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
    page += "       .button2 {background-color: #555555;}";
    page += "   </style>";
    page += "</head>";
    page += "<body>";
    page += "   <h1>ESP32 Web Server login wifi</h1>";
    page += "   <form action=\"/connect/set\" method=\"GET\">";
    page += "       <p><label for=\"uname\"><b>Nom du reseau</b></label><input type=\"text\" placeholder=\"Entrez le nom du reseau\" name=\"ssid\" required></p>";
    page += "       <p><label for=\"uname\"><b>Mot de passe</b></label><input type=\"password\" placeholder=\"Entrez le mot de passe\" name=\"password\" required></p>";
    page += "       <p><button type=\"submit\">Login</button></p>";
    page += "   </form>";
    page += "   <div>";
    page += "       <h3>Networks SSIDs available : " + String(nbrNetworks) + ". </h3>";
    for (int i = 0; i < nbrNetworks; ++i) {
        page += "<p>" + WiFi.SSID(i) + "</p>";
    }
    page += "   </div>";
    page += "</body></html>";

    server.setContentLength(page.length());
    server.send(200, "text/html", page);
}

void WifiAccessPoint::onConnectRequest(const String &ssid, const String &password) {
    if (ssid.length() > 0 && password.length() > 0) {
        if (WifiESP::connect(ssid, password)) {
            WifiAccessPoint::closeAp();
            server.send(200, "text/json", "{success: true}");
        } else {
            server.send(400, "text/json", "{success: false, error: \"Unable to connect to the network\"}");
        }
    } else {
        server.send(400, "text/json", "{success: false, error: \"Missing parameters ssid and password\"}");
    }
}

void WifiAccessPoint::loop() {
    this->server.handleClient();
}
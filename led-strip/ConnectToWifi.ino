#define ACCESS_POINT_NAME "ESP32_LedStrip"
#define ACCESS_POINT_PASSWORD "ESP32_SetupNetwork"

void setupConfigWifiRoutes() {
  server.on("/connect", HTTP_GET, connectPage);
  server.on("/connect/set", HTTP_GET, connectRequest);
}

void switchOnAP() {
  IPAddress localIp(192,168,4,1);
  IPAddress gateway(192,168,4,2);
  IPAddress subnet(255,255,255,0);

  WiFi.softAPConfig(localIp, gateway, subnet);
  WiFi.softAP(ACCESS_POINT_NAME, ACCESS_POINT_PASSWORD);
  WiFi.mode(WIFI_AP);
}

void switchOffAP() {
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
}

void connectPage() {
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
  page += "       <p><label for=\"uname\"><b>Nom du reseau</b></label><input type=\"text\" placeholder=\"Entrez le nom du reseau\" name=\"networkname\" required></p>";
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

void connectRequest() {
  String ssid = server.arg("networkname");
  String password = server.arg("password");

  if (ssid.length() > 0 && password.length() > 0) {
    if (connectToWifi(ssid.c_str(), password.c_str())) {
      server.send(200, "text/html", "<!DOCTYPE html><html><body><h1>Success</h1><p>Votre ESP32 est connecté au réseau.</p></body></html>");
    } else {
      server.send(400, "text/html", "<!DOCTYPE html><html><body><h1>Erreur 400</h1><p>Les identifiants pour se connecter sont invalides.</p></body></html>");
    }
  } else {
    server.send(400, "text/html", "<!DOCTYPE html><html><body><h1>Erreur 400</h1><p>Vous n'avez pas entré le nom du réseau ou le mot de passe.</p></body></html>");
  }
}


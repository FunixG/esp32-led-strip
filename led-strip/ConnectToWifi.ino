#include <WiFi.h>

#include "ConnectToWifi.h"
#include "HttpParser.h"

void switchOnAP() {
  IPAddress localIp(192,168,4,2);
  IPAddress gateway(192,168,4,1);
  IPAddress subnet(255,255,255,0);

  WiFi.softAPConfig(localIp, gateway, subnet);
  WiFi.softAP(ACCESS_POINT_NAME, ACCESS_POINT_PASSWORD);
}

void httpLoopWifiAP() {
  client = server.available();

  if (client) {
    const char *header = fetchPartFromClient().c_str();

    Serial.println(header);
    if (strstr(header, "POST /connect") != nullptr) {
      String body = fetchPartFromClient();
      char *body_c = new char [body.length()+1];
      strcpy(body_c, body.c_str());

      char *part1 = strtok(body_c, "&");
      char *part2 = strtok(NULL, "&");

      strtok(part1, "=");
      char *wifi_ssid_to_connect = strtok(NULL, "=");
      strtok(part2, "=");
      char *wifi_password_to_connect = strtok(NULL, "=");

      delete[] body_c;
      if (connectToWifi(wifi_ssid_to_connect, wifi_password_to_connect)) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

        client.println("<!DOCTYPE html><html>");
        client.println("<body><h1>ESP32 Web Server</h1>");
        client.println("<p>Connection success.</p>");
        client.println("</body></html>");
      } else {
        client.println("HTTP/1.1 400 Bad Request");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();

        client.println("<!DOCTYPE html><html>");
        client.println("<body><h1>ESP32 Web Server</h1>");
        client.println("<p>Connection wifi error.</p>");
        client.println("</body></html>");
      }
    } else if (strstr(header, "GET /connect") != nullptr) {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println("Connection: close");
      client.println();

      client.println("<!DOCTYPE html><html>");
      client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
      client.println("<link rel=\"icon\" href=\"data:,\">");

      client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
      client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
      client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
      client.println(".button2 {background-color: #555555;}</style></head>");

      client.println("<body><h1>ESP32 Web Server</h1>");

      client.println("<form action=\"/connect\" method\"POST\">");
      client.println("<p><label for=\"uname\"><b>Nom du reseau</b></label><input type=\"text\" placeholder=\"Entrez le nom du reseau\" name=\"networkname\" required>");

      client.println("<p><label for=\"uname\"><b>Mot de passe</b></label><input type=\"password\" placeholder=\"Entrez le mot de passe\" name=\"password\" required>");

      client.println("<p><button type=\"submit\">Login</button></p>");
      client.println("</form></body></html>");
      client.println();
    }

    client.stop();
  }
}

void switchOffAP() {
  WiFi.softAPdisconnect(true);
}

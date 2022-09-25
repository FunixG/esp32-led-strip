#define TIME_OUT_WIFI 10000
#define HOSTNAME "Esp32-LedStripController"

void setupWifiClient();
bool wifiConnected();
void disconnectWifi();
void reconnectWifi();
bool connectToWifi(char* wifi_ssid_to_connect, char* wifi_password_to_connect);

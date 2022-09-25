#include "HttpParser.h"

String fetchPartFromClient() {
  String data = "";
  char lastChar = 'a';
  char c;

  while (client.connected()) {
    if (client.available()) {
      c = client.read();

      if (c == '\n') {
        if (lastChar == '\n') {
          break;
        }
      } else {
        data += c;
      }

      lastChar = c;
    } else {
      break;
    }
  }

  return data;
}
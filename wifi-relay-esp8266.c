#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String page = "";
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", page);
}

void handleOn() {
  Serial.println("On");
  server.send(200, "text/plain", "On");
}

void handleOff() {
  Serial.println("Off");
  server.send(200, "text/plain", "Off");
}

void setup(void) {
  Serial.begin(115200);
  WiFi.begin("SSID", "PASSWORD");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println();
  Serial.println(WiFi.localIP());

  server.on("/home.htm", handleRoot);
  server.on("/turnOn", handleOn);
  server.on("/turnOff", handleOff);

  server.begin();
  Serial.println("home.htm");
}

void loop() {
  if (Serial.available()) {
    page += (char)Serial.read();
  }
  server.handleClient();
}

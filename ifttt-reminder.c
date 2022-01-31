#include "ESP8266.h"
#include <SoftwareSerial.h>

#define SSID        "SSID"
#define PASSWORD    "PASSWORD"
#define BTN_PIN     12

SoftwareSerial mySerial(4, 5);
ESP8266 wifi(mySerial);
boolean buttonWasUp = true;
String maker_ID = "qwe123";

void setup(void) {
  Serial.begin(9600);
  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.println("I'm ready! Press the button.");
  } else {
    Serial.println("Wi-Fi connection error");
  }
}

void loop(void) {
  boolean buttonIsUp = digitalRead(BTN_PIN);
  if (buttonWasUp && !buttonIsUp) {
    delay(10);
    buttonIsUp = digitalRead(BTN_PIN);
    if (!buttonIsUp) {
      sendEmail();
      Serial.println("Notification has been sent");
    }
  }
  buttonWasUp = buttonIsUp;
}

boolean sendEmail() {
  if (wifi.createTCP("maker.ifttt.com", 80)) {
    String value1 = "Hello!";
    String request = "GET /trigger/trigger/with/key/" + maker_ID + "?value1=" + value1 + " HTTP/1.1\r\n";
    request += "Host: maker.ifttt.com\r\n\r\n";
    wifi.send(request.c_str(), request.length());
    wifi.releaseTCP();
  } else {
    Serial.println("create tcp error");
  }
}

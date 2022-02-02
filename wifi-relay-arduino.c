#include <SPI.h>
#include <SD.h>

#define RELAY A4

File myFile;

void setup() {
  Serial.begin(115200);
  SD.begin(8);
  pinMode(RELAY, OUTPUT);
}

void loop() {
  String command = Serial.readStringUntil('\n');
  command.trim();

  if (command == "On") {
    digitalWrite(RELAY, HIGH);
  }
  if (command == "Off") {
    digitalWrite(RELAY, LOW);
  }
  if (command == "home.htm") {
    myFile = SD.open("home.htm");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  }
}

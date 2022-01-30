#include <SPI.h>
#include <SD.h>
#include <math.h>

#define LIGHT_PIN A3
#define TEMP_PIN A2
#define CS 8

void setup() {
  Serial.begin(9600);
  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    return;
  }
}

void loop() {
  float r_light = 10.0 / (1023.0 / analogRead(LIGHT_PIN) - 1.0);
  float light = 10.0 * pow(14.0 / r_light, 1.6);

  float v_temp = 1023.0 / analogRead(TEMP_PIN) - 1.0;
  float temp = 1.0 / ( -log(v_temp) / 3977.0 + 1.0 / 295.0 ) - 273.0;

  String data = String(millis() / 1000) + ";" + String(light) + ";" + String(temp);
  data.replace(".", ",");
  Serial.println(data);

  File logFile = SD.open("log.csv", FILE_WRITE);
  logFile.println(data);
  logFile.close();

  delay(1000);
}

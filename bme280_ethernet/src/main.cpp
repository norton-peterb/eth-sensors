#include <Arduino.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;
char buffer[128];
char valBufferT[32];
char valBufferP[32];
char valBufferH[32];
float temperature = 0;
float pressure = 0;
float humidity = 0;

void setup() {
  bme.begin(0x76);
  Serial.begin(9600);
}

void buildSensorData() {
  dtostrf(temperature,-1,1,valBufferT);
  dtostrf(pressure,-1,1,valBufferP);
  dtostrf(humidity,-1,1,valBufferH);
  sprintf(buffer,"env_temp %s\nenv_pressure %s\nenv_humidity %s\n",
    valBufferT,valBufferP,valBufferH);
}

void loop() {
  delay(30000);
  temperature = bme.readTemperature();
  pressure = bme.readPressure() / 100.0f;
  humidity = bme.readHumidity();
  buildSensorData();
  Serial.print(buffer);
}
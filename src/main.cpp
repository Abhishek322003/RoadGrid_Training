// master.cpp
#include <Arduino.h>
#include <Wire.h>

#define SLAVE_ADDR 0x28
const int SDA_PIN = 10;
const int SCL_PIN = 11;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);   // Master mode, custom pins
  Wire.setClock(100000);          // Standard I2C speed
  delay(100);
  Serial.printf("I2C Master started on SDA=%d SCL=%d\n", SDA_PIN, SCL_PIN);
}

void loop() {
  // Example: send 1 -> LED ON
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(1);
  uint8_t rc = Wire.endTransmission();
  Serial.printf("Sent: 1, status=%d\n", rc);
  delay(2000);

  // Example: send 0 -> LED OFF
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0);
  rc = Wire.endTransmission();
  Serial.printf("Sent: 0, status=%d\n", rc);
  delay(2000);
}

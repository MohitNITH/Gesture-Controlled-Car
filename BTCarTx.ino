#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>
#include <SPI.h>

MPU6050 mpu;
SoftwareSerial BTSerial(10, 11); // RX, TX

void setup() {
  Serial.begin(115200);
  BTSerial.begin(38400);
  Wire.begin();
  mpu.initialize();
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Determine gesture based on acceleration values
  if (ay > 10000) {
    BTSerial.write('F');
    Serial.println("F");// Move Forward
  } else if (ay < -10000) {
    BTSerial.write('B');
    Serial.println("B");// Move Backward
  } else if (ax > 10000) {
    BTSerial.write('R');
    Serial.println("R");// Turn Right
  } else if (ax < -10000) {
    BTSerial.write('L');
    Serial.println("L");// Turn Left
  } else {
    BTSerial.write('S');
    Serial.println("S");// Stop
  }

  delay(100);
}

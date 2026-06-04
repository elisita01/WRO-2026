#include <Wire.h>
#include <Adafruit_VL53L0X.h>

#define SLAVE_ADDRESS 8

#define XSHUT_1 2
#define XSHUT_2 3
#define XSHUT_3 4

Adafruit_VL53L0X sensor1;
Adafruit_VL53L0X sensor2;
Adafruit_VL53L0X sensor3;

VL53L0X_RangingMeasurementData_t m1;
VL53L0X_RangingMeasurementData_t m2;
VL53L0X_RangingMeasurementData_t m3;

void setup() {

  Serial.begin(9600);
  Wire.begin();

  pinMode(XSHUT_1, OUTPUT);
  pinMode(XSHUT_2, OUTPUT);
  pinMode(XSHUT_3, OUTPUT);

  digitalWrite(XSHUT_1, LOW);
  digitalWrite(XSHUT_2, LOW);
  digitalWrite(XSHUT_3, LOW);

  delay(100);

  // Sensor 1
  digitalWrite(XSHUT_1, HIGH);
  delay(10);

  if (!sensor1.begin()) {
    Serial.println(F("Error S1"));
    while (1);
  }
  sensor1.setAddress(0x30);

  // Sensor 2
  digitalWrite(XSHUT_2, HIGH);
  delay(10);

  if (!sensor2.begin()) {
    Serial.println(F("Error S2"));
    while (1);
  }
  sensor2.setAddress(0x31);

  // Sensor 3
  digitalWrite(XSHUT_3, HIGH);
  delay(10);

  if (!sensor3.begin()) {
    Serial.println(F("Error S3"));
    while (1);
  }
  sensor3.setAddress(0x32);

  Serial.println(F("Sensores listos"));
}

void loop() {

  sensor1.rangingTest(&m1, false);
  sensor2.rangingTest(&m2, false);
  sensor3.rangingTest(&m3, false);

  bool detectar = false;

  if (m1.RangeStatus != 4 && m1.RangeMilliMeter < 200)
    detectar = true;

  if (m2.RangeStatus != 4 && m2.RangeMilliMeter < 200)
    detectar = true;

  if (m3.RangeStatus != 4 && m3.RangeMilliMeter < 200)
    detectar = true;

  Wire.beginTransmission(SLAVE_ADDRESS);

  if (detectar)
    Wire.write('1');
  else
    Wire.write('0');

  Wire.endTransmission();

  delay(100);
}
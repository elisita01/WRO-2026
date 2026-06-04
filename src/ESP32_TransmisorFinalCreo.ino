#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensorIzq;
VL53L0X sensorCen;
VL53L0X sensorDer;

#define XSHUT_IZQ 6
#define XSHUT_CEN 5
#define XSHUT_DER 7

void setup() {

  Serial.begin(115200);

  // UART
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  // I2C
  Wire.begin(8, 9);

  pinMode(XSHUT_IZQ, OUTPUT);
  pinMode(XSHUT_CEN, OUTPUT);
  pinMode(XSHUT_DER, OUTPUT);

  // Apagar todos los sensores
  digitalWrite(XSHUT_IZQ, LOW);
  digitalWrite(XSHUT_CEN, LOW);
  digitalWrite(XSHUT_DER, LOW);

  delay(100);

  digitalWrite(XSHUT_IZQ, HIGH);
  delay(100);

//Sensor de la izquierda
  if (!sensorIzq.init()) {
    Serial.println("Error sensor izquierdo");
    while (1);
  }

  sensorIzq.setAddress(0x30);

//Sensor del centro
  digitalWrite(XSHUT_CEN, HIGH);
  delay(100);

  if (!sensorCen.init()) {
    Serial.println("Error sensor central");
    while (1);
  }

  sensorCen.setAddress(0x31);

//Sensor de la derecha
  digitalWrite(XSHUT_DER, HIGH);
  delay(100);

  if (!sensorDer.init()) {
    Serial.println("Error sensor derecho");
    while (1);
  }

  sensorDer.setAddress(0x32);

  sensorIzq.setTimeout(500);
  sensorCen.setTimeout(500);
  sensorDer.setTimeout(500);

}

void loop() {

  int distanciaIzq = sensorIzq.readRangeSingleMillimeters();
  int distanciaCen = sensorCen.readRangeSingleMillimeters();
  int distanciaDer = sensorDer.readRangeSingleMillimeters();

  Serial.print("Izq: ");
  Serial.print(distanciaIzq);

  Serial.print("  Cen: ");
  Serial.print(distanciaCen);

  Serial.print("  Der: ");
  Serial.println(distanciaDer);

  // Enviamos al otro ESP32 si detecta algo a menos de 20 cm
  if (distancia < 200) {
    Serial2.println(distancia);
  }

  delay(100);
}

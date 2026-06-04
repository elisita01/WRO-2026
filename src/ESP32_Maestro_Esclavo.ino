#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X sensor = Adafruit_VL53L0X();

// MAC del receptor
uint8_t direccionReceptor[] = {
  0xF0, 0x24, 0xF9, 0x0C, 0x6C, 0x2C
};

// Estructura de datos
typedef struct {
  int distancia;
} Datos;

Datos datosEnviar;

void setup() {

  Serial.begin(115200);

  // I2C
  Wire.begin(8, 9);

  WiFi.mode(WIFI_STA);

  // Configurar receptor
  esp_now_peer_info_t peerInfo = {};

  memcpy(peerInfo.peer_addr,
         direccionReceptor,
         6);

  peerInfo.channel = 0;
  peerInfo.encrypt = false;
}

void loop() {

  VL53L0X_RangingMeasurementData_t medida;

  sensor.rangingTest(&medida, false);

  if (medida.RangeStatus != 4) {

    datosEnviar.distancia = medida.RangeMilliMeter;

    Serial.print("Distancia: ");
    Serial.print(datosEnviar.distancia);
    Serial.println(" mm");x

    esp_now_send(
      direccionReceptor,
      (uint8_t *) & datosEnviar,
      sizeof(datosEnviar)
    );
  }

  delay(200);
}
#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include "Adafruit_VL53L0X.h"

// Pines I2C
#define SDA_PIN 8
#define SCL_PIN 9

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// MAC del receptor
uint8_t broadcastAddress[] = {0xA0, 0xF2, 0x62, 0xA6, 0x18, 0xF};

// Estructura jiji
typedef struct struct_message {
  bool ledState;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void setup() {

  Serial.begin(115200);

  // Iniciar I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  WiFi.mode(WIFI_STA);

  // Iniciamos ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error ESP-NOW");
    return;
  }

  // Registramos el receptor
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error agregando receptor");
    return;
  }
}

void loop() {

  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {

    int distancia = measure.RangeMilliMeter / 10;

    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    // Menor o igual a 20 cm
    if (distancia <= 20) {
      myData.ledState = true;
    } else {
      myData.ledState = false;
    }

    // Enviar señal
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  }

  delay(200);
}

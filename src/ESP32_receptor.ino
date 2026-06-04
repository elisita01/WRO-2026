#include <WiFi.h>
#include <esp_now.h>

#define LED_PIN 2

typedef struct struct_message {
  bool ledState;
} struct_message;

struct_message incomingData;

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingDataBytes, int len) {

  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));

  if (incomingData.ledState) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);

  // Iniciamos el ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error iniciando ESP-NOW");
    return;
  }

  // Recibir los datos
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}
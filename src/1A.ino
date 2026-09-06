#include <Wire.h>

#define SLAVE 8

// ------------------ Botón ------------------
const int boton = 12;
bool iniciado = false;

// ------------------ Sensor 1 Izquierda ------------------
const int trig1 = 2;
const int echo1 = 3;

// ------------------ Sensor 2 Centro ------------------
const int trig2 = 4;
const int echo2 = 5;

// ------------------ Sensor 3 Derecha ------------------
const int trig3 = 6;
const int echo3 = 7;

long duration;
int distance;

int medirDistancia(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  return distance;
}

void setup() {

  Wire.begin();
  Serial.begin(9600);

  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);

  pinMode(boton, INPUT_PULLUP);

  Serial.println("Esperando botón de inicio...");
}

void loop() {

if (digitalRead(boton) == LOW) {

  // Medición de los sensores
  int d1 = medirDistancia(trig1, echo1);
  delay(60);

  int d2 = medirDistancia(trig2, echo2);
  delay(60);

  int d3 = medirDistancia(trig3, echo3);
  delay(60);

  byte dato = 0;

  if (d1 < 20)
    dato = 1;
  else if (d2 < 20)
    dato = 2;
  else if (d3 < 20)
    dato = 3;

  // Enviar dato al Arduino esclavo
  Wire.beginTransmission(SLAVE);
  Wire.write(dato);
  Wire.endTransmission();

  // Monitor Serial
  Serial.print("S1: ");
  Serial.print(d1);
  Serial.print(" cm  ");

  Serial.print("S2: ");
  Serial.print(d2);
  Serial.print(" cm  ");

  Serial.print("S3: ");
  Serial.print(d3);
  Serial.print(" cm  ");

  Serial.print("Enviado: ");
  Serial.println(dato);

  delay(100);
  }
}



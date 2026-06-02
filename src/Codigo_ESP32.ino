#include <ESP32Servo.h>

#define TRIG1 5
#define ECHO1 18

#define TRIG2 19
#define ECHO2 21

#define TRIG3 35
#define ECHO3 36

#define ENA 1
#define IN1 2
#define IN2 4

#define ENB 7
#define IN3 6
#define IN4 8

#define SERVO_PIN 13

float distancia1;
float distancia2;
float distancia3;

Servo miServo;

float medirDistancia(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH);

  float distancia = duracion * 0.034 / 2;

  return distancia;
}

void setup() {

  Serial.begin(115200);

  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  miServo.attach(SERVO_PIN);

  miServo.write(0);

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Robot iniciado");
}

void loop() {

  distancia1 = medirDistancia(TRIG1, ECHO1);
  distancia2 = medirDistancia(TRIG2, ECHO2);
  distancia3 = medirDistancia(TRIG3, ECHO3);

  Serial.print("Sensor 1: ");
  Serial.print(distancia1);
  Serial.println(" cm");

  Serial.print("Sensor 2: ");
  Serial.print(distancia2);
  Serial.println(" cm");

  Serial.print("Sensor 3: ");
  Serial.print(distancia3);
  Serial.println(" cm");

  if (distancia1 < 40 || distancia2 < 40 || distancia3 < 40) {

    Serial.println("Obstaculo detectado");

    miServo.write(90);

  } else {

    miServo.write(0);
  }

  delay(50);
}
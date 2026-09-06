#include <Wire.h>
#include <Servo.h>

Servo servo;

byte datoRecibido = 0;

// ---------- TB6612 ----------
const int PWMA = 5;
const int AIN1 = 2;
const int AIN2 = 3;

const int PWMB = 6;
const int BIN1 = 4;
const int BIN2 = 7;

// Velocidades
const int velocidadNormal = 255;
const int velocidadMayor = 255;

void recibir(int cantidad) {
  while (Wire.available()) {
    datoRecibido = Wire.read();
  }
}

// Función para avanzar
void avanzar(int velIzq, int velDer) {

  // Motor izquierdo
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, velIzq);

  // Motor derecho
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, velDer);
}

void setup() {

  Wire.begin(8);
  Wire.onReceive(recibir);

  servo.attach(9);
  servo.write(90);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);



  Serial.begin(9600);
}

void loop() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, velocidadNormal);

  // Motor derecho
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, velocidadNormal);

  switch (datoRecibido) {

    case 1:   // Objeto a la izquierda
      servo.write(70);
      avanzar(velocidadMayor, velocidadNormal);
      break;

    case 2:   // Centro
      servo.write(90);
      avanzar(velocidadNormal, velocidadNormal);
      break;

    case 3:   // Objeto a la derecha
      servo.write(110);
      avanzar(velocidadNormal, velocidadMayor);
      break;

    default:
      servo.write(90);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);
      analogWrite(PWMA, 0);

      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMB, 0);
      break;
  }

  delay(20);
}
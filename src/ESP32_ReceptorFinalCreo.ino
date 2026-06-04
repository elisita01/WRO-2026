#include <ESP32Servo.h>

Servo servo;

int angulo;
int distancia;

// TB6612FNG
#define PWMA 5
#define AIN1 10
#define AIN2 0

#define PWMB 6
#define BIN1 1
#define BIN2 2

//#define STBY 4

void setup() {

Serial.begin(115200);

// RX=8 TX=9
Serial1.begin(9600, SERIAL_8N1, 8, 9);
Serial1.setTimeout(50);

servo.attach(7);

pinMode(AIN1, OUTPUT);
pinMode(AIN2, OUTPUT);
pinMode(BIN1, OUTPUT);
pinMode(BIN2, OUTPUT);
// pinMode(STBY, OUTPUT);

pinMode(PWMA, OUTPUT);
pinMode(PWMB, OUTPUT);

//digitalWrite(STBY, HIGH); // habilita el driver

// motores apagados al iniciar
analogWrite(PWMA, 0);
analogWrite(PWMB, 0);
}

void loop() {

if (Serial1.available()) {

distancia = Serial1.parseInt();

if (distancia > 0) {

Serial.print("Distancia: ");
Serial.println(distancia);

// servo
angulo = map(distancia, 20, 200, 0, 180);
angulo = constrain(angulo, 0, 180);
servo.write(angulo);

digitalWrite(AIN1, HIGH);
digitalWrite(AIN2, LOW);

digitalWrite(BIN1, HIGH);
digitalWrite(BIN2, LOW);

analogWrite(PWMA, 200);
analogWrite(PWMB, 200);
}
else {

analogWrite(PWMA, 0);
analogWrite(PWMB, 0);

digitalWrite(AIN1, LOW);
digitalWrite(AIN2, LOW);
digitalWrite(BIN1, LOW);
digitalWrite(BIN2, LOW);
}
}
}

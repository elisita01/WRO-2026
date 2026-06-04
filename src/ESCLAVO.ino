#include <Wire.h>
#include <Servo.h>
//esclavo
#define SLAVE_ADDRESS 8

Servo servo;

// TB6612FNG
const int PWMA = 3;
const int AIN1 = 4;
const int AIN2 = 5;

const int PWMB = 6;
const int BIN1 = 7;
const int BIN2 = 8;

// Servo
const int SERVO_PIN = 10;

char comando = 'S';

void receiveEvent(int howMany)
{
  while (Wire.available())
  {
    comando = Wire.read();
  }
}

void avanzar(){

  // Motor A
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 250);

  // Motor B
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 250);
}

void detener()
{
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

void setup()
{
  Serial.begin(9600);

  // TB6612
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  // Servo
  servo.attach(SERVO_PIN);

  // Centro inicial
  servo.write(90);

  // I2C
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);

  detener();

  Serial.println("Esclavo listo");
}

void loop()
{
  switch(comando)
  {
    // Sensor izquierdo detecta
    case 'L':

      // Girar derecha
      servo.write(100);

      avanzar();

      Serial.println("GIRAR DERECHA");

      break;

    // Sensor derecho detecta
    case 'R':

      // Girar izquierda
      servo.write(60);

      avanzar();

      Serial.println("GIRAR IZQUIERDA");

      break;

    // Sensor central detecta
    case 'B':
    // Centro
      servo.write(110);
      avanzar();

      break;
    
    case 'A':
    // Centro
      servo.write(45);
      avanzar();
      //detener();
      //Serial.println("OBJETO EN FRENTE");
      break;

    // Sin obstaculo
    case 'S':

      servo.write(80);

      avanzar();

      Serial.println("ADELANTE");

      break;
  }

  delay(100);
}

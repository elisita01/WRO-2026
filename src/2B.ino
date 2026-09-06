#include <Wire.h>
#include <Servo.h>

Servo servoDireccion;        // MG995 delantero - dirección
Servo servoMotorIzquierdo;  // MG995 360° - rueda izquierda
Servo servoMotorDerecho;    // MG995 360° - rueda derecha

const int PIN_DIRECCION = 9;

const int PIN_MOTOR_IZQUIERDO = 5;

const int PIN_MOTOR_DERECHO = 10;

byte datoRecibido = 0;

// Posiciones en grados.

const int DIRECCION_CENTRO = 80;

const int DIRECCION_IZQUIERDA = 50;

const int DIRECCION_DERECHA = 110;


const int MOTOR_IZQUIERDO_ADELANTE = 120;

const int MOTOR_DERECHO_ADELANTE = 60;

void recibir(int cantidad) {

  while (Wire.available()) {

    datoRecibido = Wire.read();

  }

}

void avanzar() {

  // Motor izquierdo
  servoMotorIzquierdo.write(MOTOR_IZQUIERDO_ADELANTE);

  // Motor derecho
  servoMotorDerecho.write(MOTOR_DERECHO_ADELANTE);

}

void setup() {

  Wire.begin(8);

  Wire.onReceive(recibir);

  servoDireccion.attach(PIN_DIRECCION);

  servoDireccion.write(DIRECCION_CENTRO);

  servoMotorIzquierdo.attach(PIN_MOTOR_IZQUIERDO);

  servoMotorIzquierdo.write(MOTOR_IZQUIERDO_ADELANTE);

  servoMotorDerecho.attach(PIN_MOTOR_DERECHO);

  servoMotorDerecho.write(MOTOR_DERECHO_ADELANTE);

  Serial.begin(9600);

  Serial.println("Esclavo iniciado");

}

void loop() {

  avanzar();
  switch (datoRecibido) {

    case 1: // El objeto está a la izquierda. // El carrito debe ir hacia la derecha.
      servoDireccion.write(DIRECCION_DERECHA);
      Serial.println("Objeto izquierda -> DIRECCION DERECHA");
      break;

    case 2: // El objeto está en el centro. // Mantener dirección centrada.
      servoDireccion.write(DIRECCION_CENTRO);
      Serial.println("Objeto centro -> DIRECCION CENTRO");
      break;

    case 3: // El objeto está a la derecha. // El carrito debe ir hacia la izquierda.
      servoDireccion.write(DIRECCION_IZQUIERDA);
      Serial.println("Objeto derecha -> DIRECCION IZQUIERDA");
      break;
    
    default: // No hay objeto. // El carrito sigue avanzando. // La dirección vuelve al centro.
      servoDireccion.write(DIRECCION_CENTRO);
      Serial.println("Sin objeto -> AVANZANDO");
      break;

  }


  delay(20);

}

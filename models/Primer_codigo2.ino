#include <Servo.h> //Aquí incluimos la librería del servo

int trigPinI = 2; //Acá estamos declarando nuestros puertos de los ultrasónicos, estos 2 puertos son del ultrasónico de la izquierda
int echoPinI = 3;

int trigPinD = A0; //Estos del ultrasónico de la derecha
int echoPinD = A1;

int trigPinC = A2; //Estos son del ultrasónico del centro
int echoPinC = A3;

Servo miServo; //Aquí llamamos a nuestro servomotor y declaramos su puerto
int pinServo = 7;

int distanciaLimite = 20; //Pusimos un valor límite de separación del ultrasónico a un objeto/pared

long distanciaDerecha = 0; 
long distanciaCentro = 0;
long distanciaIzquierda = 0;

int IN1 = 8; //Pines de el controlador de motores
int IN2 = 9;
int ENA = 5;

int IN3 = 10;
int IN4 = 11;
int ENB = 6;

void setup() {
  pinMode(trigPinI, OUTPUT); //Luego aquí configuramos los puertos de cada ultrasónico
  pinMode(echoPinI, INPUT);
  
  pinMode(trigPinD, OUTPUT);
  pinMode(echoPinD, INPUT);

  pinMode(trigPinC, OUTPUT);
  pinMode(echoPinC, INPUT);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  miServo.attach(pinServo); //Configuración de servo
  miServo.write(105); //Este es el ángulo en donde empieza el servo

  Serial.begin(9600); //Esta es la velocidad de la comunicación entre la compu y el arduino
  delay(5000);
}

void loop() {
  Avanzarmotores();
  distanciaDerecha = medirDistancia(trigPinD, echoPinD); //Acá es una función donde le indicamos que lea la información del ultrasónico derecho 
  distanciaCentro = medirDistancia(trigPinC, echoPinC); //función donde le indicamos que lea la información del ultrasónico centro
  distanciaIzquierda = medirDistancia(trigPinI, echoPinI); //función donde le indicamos que lea la información del ultrasónico izquierdo

Serial.print("Centro: ");
  Serial.println(distanciaCentro);

  Serial.print("Izquierda: ");
  Serial.println(distanciaIzquierda);

  if (distanciaIzquierda < 20 && distanciaIzquierda > 10) { //Si la distancia centro es menor que la distancia límite(20) y la distancia centro es mayor que 5 se moverá nuestro servo
    miServo.write(80);
    delay(2000);

  }
  delay(50); 
  miServo.write(105);

  if (distanciaCentro < 70 && distanciaCentro > 50) { 
    miServo.write(70);
    delay(2000);

  }
  delay(50); 
  miServo.write(105);

}

long medirDistancia(int trigPin, int echoPin) { 
//Esta es la función de medir distancia, aquí se lee toda la información que lleva el ultrasónico, se hacen operaciones matemáticas y luego nos regresa el valor de distancia
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000);


  long distancia = duracion * 0.034 / 2;
  return distancia;
}

void Avanzarmotores(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, 100);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, 80);
}
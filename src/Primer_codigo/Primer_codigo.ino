#include <Servo.h> //Aquí incluimos la librería del servo

int trigPinI = 12; //Acá estamos declarando nuestros puertos de los ultrasónicos, estos 2 puertos son del ultrasónico de la izquierda
int echoPinI = 13;

int trigPinD = A0; //Estos del ultrasónico de la derecha
int echoPinD = A1;

int trigPinC = A2; //Estos son del ultrasónico del centro
int echoPinC = A3;

Servo miServo; //Aquí llamamos a nuestro servomotor y declaramos su puerto
int pinServo = 3;

int distanciaLimite = 20; //Pusimos un valor límite de separación del ultrasónico a un objeto/pared

long distanciaDerecha = 0; 
long distanciaCentro = 0;
long distanciaIzquierda = 0;

void setup() {
  pinMode(trigPinI, OUTPUT); //Luego aquí configuramos los puertos de cada ultrasónico
  pinMode(echoPinI, INPUT);
  
  pinMode(trigPinD, OUTPUT);
  pinMode(echoPinD, INPUT);

  pinMode(trigPinC, OUTPUT);
  pinMode(echoPinC, INPUT);

  miServo.attach(pinServo); //Configuración de servo
  miServo.write(90); //Este es el ángulo en donde empieza el servo

  Serial.begin(115200); //Esta es la velocidad de la comunicación entre la compu y el arduino
}

void loop() {
  distanciaDerecha = medirDistancia(trigPinD, echoPinD); //Acá es una función donde le indicamos que lea la información del ultrasónico derecho 
  distanciaCentro = medirDistancia(trigPinC, echoPinC); //función donde le indicamos que lea la información del ultrasónico centro
  distanciaIzquierda = medirDistancia(trigPinI, echoPinI); //función donde le indicamos que lea la información del ultrasónico izquierdo

  Serial.print("Centro: "); 
  Serial.println(distanciaCentro); //Imprimimos el valor de la distancia centro

  if (distanciaCentro < 20 && distanciaCentro > 5) { //Si la distancia centro es menor que la distancia límite(20) y la distancia centro es mayor que 5 se moverá nuestro servo
    miServo.write(0);
    delay(2000);
    miServo.write(70);
   // delay(5000);
  }

  delay(5); 
}

long medirDistancia(int trigPin, int echoPin) { 
//Esta es la función de medir distancia, aquí se lee toda la información que lleva el ultrasónico, se hacen operaciones matemáticas y luego nos regresa el valor de distancia
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000);

  // Si no hay lectura válida nos regresa un 0
  if (duracion == 0) {
    return 0;
  }

  long distancia = duracion * 0.034 / 2;
  return distancia;
}
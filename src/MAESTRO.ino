#include <Wire.h>
#define SLAVE_ADDRESS 8
//maestro
// SENSOR IZQUIERDO
const int trigL = 8;
const int echoL = 9;

// SENSOR CENTRO
const int trigC = 4;
const int echoC = 5;

// SENSOR DERECHO
const int trigR = 6;
const int echoR = 7;

long izquierda;
long centro;
long derecha;

long medirDistancia(int trigPin, int echoPin){
  // Limpiar trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  // Pulso de 10us
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Timeout de 30 ms
  long duracion = pulseIn(echoPin, HIGH, 30000);

  // Si no hubo lectura
  if (duracion == 0)
  {
    return 999;
  }

  // Convertir a cm
  long distancia = duracion * 0.034 / 2;

  return distancia;
}

void setup()
{
  Serial.begin(9600);

  Wire.begin();

  // IZQUIERDO
  pinMode(trigL, OUTPUT);
  pinMode(echoL, INPUT);

  // CENTRO
  pinMode(trigC, OUTPUT);
  pinMode(echoC, INPUT);

  // DERECHO
  pinMode(trigR, OUTPUT);
  pinMode(echoR, INPUT);

  Serial.println("Sensores listos");
}

void loop()
{
  // Leer uno por uno
  izquierda = medirDistancia(trigL, echoL);
  delay(50);

  centro = medirDistancia(trigC, echoC);
  delay(50);

  derecha = medirDistancia(trigR, echoR);
  delay(50);

  Serial.print("L: ");
  Serial.print(izquierda);

  Serial.print(" cm  C: ");
  Serial.print(centro);

  Serial.print(" cm  R: ");
  Serial.print(derecha);
  Serial.println(" cm");

  char comando = 'S';

  // PRIORIDAD FRENTE
  if (centro < 20)
  {
    if(derecha < izquierda){
      comando = 'A';
    }
    if(izquierda < derecha){
      comando = 'B';
    }
    //comando = 'C';
  }
  else if (izquierda < 20)
  {
    comando = 'L';
  }
  else if (derecha < 20)
  {
    comando = 'R';
  }
  else
  {
    comando = 'S';
  }

  // Enviar por I2C
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(comando);
  Wire.endTransmission();

  Serial.print("Comando: ");
  Serial.println(comando);

  delay(50);
}
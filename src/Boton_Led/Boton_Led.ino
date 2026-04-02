int Boton= 12;
int Led= 5;
int EstadoBoton;

void setup() {
  pinMode(Boton, INPUT);
  pinMode(Led, OUTPUT);

}

void loop() {
  EstadoBoton=digitalRead(Boton); 
  if(EstadoBoton== HIGH){
    digitalWrite(Led, HIGH);
  }
  if(EstadoBoton== LOW){
    digitalWrite(Led, LOW);
  }


}

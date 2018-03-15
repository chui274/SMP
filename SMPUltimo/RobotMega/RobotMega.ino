

#include <Servo.h>
#include <Timer.h>

#define avanza 1
#define gira45D 2
#define gira45I 3 
#define gira180 4
#define gira90D 5
#define gira90I 6
#define busqueda 7
#define atras 8


//PINES PARA MOTOR
const int dirPin = 12;
const int stepPin = 10;
const int dirPin1 = 13;
const int stepPin1 = 11;

int motorState = LOW;
int motor1State = LOW;

//PINES PARA ULTRASONIDO


const int pinUltrasonidoCentro = 18;
const int pinUltrasonidoIzquierda = 19;
const int pinUltrasonidoDerecha = 20;



//PIN RELE
const int rele = 8;

//PINES PARA CNY70

const int cnyIIzquierda = 21;
const int cnyIAtras = 22;
const int cnyIDerecha = 23;


int direccion = 0;

//PINES PARA BUMPER
const int bumperArriba = 2;
const int bumperAbajo = 3;


//Estados
int estado = 1;
int retroceder();


void setup(void)
{

  Serial.begin(9600);
  //RELE
  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH);



  //BUMPER
  pinMode(bumperArriba, INPUT_PULLUP);
  pinMode(bumperAbajo, INPUT_PULLUP);

  //ULTRASONIDOS
  pinMode(pinUltrasonidoCentro, INPUT);
  pinMode(pinUltrasonidoDerecha, INPUT);
  pinMode(pinUltrasonidoIzquierda, INPUT);

  //CNY70
  pinMode(cnyIIzquierda, INPUT);
  pinMode(cnyIDerecha, INPUT);
  pinMode(cnyIAtras, INPUT);



  pinMode(stepPin1, OUTPUT);

  digitalWrite(dirPin, HIGH);  // Asignamos el valor del
  digitalWrite(dirPin1, LOW); // status a la salida
}


void loop(void)
{

  //Serial.print(estado);
  delay(2500);

  while(1){
  switch (estado) {

    case 1:
      Serial.print("Avanza\n");
      estado = avanzar();
      //Serial.print(estado);

      break;
    case 2:
      Serial.print("Gira45I\n");
      estado = giraI(200); //45 grados
      //Serial.print(estado);

      break;
    case 3:
      Serial.print("Gira45D\n");
      estado = giraD(200); //45 grados
      //Serial.print(estado);

      break;
    case 4:
      Serial.print("Gira180\n");
      
      estado = gira_180();
      //Serial.print(estado);

      break;
    case 5:
      Serial.print("Gira90D\n");
      estado = giraDInt(350); //90 grados
     
      //Serial.print(estado);

      break;
    case 6:
      Serial.print("Gira90I\n");
      estado = giraIInt(350); //90 grados
      
      //Serial.print(estado);

      break;
    case 7:
      Serial.print("Busqueda\n");
      estado = buscar();
      //Serial.print(estado);

      break;
    case 8:
      Serial.print("Atras\n");
      estado = retroceder();

      //Serial.print(estado);

      break;

  }
  }

}

void gira_90() {
  digitalWrite(dirPin, HIGH);  // Asignamos el valor del
  digitalWrite(dirPin1, HIGH); // status a la salida
  for (int i = 0; i < 350; i++) {
    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(3);
  }
}

int gira_180() {

  digitalWrite(dirPin, HIGH);  // Asignamos el valor del
  digitalWrite(dirPin1, HIGH); // status a la salida
  for (int i = 0; i < 680; i++) {

    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(3);
  }
  return 7;
}



int avanzar() { //Caso 1
  digitalWrite(dirPin, HIGH);  // Asignamos el valor del
  digitalWrite(dirPin1, LOW); // status a la salida

  for (int i = 0; i < 200 ; i++) {

    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(1);

    if (digitalRead(cnyIIzquierda)) {
      return gira90D;
    }
    else if (digitalRead(cnyIDerecha)) {
      return gira90I;
    }
    else if (digitalRead(bumperArriba) == LOW) {
      i = i-1; // SIGUE EN LA FUNCIÓN
    }
    else if (digitalRead(bumperAbajo) == LOW) {
      return atras;
    }
    else if (digitalRead(pinUltrasonidoCentro) == HIGH ) {
      i = i-1; // SIGUE EN LA FUNCIÓN
    }
    else if (digitalRead(pinUltrasonidoDerecha) == HIGH ) {
      return gira45D;
    }
    else if (digitalRead(pinUltrasonidoIzquierda) == HIGH ) {
      return gira45I;
    }


  }

  return busqueda;

}

// Cuando el pin ultrasonido derecho esté activado
int giraD(int pasos) { //Caso 2 
  digitalWrite(dirPin, HIGH);  // Asignamos el valor del
  digitalWrite(dirPin1, HIGH); // status a la salida

  for (int i = 0; i < pasos ; i++) {

    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(2);
    
    if (digitalRead(cnyIDerecha)) {
      return gira90I;
    }
    else if (digitalRead(cnyIIzquierda)){
      return gira90D;
    }
    
//    else if (digitalRead(pinUltrasonidoCentro) == HIGH) {
//      return avanza;
//    }

    else if (digitalRead(bumperArriba) == LOW) {
      return avanza;
    }
    else if (digitalRead(bumperAbajo) == LOW) {
      return atras;
    }

  }
  return busqueda;

}

// Cuando el pin ultrasonido izquierdo esté activado
int giraI(int pasos) { //Caso 3
  digitalWrite(dirPin, LOW);  // Asignamos el valor del
  digitalWrite(dirPin1, LOW); // status a la salida

  for (int i = 0; i < pasos ; i++) {

    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(2);

    
    if (digitalRead(cnyIIzquierda)) {
      return gira90D; 
    }
    else if(digitalRead(cnyIDerecha)){
      return gira90I;
    }
    
//    else if (digitalRead(pinUltrasonidoCentro) == HIGH) {
//      return 1;
//    }

    if (digitalRead(bumperArriba) == LOW) {
      return avanza;
    }
    else if (digitalRead(bumperAbajo) == LOW) {
      return atras;
    }
  }
  return busqueda;

}

//En caso que el CNY70 IZQUIERDO esté viendo NEGRO
int giraDInt(int pasos) { //caso 5
  
  digitalWrite(dirPin, LOW);  // Asignamos el valor del
  digitalWrite(dirPin1, HIGH); // status a la salida
  //Retrocede 150 pasos antes de girar
  for (int i = 0; i < 300 ; i++) {

    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(2);

    if(digitalRead(cnyIAtras)){
      i=300;
      }
  }
  
  digitalWrite(dirPin, LOW);  // Asignamos el valor del
  digitalWrite(dirPin1, LOW); // status a la salida

  for (int i = 0; i < pasos  ; i++) {


    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(3);

    if (digitalRead(bumperArriba) == LOW) {
      return avanza; 
    }
    else if (digitalRead(bumperAbajo) == LOW) {
      return atras; 
    }
    else if (digitalRead(pinUltrasonidoDerecha) == HIGH ) {
      return gira45D;
    }
    else if (digitalRead(pinUltrasonidoIzquierda) == HIGH){
      return gira45I;
    }
    //PUEDE QUE TENGAMOS QUE COMPROBAR LOS CNY TAMBIÉN AQUÍ, MIRAR SI ACASO


  }

  return busqueda;

}

//En caso que el CNY70 DERECHO esté viendo NEGRO
int giraIInt(int pasos) { //caso 6
  
  digitalWrite(dirPin, LOW);  // Asignamos el valor del
  digitalWrite(dirPin1, HIGH); // status a la salida
  
  //Retrocede 150 pasos antes de girar
  for (int i = 0; i < 300 ; i++) {

    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(2);

    if(digitalRead(cnyIAtras)){
      i=300;
      }
  }
   
  digitalWrite(dirPin, HIGH);  // Asignamos el valor del
  digitalWrite(dirPin1, HIGH); // status a la salida

  for (int i = 0; i < pasos  ; i++) {


    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(3);

    if (digitalRead(bumperArriba) == LOW) {
      return avanza; // Avanza
    }
    else if (digitalRead(bumperAbajo) == LOW) {
      return atras; // Atras
    }
    else if (digitalRead(pinUltrasonidoIzquierda) == HIGH ) {
      return gira45I; // GiraI
    }
    else if (digitalRead(pinUltrasonidoDerecha) == HIGH ) {
      return gira45D;
    }
  //A LO MEJOR TENEMOS QUE COMPROBAR CNY TAMBIÉN
  }

  return busqueda;

}

//GIRA A LA IZQUIERDA MIENTRAS NO DETECTE ALGO
int buscar() { //Caso 7
  
  digitalWrite(dirPin, HIGH);  // Asignamos el valor del
  digitalWrite(dirPin1, HIGH); // status a la salida
  for (int i = 0; i < 1400; i++) {

    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(5);

    if (digitalRead(bumperArriba) == LOW) {
      return avanza;
    }
    else if (digitalRead(bumperAbajo) == LOW) {
      return atras;
    }

    if (digitalRead(pinUltrasonidoIzquierda) == HIGH ) {
      return gira45I;
    }
    else if (digitalRead(pinUltrasonidoDerecha) == HIGH ) {
      return gira45D;
    }
    else if (digitalRead(pinUltrasonidoCentro) == HIGH ) {
      return avanza;
      }


  }
  return busqueda;
}


int retroceder() { //Caso 8
  digitalWrite(dirPin, LOW);  // Asignamos el valor del
  digitalWrite(dirPin1, HIGH); // status a la salida

  for (int i = 0; i < 200 ; i++) {

    motorState = !motorState ;
    motor1State = !motor1State;
    digitalWrite(stepPin, motorState);
    digitalWrite(stepPin1, motor1State);
    delay(1);

    if (digitalRead(cnyIAtras)) {
      digitalWrite(dirPin, HIGH);  // Asignamos el valor del
      digitalWrite(dirPin1, LOW); // status a la salida

      for (int j = 0; j < 50; j++) {
        motorState = !motorState ;
        motor1State = !motor1State;
        digitalWrite(stepPin, motorState);
        digitalWrite(stepPin1, motor1State);
        delay(1);
      }
      return avanza;

    }
    else if (digitalRead(bumperArriba) == LOW) {
      return avanza;
    }
    else if (digitalRead(bumperAbajo) == LOW) {
      return atras;
    }

  }

  return busqueda;

}


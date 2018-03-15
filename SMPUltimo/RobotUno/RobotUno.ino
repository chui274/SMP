#include <Ultrasonic.h>



//PINES PARA ULTRASONIDO
const int pinUltrasonidoCentro = 10;
const int pinUltrasonidoIzquierda = 9;
const int pinUltrasonidoDerecha = 8;
//Centro
const int echoC = 6;
const int trigC = 7;
//Izquierda
const int echoI = 5;
const int trigI = 4;
//Derecha
const int echoD = 3;
const int trigD = 2;


float distanciaC = 0;
float distanciaI = 0;
float distanciaD = 0;
float distanciaComprobadaCentro =0.0;
float distanciaComprobadaIzquierda =0.0;
float distanciaComprobadaDerecha =0.0;

Ultrasonic ultrasonicC(trigC, echoC);
Ultrasonic ultrasonicD(trigD, echoD);
Ultrasonic ultrasonicI(trigI, echoI);

//PINES PARA CNY70
const int cnyIIzquierda = 0;
const int cnyIAtras = 1;
const int cnyIDerecha = 2;
const int cnyOIzquierda = 11;
const int cnyOAtras = 12;
const int cnyODerecha = 13;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //UltrasonidoCentro
  pinMode(echoC, INPUT); 
  pinMode(trigC, OUTPUT);
  pinMode(pinUltrasonidoCentro, OUTPUT);

    //UltrasonidoDerecha
  pinMode(echoD, INPUT); 
  pinMode(trigD, OUTPUT);
  pinMode(pinUltrasonidoDerecha, OUTPUT);

    //UltrasonidoIzquierda
  pinMode(echoI, INPUT); 
  pinMode(trigI, OUTPUT);
  pinMode(pinUltrasonidoIzquierda, OUTPUT);
  
  
  //CNY70
      /* pinMode(cnyI1,INPUT);
       pinMode(cnyI2,INPUT);
       pinMode(cnyI3,INPUT);*/
       
       pinMode(cnyOIzquierda,OUTPUT); //Pin de datos para mantar la interrupción a arduino Mega
       pinMode(cnyOAtras,OUTPUT); //Pin de datos para mantar la interrupción a arduino Mega
       pinMode(cnyODerecha,OUTPUT); //Pin de datos para mantar la interrupción a arduino Mega
       digitalWrite(cnyOAtras,LOW);

  
}

float comprobacionDistanciaCentro() {
  distanciaC = ultrasonicC.Ranging(CM);
  return distanciaC;
}
float comprobacionDistanciaIzquierda() {
  distanciaI = ultrasonicI.Ranging(CM);
  return distanciaI;
}
float comprobacionDistanciaDerecha() {
  distanciaD = ultrasonicD.Ranging(CM);
  return distanciaD;
}
void loop() {

  
  distanciaComprobadaCentro = comprobacionDistanciaCentro();
  distanciaComprobadaDerecha =  comprobacionDistanciaDerecha();
  distanciaComprobadaIzquierda = comprobacionDistanciaIzquierda();
      
      
      
        
       //IZQUIERDA CNY
        if ( analogRead(cnyIIzquierda) < 50){
          digitalWrite(cnyOIzquierda,HIGH);
          delay(10);

        }else{
          digitalWrite(cnyOIzquierda,LOW);
          delay(10);
        }
        //Valor analógico a pasar
        
        //Serial.println(analogRead(cnyIIzquierda));
        
  //ABAJO CNY
  if ( analogRead(cnyIAtras) < 130){
          digitalWrite(cnyOAtras,HIGH);
          delay(10);

        }else{
          digitalWrite(cnyOAtras,LOW);
          delay(10);
         // Serial.print("B\n");
        }
        //Valor analógico a pasar
       // Serial.println(analogRead(cnyIAtras));

  //DERECHA CNY
        
  if ( analogRead(cnyIDerecha) < 50){
          digitalWrite(cnyODerecha,HIGH);
          delay(10);

        }else{
          digitalWrite(cnyODerecha,LOW);
          delay(10);
        }
        //Valor analógico a pasar
        //Serial.println(analogRead(cnyIDerecha));


 //Comprobacion de distanciasCentro
    if(distanciaComprobadaCentro < 45.0 ){
      digitalWrite(pinUltrasonidoCentro, HIGH);
      Serial.print("Centro");
      Serial.println(distanciaComprobadaCentro);
      //Serial.print("\n");
      
      delay(10);
    }
    else{
      digitalWrite(pinUltrasonidoCentro, LOW);
      //Serial.print(distanciaComprobada);
      //Serial.print("\n");
      //Serial.print("Es mayor que 30\n");
      delay(10);
    }
    
    //Comprobacion de distanciasIzquierda
     if(distanciaComprobadaIzquierda < 45.0 ){
      
      
      delay(10);
      distanciaComprobadaIzquierda = comprobacionDistanciaIzquierda();
      if(distanciaComprobadaIzquierda<45.0){
        digitalWrite(pinUltrasonidoIzquierda, HIGH);
        Serial.print("Izquierda");
      Serial.println(distanciaComprobadaIzquierda);
      }
      delay(10);
    }
    else{
      digitalWrite(pinUltrasonidoIzquierda, LOW);
      
      delay(10);
    }
       //Comprobacion de distanciasDerecha
        if(distanciaComprobadaDerecha < 45.0){
          delay(1);
          distanciaComprobadaDerecha =  comprobacionDistanciaDerecha();
          if(distanciaComprobadaDerecha < 45.0){
            digitalWrite(pinUltrasonidoDerecha, HIGH);
                    Serial.print("Derecha");
      Serial.println(distanciaComprobadaDerecha);
          }
      
      delay(10);
    }
    else{
      digitalWrite(pinUltrasonidoDerecha, LOW);
      
      delay(10);
    }
    
  
  

  
  
}


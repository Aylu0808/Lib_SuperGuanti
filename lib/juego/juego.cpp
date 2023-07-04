#include "juego.h"

void apagarLeds(){
  digitalWrite(pinLatch, LOW);              
  shiftOut(dataPin, clockPin, MSBFIRST, 0); 
  digitalWrite(pinLatch, HIGH);
}

void juego(){
/* En esta funcion se cambia el led que esta encendido, con la condicion de que no se prenda dos veces el mismo
  * Esta funcion es llamada cuando se detecta como valido un viaje  
  * Luego de encender el led se va al estadoPrograma 2 donde se reciben instrucciones para la grua
  */
  while(aleatorio == numAnterior){
    aleatorio = random(0, 5);
  }
  
  switch (aleatorio)
  {
    case 0:
      digitalWrite(pinLatch, LOW);              
      shiftOut(dataPin, clockPin, MSBFIRST, 1); 
      digitalWrite(pinLatch, HIGH);
      numAnterior = 0;
      estadoPrograma = 2;
    break;
    case 1:
      digitalWrite(pinLatch, LOW);              
      shiftOut(dataPin, clockPin, MSBFIRST, 2); 
      digitalWrite(pinLatch, HIGH);
      numAnterior = 1;
      estadoPrograma = 2;
    break;
    case 2:
      digitalWrite(pinLatch, LOW);              
      shiftOut(dataPin, clockPin, MSBFIRST, 4); 
      digitalWrite(pinLatch, HIGH);
      numAnterior = 2;
      estadoPrograma = 2;
    break;
    case 3:
      digitalWrite(pinLatch, LOW);              
      shiftOut(dataPin, clockPin, MSBFIRST, 8);
      digitalWrite(pinLatch, HIGH);
      numAnterior = 3;
      estadoPrograma = 2;
    break;
    case 4:
      digitalWrite(pinLatch, LOW);               
      shiftOut(dataPin, clockPin, MSBFIRST, 16); 
      digitalWrite(pinLatch, HIGH);
      numAnterior = 4;
      estadoPrograma = 2;
    break;
  }
}
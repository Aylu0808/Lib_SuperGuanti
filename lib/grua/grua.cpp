#include "grua.h"

void grua(){
  
  estadoBluetooth = Serial.read(); 

  ///SERVO 1 -- DERECHA IZQUIERDA -- 9///
  if(estadoBluetooth == '1'){
    grados1 = grados1 + 3;
    if(grados1 >= 180){
      grados1 = 180;
    }
    miservo_1.write(grados1); //,0 para velocidad 
  }

  if(estadoBluetooth == '3'){
    grados1 = grados1 - 3;
    if(grados1 <= 0){
      grados1 = 0;
    }
    miservo_1.write(grados1);
  }

  ///SERVO 2 -- ADELANTE ATRAS -- 6///
  if(estadoBluetooth == '5'){
    grados2 = grados2 + 3;
    if(grados2 >= 180){
      grados2 = 180;
    }
    miservo_2.write(grados2);
  }

  if(estadoBluetooth == '7'){
    grados2 = grados2 - 4;
    if(grados2 <= 0){
      grados2 = 0;
    }
    miservo_2.write(grados2);
  }
  ///SERVO 3 -- ABAJO -- 11///
  if(estadoBluetooth == '9'){    
    grados3 = grados3 - 3;        
    if(grados3<=0){
      grados3 = 90;
    }
    miservo_3.write(grados3);
  }  
}
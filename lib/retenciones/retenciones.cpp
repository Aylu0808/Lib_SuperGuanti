void retencionInicio(){

  switch(estadoRetencionInicio){
    case 1:
      flagPulsoInicio = false;

      if(digitalRead(inicio) == LOW)
        estadoRetencionInicio = 1;

      if(digitalRead(inicio) == HIGH){
        tInicio = 0;
        estadoRetencionInicio = 2;
      }
    break;
    case 2:
      if(tInicio < 7)
        estadoRetencionInicio = 2;
      if(tInicio >= 7)
        estadoRetencionInicio = 3;
    break;
    case 3: 
      if(digitalRead(inicio) == HIGH){
        flagPulsoInicio = true;
        estadoRetencionInicio = 1;
      }
      else{
        flagPulsoInicio = false;
        estadoRetencionInicio = 1;
      }
    break;
  }
}

void retencionIncremento(){
  
  switch(estadoRetencionIncremento){
        case 1:
          flagPulsoIncremento = false;

          if(digitalRead(incremento) == LOW)
            estadoRetencionIncremento = 1;

          if(digitalRead(incremento) == HIGH){
            tIncremento = 0;
            estadoRetencionIncremento = 2;
          }
        break;
        case 2:
          if(tIncremento < 20)
            estadoRetencionIncremento = 2;
          if(tIncremento >= 20)
            estadoRetencionIncremento = 3;
        break;
        case 3: 
          if(digitalRead(incremento) == HIGH){
            flagPulsoIncremento  = true;
            estadoRetencionIncremento  = 1;
          }
          else{
            flagPulsoIncremento = false;
            estadoRetencionIncremento = 1;
          }
        break;
      }
}
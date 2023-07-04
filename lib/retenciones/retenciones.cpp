#define FALSE 0
#define TRUE 1

#define incremento 13 //10
#define inicio A0 //12

int estadoPrograma = 1;
int estadoRetencionIncremento = 1;
int estadoRetencionInicio = 1;
int estadoLcd = 0;
int estadoBluetooth = 0;

int tInicio = 0;
int tIncremento = 0;

bool flagPulsoIncremento = FALSE;
bool flagPulsoInicio = FALSE;
bool flagHabilitacionInicio = FALSE;

void retencionInicio(){

  switch(estadoRetencionInicio){
    case 1:
      flagPulsoInicio = FALSE;

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
        flagPulsoInicio = TRUE;
        estadoRetencionInicio = 1;
      }
      else{
        flagPulsoInicio = FALSE;
        estadoRetencionInicio = 1;
      }
    break;
  }
}

void retencionIncremento(){
  
  switch(estadoRetencionIncremento){
        case 1:
          flagPulsoIncremento = FALSE;

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
            flagPulsoIncremento  = TRUE;
            estadoRetencionIncremento  = 1;
          }
          else{
            flagPulsoIncremento = FALSE;
            estadoRetencionIncremento = 1;
          }
        break;
      }
}
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <TimerOne.h>

/* 
  Hay que volver a declarar las variables dentro de cada libreria??

  Si las librerias se usan en en mis librerias, tambien las tengo que declarar aca???
*/

#define FALSE 0
#define TRUE 1

#define incremento 13 //10
#define inicio A0 //12

#define infra1 11 //4
#define infra2 12 //A3
#define infra3 A1 //A2
#define infra4 A2 //A1
#define infra5 A3 //A0
// 74hc595
#define pinLatch 9 //7  
#define clockPin 10 //8 
#define dataPin 8 //5  

Servo miservo_1, miservo_2, miservo_3;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

int tIncremento = 0;
int tInicio = 0;
int tInfras = 0;
int taux = 0;
int tauxmili = 0;
int tlcd = 0;
int tmin = 0;
int tseg = 0;
int thora = 0;

int estadoPrograma = 1;
int estadoRetencionIncremento = 1;
int estadoRetencionInicio = 1;
int estadoLcd = 0;
int estadoBluetooth = 0;

int numViajes = 0;
int contadorViajes = 0;
int aleatorio = 0;
int numAnterior = 0;

int menique = 0;
int indice = 0;
int anular = 0;
int mayor = 0;
int pulgar = 0;

int grados1 = 0;
int grados2 = 0;
int grados3 = 60;

bool flagPulsoIncremento = FALSE;
bool flagPulsoInicio = FALSE;
bool flagHabilitacionInicio = FALSE;

void actualizarLcd();
void juego();
void grua();
void retencionInicio();
void apagarLeds();

void setup(){
  //Inicializacion del Timer2
  cli(); 
  TCCR2A = 0; 
  TCCR2B = 0; 
  TCNT2 = 0;  

  OCR2A = 255; 
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (0b00000111); //1024 (preescala)
  TIMSK2 |= (1 << OCIE2A);
  sei(); 

  Serial.begin(57600); 

  miservo_1.attach(3, 350, 2900); //servo base, derecha-izquierda (9)
  miservo_1.write(grados1); 

  miservo_2.attach(5, 1000, 2000); //servo de la derecha, adelante-atras (6)
  miservo_2.write(grados2); 

  miservo_3.attach(6, 1000, 2000); //servo de la izqueirda, abajo (11)
  miservo_3.write(grados3);
  delay(500);

  apagarLeds();

  lcd.init();
  lcd.backlight();
  //Mensaje de bienvenida
  lcd.setCursor(0, 0);
  lcd.print("  Bienvenido a  ");
  lcd.setCursor(0, 1);
  lcd.print("  Super Guanti  ");
  delay(1000);  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Una creacion de:");
  lcd.setCursor(0, 1);
  lcd.print("     M.A.L.     ");
  delay(1000);
  lcd.clear();

  pinMode(incremento, INPUT);
  pinMode(inicio, INPUT);

  pinMode(pinLatch, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

ISR(TIMER2_COMPA_vect){ 
/* Esta funcion se interrumpe cada 32.77us
   La cuenta no es exacta. Salida ejemplo: 4:30(salida arduino) 4:26(cronometro)
*/
  tauxmili++;
  if (tauxmili >= 30) {
    tIncremento++;
    tInicio++;
    taux++;
    
    if(taux >= 60){
      tlcd--;
      taux = 0;
      if(estadoLcd == 2){
        tseg++;
        if(tseg >= 60){
          tmin++;
          tseg = 0;
          if(tmin >= 60){
            thora++;
            tmin = 0;
          }
        }
      }
    }
  } 
}

void loop(){
  
  actualizarLcd();
  
  switch(estadoPrograma){
    case 1:
    /* En este caso se hace la eleccion de la cantidad de viajes a realizar y se da inicio al juego
    * Las MEF son para la retencion de los pulsadores de incremento de viajes y de inicio 
    */
      apagarLeds();

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
      retencionInicio(); //la mef para la retencion del pulsador inicio se llama varias veces en el programa
      
      /*Si el pulsador verdaderamente esta presionado, se incrementa una vez la variable
        Se puede dar inicio al juego luego de haber seleccionado minimo un viaje, entonces se habilita el boton inicio
      */
      if(flagPulsoIncremento == TRUE){
        numViajes++;
        flagHabilitacionInicio = TRUE;
      }
      if(estadoLcd == 2){ //condicion para salir de este estado, le puse esta para no repetir la condicion del estado del lcd
        juego(); //llamo para encender el primer led
        estadoPrograma = 2;
        tmin = 0;
        tseg = 0;
        thora = 0;
      }
    break;
    case 2:
    /* Si se reciben datos por bluetooth se llama a la grua
      * Al detectar que se pulso un infra se avanza al siguiente estado
    */
      if(Serial.available()){
        grua();
      }

      if(digitalRead(infra1) == LOW || digitalRead(infra2) == LOW || digitalRead(infra3) == LOW || digitalRead(infra4) == LOW || digitalRead(infra5) == LOW){
        estadoPrograma = 3;
      }
    break;
    case 3:
    /* Cuando el infra deja de detectar se cuenta como un viaje
    *  Mientras el infra este activado se llama a la grua para poder levantar el bloque
    *  Mientras el lcd diga A JUGAR se llama a la funcion juego para prender el sig led
    */
      
      if(digitalRead(infra1) == LOW || digitalRead(infra2) == LOW || digitalRead(infra3) == LOW || digitalRead(infra4) == LOW || digitalRead(infra5) == LOW){
        estadoPrograma = 3;
        grua();
      }
      if(digitalRead(infra1) == HIGH && digitalRead(infra2) == HIGH && digitalRead(infra3) == HIGH && digitalRead(infra4) == HIGH && digitalRead(infra5) == HIGH){
        contadorViajes++;
        if(estadoLcd == 2){
          juego();
        }
        estadoPrograma = 2;
      }
    break;
    case 4:
    /*En este estado se entra desde la condicion anterior y desde las condiciones del lcd al llegar al ultimo caso
      Se reinician todas las varibles definidas en el inicio   
      La variable flagHabilitacionInicio se desactiva para volver a ingresar la cantidad de viajes que se quieren
    */
      tmin = 0;
      tseg = 0;
      thora = 0;

      numViajes = 0;
      contadorViajes = 0;
      aleatorio = 0;
      numAnterior = 0;

      estadoLcd = 0;
      flagHabilitacionInicio = FALSE;
      estadoPrograma = 1;
    break;
  }
}




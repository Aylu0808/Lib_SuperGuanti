#include "lcd.h"
#include <juego.h>
#include <retenciones.h>

/*Aca tengo que volver a declarar la libreria LiquidCrystal??

Tengo que volver a declarar todas las variables?? */


void actualizarLcd(){
  /* En esta MEF estan agrupadas todas las salidas en pantalla con sus respectivas condiciones  
   * para cambiar de estado
  */
  switch (estadoLcd)
  {
    case 0:
      lcd.setCursor(0,0);
      lcd.print("Cant de viajes: ");
      lcd.setCursor(0,1);
      lcd.print(numViajes);

      if(flagPulsoInicio == true && flagHabilitacionInicio == true){ //se cambia de estado si ya hay viajes seleccionados
        tlcd = 5;
        estadoLcd = 1;
      }
      else{
        estadoLcd = 0;
      }
    break;
    case 1:
      lcd.setCursor(0,0);
      lcd.print("El juego inicia");
      lcd.setCursor(0, 1);
      lcd.print("     en: ");
      lcd.print(tlcd);

      if(tlcd > 0)
        estadoLcd = 1;
      else{
        lcd.clear();
        estadoLcd = 2;
      }
    break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("    A JUGAR!    ");
      lcd.setCursor(4, 1);
      lcd.print(thora);
      lcd.print(":");
      lcd.print(tmin);
      lcd.print(":");
      lcd.print(tseg);

      if(contadorViajes != numViajes)
        estadoLcd = 2;
      else{
        tlcd = 5;//este tiempo es corto porque se estan haciendo pruebas, despues se puede modificar
        lcd.clear();
        estadoLcd = 3;
      }
        
    break;
    case 3:
      apagarLeds();

      lcd.setCursor(0, 0);
      lcd.print("  Felicidades!  ");
      lcd.setCursor(4, 1);
      lcd.print(thora);
      lcd.print(":");
      lcd.print(tmin);
      lcd.print(":");
      lcd.print(tseg);

      if(tlcd <= 0){
        tlcd = 5;
        lcd.clear();
        estadoLcd = 4;
      }
    break;
    case 4:
    /*Por ahora aca se muestra todo en cero, falta desarrollar la suma de estas variables*/
      lcd.setCursor(0,0);
      lcd.print("1:");
      lcd.print(menique);
      lcd.print(" 2:");
      lcd.print(indice);
      lcd.print(" 3:");
      lcd.print(pulgar);
      lcd.setCursor(0, 1);
      lcd.print("4:");
      lcd.print(anular);
      lcd.print(" 5:");
      lcd.print(mayor);

      if(tlcd <= 0){
        tlcd = 10;
        lcd.clear();
        estadoLcd = 5;
      }
    break;
    case 5:
      lcd.setCursor(0,0);
      lcd.print(" Para reiniciar ");
      lcd.setCursor(0,1);
      lcd.print("presionar inicio");

      retencionInicio(); 
      if(flagPulsoInicio == true){
        lcd.clear();
        estadoPrograma = 4;
      }
    break;
  }
}
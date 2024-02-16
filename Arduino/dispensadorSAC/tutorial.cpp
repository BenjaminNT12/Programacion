#include "tutorial.h"  
#include <LiquidCrystal_I2C.h> // Biblioteca para controlar la pantalla LCD

const char message1[] PROGMEM = "Bienvenidos";
const char message2[] PROGMEM = "1: Deposite sus monedas. ";
const char message3[] PROGMEM = "2: Coloque su envase . ";
const char message4[] PROGMEM = "3: Presione el boton . ";

const char* const tutorialMessages[] PROGMEM = {
  message1,
  message2,
  message3,
  message4
};

extern LiquidCrystal_I2C lcd;

void mostrarTutorialLCD() {
  static unsigned long lastUpdate = 0;
  static int i = 1;
  static int j = 0;
  char buffer[100];

  if (millis() - lastUpdate >= 100) { // Si han pasado 3 segundos
    lastUpdate = millis(); // Actualiza el tiempo de la última actualización

    if (i < sizeof(tutorialMessages) / sizeof(tutorialMessages[0])) {
      lcd.setCursor(0, i);
      lcd.print("                "); // Limpia la línea

      strcpy_P(buffer, (char*)pgm_read_word(&(tutorialMessages[i])));

      // Si el mensaje es más largo de 20 caracteres, se desplaza de derecha a izquierda
      if (strlen(buffer) > 20) {
        if (j < strlen(buffer)) {
          lcd.setCursor(0, i);
          lcd.print(String(buffer).substring(j, j + 20));
          j++;
        } else {
          lcd.setCursor(0, i);
          lcd.print(String(buffer).substring(0, 20)); // Muestra la primera parte del texto
          j = 0;
          i++;
        }
      } else {
        lcd.setCursor((20 - strlen(buffer)) / 2, i);
        lcd.print(buffer);
        i++;
      }
    }
    if(i == sizeof(tutorialMessages) / sizeof(tutorialMessages[0])){
      i = 1;
    }
  }
}
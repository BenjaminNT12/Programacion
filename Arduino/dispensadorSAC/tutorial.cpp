#include "tutorial.h"  
#include <LCD_I2C.h> // Biblioteca para controlar la pantalla LCD

const char message1[] PROGMEM = "Como usar el dispensador?";
const char message2[] PROGMEM = "1: Deposite sus monedas en la ranura. ";
const char message3[] PROGMEM = "2: Coloque su envase bajo el producto seleccionado. ";
const char message4[] PROGMEM = "3: Presione el boton del producto. ";

const char* const tutorialMessages[] PROGMEM = {
  message1,
  message2,
  message3,
  message4
};

unsigned int speedTransition = 300;

extern LCD_I2C lcd;

void mostrarTutorialLCD() {
  // unsigned long startMillis = millis();  // Guarda el tiempo de inicio

  static unsigned long lastUpdate = 0;
  static int i = 0;
  static int j = 0;
  char buffer[55];

  if (millis() - lastUpdate >= (unsigned long)speedTransition) { // Si han pasado 3 segundos
    lastUpdate = millis(); // Actualiza el tiempo de la última actualización
    if(i == 0) lcd.clear();

    if (i < sizeof(tutorialMessages) / sizeof(tutorialMessages[0])) {
      lcd.setCursor(0, i);
      lcd.print("                "); // Limpia la línea

      strcpy_P(buffer, (char*)pgm_read_word(&(tutorialMessages[i])));
      // handleCoin();
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
      i = 0;
    }
  }

  // unsigned long duration = millis() - startMillis;  // Calcula la duración
  // Serial.print("mostrarTutorialLCD took: ");
  // Serial.print(duration);
  // Serial.println(" ms");
}
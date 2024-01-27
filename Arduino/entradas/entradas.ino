#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección I2C del display LCD (puede variar según el módulo)
#define LCD_ADDRESS 0x27
#include <ShiftIn.h>
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2); // Crear objeto del LCD

ShiftIn<2> shift;

void setup() {
  Wire.begin();        // Inicializar la comunicación I2C
  lcd.backlight();
  lcd.begin(20, 4);    // Inicializar el LCD
  Serial.begin(9600);
  shift.begin(10, 9, 11, 12);
  Serial.print("Hola \n"); // get state of button i

  lcd.print("Presiona un");
  lcd.setCursor(0, 1);
  lcd.print("boton...");
}


int estadoEntrada(int id, int estado) { // almacenal el estado del sensor en la variable StateSLAVE[x].val
    static unsigned char retorno = 0;

    for (unsigned char i = 0; i < 8; i++) {
      if (estado == 1){
          retorno |= (0x01 << id);
      }else {
          retorno &= (0xFF^(0x01 << id));
      }
    }
    return retorno;
}


int getState(int pinNumber) {
  // int estadosActual = 0;
  static int estados = 0;

  if (shift.update()) { // Si hay un cambio en las entradas
    for (int i = 0; i < shift.getDataWidth(); i++){
      estados = estadoEntrada(i, shift.state(i));
    }
  }
  return (0x01&(estados>>pinNumber));
}

void loop() {
  if (getState(0) == 1) {
    Serial.print("pulsado 1 on \n"); // get state of button i
    lcd.clear();
    lcd.print("Boton: ");
    lcd.print(0);
    delay(500);
  }
  if (getState(1) == 1) {
    // Serial.print(getState(1));
    Serial.print("pulsado 2 error \n"); // get state of button i
    lcd.clear();
    lcd.print("Boton: ");
    lcd.print(1);
    delay(100);
  }
  if (getState(2) == 1) {
    Serial.print("pulsado 3 error \n"); // get state of button i
    lcd.clear();
    lcd.print("Boton: ");
    lcd.print(2);
    delay(100);
  }
  if (getState(3) == 1) {
    Serial.print("pulsado 4 error \n"); // get state of button i
    lcd.clear();
    lcd.print("Boton: ");
    lcd.print(3);
    delay(100);
  }
  if (getState(4) == 1) {
    Serial.print("pulsado 5 error \n"); // get state of button i
    lcd.clear();
    lcd.print("Boton: ");
    lcd.print(4);
    delay(100);
  }
  if (getState(5) == 1) {
    Serial.print("pulsado 6 error \n"); // get state of button i
    lcd.clear();
    lcd.print("Boton: ");
    lcd.print(5);
    delay(100);
  }
  if (getState(6) == 1) {
    Serial.print("pulsado 7 error \n"); // get state of button i
    lcd.clear();
    lcd.print("Boton: ");
    lcd.print(6);
    delay(100);
  }
  if (getState(7) == 1){
    Serial.print("pulsado 8 error \n"); // get state of button i
    lcd.clear();
    lcd.print("Boton: ");
    lcd.print(7);
    delay(100);
  }
}

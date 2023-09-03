#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección I2C del display LCD (puede variar según el módulo)
#define LCD_ADDRESS 0x27

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2); // Crear objeto del LCD

// Pines de los botones
const int botonPin1 = 3;
const int botonPin2 = 2;
const int botonPin3 = 4;
const int botonPin4 = 5;
const int botonPin5 = 7;

void setup() {
  Wire.begin();        // Inicializar la comunicación I2C
  lcd.backlight();
  lcd.begin(16, 2);    // Inicializar el LCD

  // Configurar los pines de los botones como entradas
  pinMode(botonPin1, INPUT_PULLUP);
  pinMode(botonPin2, INPUT_PULLUP);
  pinMode(botonPin3, INPUT_PULLUP);
  pinMode(botonPin4, INPUT_PULLUP);
  pinMode(botonPin5, INPUT_PULLUP);

  lcd.print("Presiona un");
  lcd.setCursor(0, 1);
  lcd.print("boton...");
}

void loop() {
  if (digitalRead(botonPin1) == LOW) {
    lcd.clear();
    lcd.print("Boton Arriba");
    delay(50);
  }
  else if (digitalRead(botonPin2) == LOW) {
    lcd.clear();
    lcd.print("Boton Abajo");
    delay(50);
  }
  else if (digitalRead(botonPin3) == LOW) {
    lcd.clear();
    lcd.print("Boton Menu");
    delay(50);
  }
  else if (digitalRead(botonPin4) == LOW) {
    lcd.clear();
    lcd.print("Boton Select");
    delay(50);
  }
  else if (digitalRead(botonPin5) == LOW) {
    lcd.clear();
    lcd.print("Boton Activacion");
    delay(50);
  }
}

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ShiftIn.h>

#define LCD_ADDRESS 0x27
#define dataPin 13
#define latchPin A0
#define clockPin A1
#define EnterCoin 7
#define outCoin 8
#define hooper 6

byte leds = 0;
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);
ShiftIn<2> shift;

void setup() {
  Wire.begin();
  lcd.backlight();
  lcd.begin(20, 4);
  Serial.begin(9600);
  shift.begin(10, 9, 11, 12);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(outCoin, INPUT);
  pinMode(EnterCoin, INPUT);
  pinMode(hooper, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(clockPin, OUTPUT);
  lcd.print("Presiona un");
  lcd.setCursor(0, 1);
  lcd.print("boton...");
}

void loop() {
//   delay(500);
//   for (int i = 0; i < 8; i++) {
//     digitalWrite(LED_BUILTIN, HIGH);
//     delay(100);
//     digitalWrite(LED_BUILTIN, LOW);
//     delay(100);
//   }
//   for(int i=0; i<8; i++) {
//     setOutput(i, true);
//     delay(100);
//     setOutput(i, false);
//   }
//   digitalWrite(hooper, HIGH);
//   delay(100);
//   digitalWrite(hooper, LOW);
//   delay(100);
  checkButtons();
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void setOutput(int outputNumber, bool status) {
  if (status) {
    bitSet(leds, outputNumber);
  } else {
    bitClear(leds, outputNumber);
  }
  updateShiftRegister();
}

int estadoEntrada(int id, int estado) {
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
  static int estados = 0;
  if (shift.update()) {
    for (int i = 0; i < shift.getDataWidth(); i++){
      estados = estadoEntrada(i, shift.state(i));
    }
  }
  return (0x01&(estados>>pinNumber));
}

void checkButtons() {
  for (int i = 0; i < 8; i++) {
    if (getState(i) == 1) {
      Serial.print("pulsado ");
      Serial.print(i+1);
      Serial.print(" error \n");
      lcd.clear();
      lcd.print("Boton: ");
      lcd.print(i);
      setOutput(i, true);
      delay(100);
    }else{
      setOutput(i, false);
    }
  }
}
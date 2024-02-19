#include <Wire.h> // Biblioteca para la comunicación I2C
#include <LiquidCrystal_I2C.h> // Biblioteca para controlar la pantalla LCD
#include <EEPROM.h> // Biblioteca para acceder a la memoria EEPROM
#include <ShiftIn.h>
#include "game.h" // Biblioteca para el juego del dinosaurio
#include "tutorial.h" // Biblioteca para el tutorial
#include "serve.h" // Biblioteca para el menú
#include "handler.h" // Biblioteca para el manejo de eventos

ShiftIn<2> shift;

extern const int BUTTON_UP_PIN;
extern const int BUTTON_DOWN_PIN;
extern const int BUTTON_SELECT_PIN;
extern const int BUTTON_MENU_PIN;
extern const int COIN_INPUT_PIN;
extern const int BUTTON_PRODUCT1_PIN;
extern const int HOOPER_OUTPUT_PIN;
extern const int HOOPER_PIN; 
extern const int LATCH_PIN;	
extern const int DATA_PIN;	
extern const int CLOCK_PIN;	

extern const int LCD_WIDTH;
extern const int LCD_HEIGHT;
extern const int MAX_MENU_ITEMS;

char message[] = "Dispensador..."; 
int messageLength = sizeof(message) - 1;
unsigned long startTime = millis();

LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);

void setup() {
  Serial.begin(115200); 
  shift.begin(10, 9, 11, 12);
  lcd.init();
  lcd.backlight();

  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_MENU_PIN, INPUT_PULLUP);
  pinMode(COIN_INPUT_PIN, INPUT);
  pinMode(BUTTON_PRODUCT1_PIN, INPUT_PULLUP);
  pinMode(HOOPER_OUTPUT_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(HOOPER_PIN, OUTPUT); 
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);  
  pinMode(CLOCK_PIN, OUTPUT);

  resetOutputs();
  showScrollingMessage(message, messageLength);
  setZeroEeprom(MAX_MENU_ITEMS);
  loadFromEEPROM(MAX_MENU_ITEMS);
  showMenu();
}


void loop() {
  static unsigned long lastPrintedTime = 0;
  unsigned long currentTime = (millis() - startTime) / 1000UL;
  static bool dynoGameShow = false; 
  static bool ledState = false;
  
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);

  handleButtons(); 
  handleTimeEvents(currentTime, lastPrintedTime, startTime);
  lastPrintedTime = currentTime;
}


#include <Wire.h> // Biblioteca para la comunicación I2C
#include <LiquidCrystal_I2C.h> // Biblioteca para controlar la pantalla LCD
#include <EEPROM.h> // Biblioteca para acceder a la memoria EEPROM
#include <ShiftIn.h>
#include "game.h" // Biblioteca para el juego del dinosaurio
#include "tutorial.h" // Biblioteca para el tutorial
#include "serve.h" // Biblioteca para el menú

#define PROD0_BUTTON BUTTON_DOWN_PIN
#define PROD1_BUTTON BUTTON_UP_PIN
#define PROD2_BUTTON BUTTON_MENU_PIN
#define PROD3_BUTTON BUTTON_SELECT_PIN
#define PROD4_BUTTON BUTTON_PRODUCT1_PIN
#define PROD5_BUTTON BUTTON_PRODUCT2_PIN
#define PROD6_BUTTON BUTTON_PRODUCT3_PIN
#define PROD7_BUTTON BUTTON_PRODUCT4_PIN

ShiftIn<2> shift;

// Conexión de la pantalla LCD
extern const int LCD_WIDTH;
extern const int LCD_HEIGHT;
LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);

const int BUTTON_DOWN_PIN = 0;
const int BUTTON_UP_PIN = 1;
const int BUTTON_MENU_PIN = 2;
const int BUTTON_SELECT_PIN = 3;

const int BUTTON_PRODUCT1_PIN = 4;
const int BUTTON_PRODUCT2_PIN = 5;
const int BUTTON_PRODUCT3_PIN = 6;
const int BUTTON_PRODUCT4_PIN = 7;

const int COIN_INPUT_PIN = 7;
const int HOOPER_OUTPUT_PIN = 8;
const int OUTPUT_PIN_0  = 0; 
const int OUTPUT_PIN_1 = 1; 
const int OUTPUT_PIN_2 = 2; 
const int OUTPUT_PIN_3 = 3; 
const int OUTPUT_PIN_4 = 4; 
const int OUTPUT_PIN_5 = 5; 
const int OUTPUT_PIN_6 = 6; 
const int OUTPUT_PIN_7 = 7; 
const int DATA_PIN  = 13;	// Data pin of 74HC595 is connected to Digital pin 13
const int LATCH_PIN = A0;	// Latch pin of 74HC595 is connected to Digital pin A0
const int CLOCK_PIN = A1;	// Clock pin of 74HC595 is connected to Digital pin A1
const int HOOPER_PIN = 38; 

char message[] = "Dispensador..."; // Mensaje de desplazamiento
int messageLength = sizeof(message) - 1; // Longitud del mensaje sin el carácter nulo
const int MAX_MENU_ITEMS = 8; // Número total de elementos del menú

float productQuantity[MAX_MENU_ITEMS] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; // Cantidad de producto a dispensar
float productCost[MAX_MENU_ITEMS] = {10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0}; // Costo del producto
float pumpTime[MAX_MENU_ITEMS] = {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0}; // Tiempo de dispensado del producto

const int PROD_BUTTONS[MAX_MENU_ITEMS] = {PROD0_BUTTON,
                                                 PROD1_BUTTON, 
                                                 PROD2_BUTTON, 
                                                 PROD3_BUTTON, 
                                                 PROD4_BUTTON, 
                                                 PROD5_BUTTON, 
                                                 PROD6_BUTTON, 
                                                 PROD7_BUTTON};

unsigned long startTime = millis(); // Tiempo de inicio de la dispensación

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial a 115200 baudios
  shift.begin(10, 9, 11, 12);
  lcd.init(); // Inicializa la pantalla LCD
  lcd.backlight(); // Enciende la luz de fondo de la pantalla LCD

  pinMode(BUTTON_UP_PIN, INPUT_PULLUP); // Configura el pin del botón de subida como entrada con resistencia pull-up
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP); // Configura el pin del botón de bajada como entrada con resistencia pull-up
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP); // Configura el pin del botón de selección como entrada con resistencia pull-up
  pinMode(BUTTON_MENU_PIN, INPUT_PULLUP); // Configura el pin del botón de menú como entrada con resistencia pull-up
  pinMode(COIN_INPUT_PIN, INPUT); // Configura el pin de inserción de moneda como entrada
  pinMode(BUTTON_PRODUCT1_PIN, INPUT_PULLUP); // Configura el pin del botón del producto 1 como entrada con resistencia pull-up
  pinMode(HOOPER_OUTPUT_PIN, INPUT_PULLUP); // Configura el pin del botón del producto 1 como entrada con resistencia pull-up
  pinMode(LED_BUILTIN, OUTPUT); // Configura el pin del LED incorporado como salida 
  pinMode(HOOPER_PIN, OUTPUT); // Configura el pin del LED como salida
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);  
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  resetOutputs();
  showScrollingMessage(message, messageLength);
  loadFromEEPROM(MAX_MENU_ITEMS);
  showMenu();
}


void loop() {
  static unsigned long lastPrintedTime = 0;
  unsigned long currentTime = (millis() - startTime) / 1000;
  static bool dynoGameShow = false; // Variable booleana estática para indicar si se ha mostrado el juego del dinosaurio

  handleButtons(); // Maneja los botones
  handleTimeEvents(currentTime, lastPrintedTime, startTime);
}


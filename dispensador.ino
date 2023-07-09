#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Conexión de la pantalla LCD
LiquidCrystal_I2C lcd(32, 16, 2);

// Pines para los botones
const int buttonUpPin = 2;
const int buttonDownPin = 3;
const int buttonSelectPin = 4;
const int buttonMenuPin = 5;

// Variables para el menú
int menuIndex = 0; // Índice del elemento del menú actual
const int maxMenuItems = 5; // Número total de elementos del menú

float productQuantity[maxMenuItems] = {0.0}; // Cantidad de producto a dispensar en litros
float productCost[maxMenuItems] = {0.0}; // Costo del producto

// Texto para cada elemento del menú
String menuItems[] = {
  "Shampoo",
  "Suavitel",
  "Pinol",
  "Desengrasante",
  "Fabuloso"
};

// Variables para el desplazamiento del mensaje
char message[] = "Dispensador de productos";
int messageLength = sizeof(message) - 1; // Longitud del mensaje sin el carácter nulo
int scrollPosition = 0; // Posición actual del desplazamiento
unsigned long scrollDelay = 150; // Retardo entre cada paso del desplazamiento

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  pinMode(buttonSelectPin, INPUT_PULLUP);
  pinMode(buttonMenuPin, INPUT_PULLUP);

  // Mostrar el mensaje de desplazamiento
  unsigned long startTime = millis();
  while (millis() - startTime < 300) {
    lcd.clear();
    lcd.setCursor(scrollPosition, 0);
    lcd.print(message);
    delay(scrollDelay);
    scrollPosition++;
    if (scrollPosition > messageLength + 16) {
      scrollPosition = -16;
    }
  }

  showMenu();
}

void loop() {
  if (digitalRead(buttonUpPin) == LOW) {
    menuIndex = (menuIndex - 1 + maxMenuItems) % maxMenuItems;
    showMenu();
    delay(200);
  } else if (digitalRead(buttonDownPin) == LOW) {
    menuIndex = (menuIndex + 1) % maxMenuItems;
    showMenu();
    delay(200);
  } else if (digitalRead(buttonSelectPin) == LOW) {
    showSubMenu();
    delay(200);
    if (digitalRead(buttonMenuPin) == LOW){
      showMenu();
    }
  }
}

void showMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Producto");
  lcd.setCursor(0, 1);
  lcd.print("- ");
  lcd.print(menuItems[menuIndex]);
}

void showSubMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">> ");
  lcd.print(menuItems[menuIndex]);

  lcd.setCursor(0, 1);
  lcd.print("Lt: ");
  lcd.print(productQuantity[menuIndex], 1);

  unsigned long selectButtonStartTime = millis();
  bool selectButtonPressed = false;
  bool saveVal = false;

  if (digitalRead(buttonSelectPin) == LOW) {
    selectButtonPressed = true;
  }

  if (selectButtonPressed && saveVal == false) {
    lcd.setCursor(7, 1);
    lcd.print(" $: ");
    lcd.print(productCost[menuIndex], 1);

    // Lógica para ajustar el costo con los botones "Arriba" y "Abajo"
    while (digitalRead(buttonMenuPin) == HIGH) {
      if (digitalRead(buttonUpPin) == LOW) {
        productCost[menuIndex] += 0.1;
        delay(200);
      } else if (digitalRead(buttonDownPin) == LOW) {
        productCost[menuIndex] -= 0.1;
        delay(200);
      }
      lcd.setCursor(11, 1);
      lcd.print(productCost[menuIndex], 1);
    }
    if (digitalRead(buttonMenuPin) == LOW){
      saveVal = true;
    }
    
  } else if(saveVal == false){
    // Lógica para ajustar la cantidad con los botones "Arriba" y "Abajo"
    while (digitalRead(buttonSelectPin) == HIGH) {
      if (digitalRead(buttonUpPin) == LOW) {
        productQuantity[menuIndex] += 0.1;
        delay(200);
      } else if (digitalRead(buttonDownPin) == LOW) {
        productQuantity[menuIndex] -= 0.1;
        delay(200);
      }
      lcd.setCursor(4, 1);
      lcd.print(productQuantity[menuIndex], 1);
    }
  }
}


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#

// Conexión de la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines para los botones
const int buttonSelectPin = 2;
const int buttonDownPin = 3;
const int buttonUpPin = 4;
const int buttonMenuPin = 5;

// Variables para el menú
int menuIndex = 0; // Índice del elemento del menú actual
const int maxMenuItems = 5; // Número total de elementos del menú

float productQuantity[maxMenuItems] = {0.0}; // Cantidad de producto a dispensar en litros
float productCost[maxMenuItems] = {0.0}; // Costo del producto
// bool saveVal[] = false;

// Texto para cada elemento del menú
String menuItems[] = {
  "Shampoo",
  "Suavitel",
  "Pinol",
  "Desengrasante",
  "Fabuloso"
};

// Variables para el desplazamiento del mensaje
char message[] = "Despachador de productos     ";
int messageLength = sizeof(message) - 1; // Longitud del mensaje sin el carácter nulo
int scrollPosition = 0; // Posición actual del desplazamiento
unsigned long scrollDelay = 150; // Retardo entre cada paso del desplazamiento



void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  pinMode(buttonSelectPin, INPUT_PULLUP);
  pinMode(buttonMenuPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  // Mostrar el mensaje de desplazamiento
  const unsigned long duration = 3000;
  unsigned long startTime = millis();

  while (millis() - startTime < duration) {
    lcd.clear();
    lcd.setCursor(15 - scrollPosition, 0);
    lcd.print(message);
    delay(scrollDelay);
    scrollPosition++;
    if (scrollPosition > messageLength + 16) {
      scrollPosition = 0;
    }
  }
  setZeroEeprom(maxMenuItems);
  loadFromEEPROM(maxMenuItems);
  showMenu();
}


void loop() {
  static bool configurationMode = false;
  static bool welcomeMessage =  false;
  bool STATE = false;

  digitalWrite(LED_BUILTIN, !STATE);
  if (digitalRead(buttonMenuPin) == LOW ) {
    configurationMode = true;
    delay(200);
    while (configurationMode) {
      showConfigurationMode();
    }
  } else {
    if (configurationMode == false && welcomeMessage == false) {
      welcomeMessage = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Bienvenidos");
      lcd.setCursor(0, 1);
      lcd.print("Ingrese monedas");
    }
  }
}

void showConfigurationMode() {
  static bool configurationMode = false;

  if (configurationMode == false) {
    configurationMode = true;
    showMenu();
  }

  if (digitalRead(buttonUpPin) == LOW) {
    menuIndex = (menuIndex - 1 + maxMenuItems) % maxMenuItems;
    showMenu();
    delay(200);
  } else if (digitalRead(buttonDownPin) == LOW) {
    menuIndex = (menuIndex + 1) % maxMenuItems;
    showMenu();
    delay(200);
  } else if (digitalRead(buttonSelectPin) == LOW) {
    delay(200);
    showSubMenu();
    showMenu();
  }
}


void showMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Configurar Produc");
  lcd.setCursor(0, 1);
  lcd.print("- ");
  lcd.print(menuItems[menuIndex]);
}

bool showSubMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">> ");
  lcd.print(menuItems[menuIndex]);

  lcd.setCursor(0, 1);
  lcd.print("Lt: ");
  lcd.print(productQuantity[menuIndex], 1);
  lcd.setCursor(7, 1);
  lcd.print(" $: ");
  lcd.print(productCost[menuIndex], 1);

  unsigned long selectButtonStartTime = millis();
  bool cursorVisible = false; // Variable para alternar el cursor
  
  while (true) {
      if (digitalRead(buttonUpPin) == LOW) {
        productQuantity[menuIndex] += 0.1;
        writeInEEPROM(productQuantity[menuIndex], menuIndex);
        delay(200);
      } else if (digitalRead(buttonDownPin) == LOW) {
        productQuantity[menuIndex] -= 0.1;
        if (productQuantity[menuIndex] <= 0.0){
          productQuantity[menuIndex] = 0.0;
        }
        writeInEEPROM(productQuantity[menuIndex], menuIndex);
        delay(200);
      }
      lcd.setCursor(4, 1);
      // Alternar el cursor visible/invisible cada 500 milisegundos
      if (millis() - selectButtonStartTime >= 500) {
        cursorVisible = !cursorVisible;
        if (cursorVisible == true) {
          lcd.print(productQuantity[menuIndex], 1);
        }else{
          lcd.print("   ");
        }
        selectButtonStartTime = millis(); // Reinicia el temporizador
      }
      if (digitalRead(buttonSelectPin) == LOW) {
        lcd.print(productQuantity[menuIndex], 1);
        delay(1000);
        break;
      }
      if (digitalRead(buttonMenuPin) == LOW) {
        lcd.print(productQuantity[menuIndex], 1);
        delay(200);
        return false;
      }
    }

    while (true) {
      if (digitalRead(buttonUpPin) == LOW) {
        productCost[menuIndex] += 0.1;
        writeInEEPROM(productCost[menuIndex], maxMenuItems+menuIndex);
        delay(200);
      } else if (digitalRead(buttonDownPin) == LOW) {
        productCost[menuIndex] -= 0.1;
        if (productCost[menuIndex] <= 0.0){
          productCost[menuIndex] = 0.0;
        }
        writeInEEPROM(productCost[menuIndex], maxMenuItems+menuIndex);
        delay(200);
      }
      lcd.setCursor(11, 1);

      // Alternar el cursor visible/invisible cada 500 milisegundos
      if (millis() - selectButtonStartTime >= 500) {
        cursorVisible = !cursorVisible;
        // Muestra u oculta el cursor
        if (cursorVisible == true) {
          lcd.print(productCost[menuIndex], 1);
        }else{
          lcd.print("   ");
        }
        selectButtonStartTime = millis(); // Reinicia el temporizador
      }
      if (digitalRead(buttonMenuPin) == LOW || digitalRead(buttonSelectPin) == LOW) {
        lcd.print(productCost[menuIndex], 1);
        delay(200);
        break;
      }
    }
    return false;
}


void writeInEEPROM(float valor, int direccion) {
  // Obtener un puntero al valor flotante para obtener sus bytes
  byte* pValor = (byte*)&valor;

  // Verificar que la dirección sea válida (entre 0 y el tamaño de la EEPROM)
  if (direccion >= 0 && direccion + sizeof(float) <= EEPROM.length()) {
    // Guardar los bytes del valor flotante en la dirección especificada
    for (int i = 0; i < sizeof(float); i++) {
      EEPROM.write(direccion + i, pValor[i]);
    }
  } else {
    // Mostrar un mensaje de error si la dirección no es válida
    Serial.println("Error: Dirección inválida para EEPROM o valor demasiado grande.");
  }
}

float readFromEEPROM(int direccion) {
  float valorLeido;

  // Obtener un puntero al valor flotante para obtener sus bytes
  byte* pValor = (byte*)&valorLeido;

  // Verificar que la dirección sea válida (entre 0 y el tamaño de la EEPROM)
  if (direccion >= 0 && direccion + sizeof(float) <= EEPROM.length()) {
    // Leer los bytes de la dirección especificada y reconstruir el valor flotante
    for (int i = 0; i < sizeof(float); i++) {
      pValor[i] = EEPROM.read(direccion + i);
    }
  } else {
    // Mostrar un mensaje de error si la dirección no es válida
    Serial.println("Error: Dirección inválida para EEPROM.");
    return 0.0; // Valor de retorno predeterminado en caso de error
  }

  return valorLeido;
}

void loadFromEEPROM(int lengthData){
  for (int i = 0; i < lengthData; i++) {
    productQuantity[i] = readFromEEPROM(i);
    productCost[i] = readFromEEPROM(maxMenuItems+i);
  }
}

void setZeroEeprom(int lengthData){
  for (int i = 0; i < lengthData; i++) {
    writeInEEPROM(0.0, i);
    writeInEEPROM(0.0, maxMenuItems+i);
  }
}

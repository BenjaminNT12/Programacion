#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>


// Conexión de la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines para los botones
const int buttonUpPin = 2;
const int buttonDownPin = 3;
const int buttonMenuPin = 4;
const int buttonSelectPin = 5;
const int EnterCoin = 6;
const int buttonProduct1Pin = 7;

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

byte customChar[] = {
  B00001,
  B00011,
  B00010,
  B00110,
  B10100,
  B11100,
  B01000,
  B00000
};

void setup() {
  lcd.begin(16, 2);
  
  lcd.home();
  lcd.write(0);
}

// Variables para el desplazamiento del mensaje
char message[] = "Limpieza...";
int messageLength = sizeof(message) - 1; // Longitud del mensaje sin el carácter nulo
int scrollPosition = 0; // Posición actual del desplazamiento
unsigned long scrollDelay = 100; // Retardo entre cada paso del desplazamiento
float totalCredit = 0.0; // Variable para el crédito total acumulado

void displayProgressBar(int percent, const char* message = "", int index = 0);

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar);
  
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
  pinMode(buttonSelectPin, INPUT_PULLUP);
  pinMode(buttonMenuPin, INPUT_PULLUP);
  pinMode(EnterCoin, INPUT);
  pinMode(buttonProduct1Pin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  // Mostrar el mensaje de desplazamiento
  const unsigned long duration = 3000;
  unsigned long startTime = millis();
  totalCredit = 0.0; // Inicializa el crédito total en cero

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
  // setZeroEeprom(maxMenuItems);
  loadFromEEPROM(maxMenuItems);
  showMenu();
}


void loop() {
  static bool configurationMode = false;
  static bool welcomeMessage =  false;
  static bool credit =  false;
  const char* message =  "Despachando...";
  bool STATE = false;

  digitalWrite(LED_BUILTIN, !STATE);
  if (digitalRead(buttonMenuPin) == LOW ) {
    configurationMode = true;
    delay(200);
    while(digitalRead(buttonMenuPin) == LOW){;}
    showMenu();
    while (configurationMode) {
      showConfigurationMode();
      if (digitalRead(buttonMenuPin) == LOW) {
        configurationMode = false;
        welcomeMessage = false;
        delay(200);
        break;  
      }
    }
  } else if (configurationMode == false && welcomeMessage == false) {
      welcomeMessage = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Bienvenidos");
      lcd.setCursor(0, 1);
      lcd.print("Ingrese monedas");
  } else if (digitalRead(EnterCoin) == HIGH) {
    totalCredit += 1.0;
    showCredit(totalCredit);
    delay(10);
    // credit = true;
  } else if (digitalRead(buttonProduct1Pin) == LOW) {

    showProduct(0);
    welcomeMessage = false;
  }
}

bool showConfigurationMode() {

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
  checkProductInfo(productQuantity[menuIndex], productCost[menuIndex], 1, 15);
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

void showCredit(float credit) {
  lcd.setCursor(0, 0);
  lcd.print("Ingrese monedas");
  
  lcd.setCursor(0, 1);
  lcd.print("Credito: $");
  lcd.print(credit, 2); // Muestra el crédito con dos decimales
}

void displayProgressBar(int percent, const char* message = "", int index = 0) {
  lcd.clear();
  lcd.setCursor(0, 0);  // Establece el cursor en la segunda fila
  lcd.print(menuItems[index]);
  lcd.print(" $:");
  lcd.print(productCost[index], 1);
  lcd.print(" lt");
  lcd.setCursor(int((16-sizeof(message))/2), 1);
  lcd.print(message);

  int progressBarWidth = map(percent, 0, 100, 0, 16);  // Mapea el porcentaje a la anchura de la barra
  
  lcd.setCursor(0, 1);  // Establece el cursor en la segunda fila
  
  for (int i = 0; i < 16; i++) {
    if (i < progressBarWidth) {
      lcd.write(0xFF);
    } 
  }
}

void showProduct(int index) {
  const char* message = "Llenando...";

  lcd.clear();
  for (int percent = 0; percent <= 100; percent++) {
    displayProgressBar(percent, message, index);
    delay(100);
  }
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gracias");
  lcd.setCursor(0, 1);
  lcd.print("Vuelva pronto");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ingrese monedas");
  lcd.setCursor(0, 1);
  lcd.print("Credito: $");
  lcd.print(totalCredit, 2);
}

void displayStatus(int row, int col, bool condition) {
  lcd.setCursor(col, row);
  
  if (condition) {
    lcd.print("✔");  // Caracter de palomita para éxito
  } else {
    lcd.print("⚠");  // Caracter de advertencia
  }
}

void checkProductInfo(float quantity, float price, int row, int col) {
  bool condition = (quantity > 0.0 && price > 0.0);
  displayStatus(row, col, condition);
}

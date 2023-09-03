#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>


// Conexión de la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines para los botones
const int buttonDownPin = 2;
const int buttonUpPin = 3;
const int buttonMenuPin = 4;
const int buttonSelectPin = 5;
const int EnterCoin = 6;
const int buttonProduct1Pin = 7;

#define prod0button buttonDownPin
#define prod1button buttonUpPin
#define prod2button buttonMenuPin
#define prod3button buttonSelectPin
#define prod4button buttonProduct1Pin
// #define prod5button buttonProduct2Pin
// #define prod6button buttonProduct3Pin
// #define prod7button buttonProduct4Pin

// Variables para el menú
int menuIndex = 0; // Índice del elemento del menú actual
const int maxMenuItems = 8; // Número total de elementos del menú

float productQuantity[maxMenuItems] = {0.0}; // Cantidad de producto a dispensar en litros
float productCost[maxMenuItems] = {0.0}; // Costo del producto
float pumpTime[maxMenuItems] = {0.0}; // Tiempo de dispensado del producto
// bool saveVal[] = false;

// Texto para cada elemento del menú
String menuItems[] = {
  "Sandia",
  "Pina",
  "Fresa",
  "Limon",
  "Naranja",
  "Coco",
  "Melon",
  "Uva"
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
  // lcd.write((byte)0);
  // Mostrar el custom char en la pantalla

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
  static bool showOneTime =  false;
  static bool credit =  false;
  const char* message =  "Despachando...";
  bool STATE = false;

  digitalWrite(LED_BUILTIN, !STATE);
  if (digitalRead(buttonMenuPin) == LOW && digitalRead(buttonSelectPin) == LOW) {
    configurationMode = true;
    showMenu();
    delay(1000);
    while(digitalRead(buttonMenuPin) == LOW || digitalRead(buttonSelectPin) == LOW){;}
    while (configurationMode) {
      showConfigurationMode();
      if (digitalRead(buttonMenuPin) == LOW) {
        configurationMode = false;
        welcomeMessage = false;
        delay(200);
        break;  
      }
    }
  } else if (configurationMode == false && welcomeMessage == false && credit == false) {
      welcomeMessage = true;
      showWelcomeMessage();
  } else if (digitalRead(EnterCoin) == HIGH) {
    totalCredit += 1.0;
    delay(40);
    credit = checkCredit(totalCredit, 0.0);
    showOneTime = false;
  }else if(digitalRead(prod0button) == LOW && productCost[0] > 0.0f){
    welcomeMessage = false;
    credit = dispenceProduct(&totalCredit,productCost[0],0);
    showOneTime = false;
  }else if(digitalRead(prod1button) == LOW && productCost[1] > 0.0f){
    welcomeMessage = false;
    credit = dispenceProduct(&totalCredit,productCost[1],1);
    showOneTime = false;
  }else if (digitalRead(prod2button) == LOW && productCost[2] > 0.0f) {
    welcomeMessage = false;
    credit = dispenceProduct(&totalCredit,productCost[2],2);
    showOneTime = false;
  } else if (digitalRead(prod3button) == LOW && productCost[3] > 0.0f) {
    welcomeMessage = false;
    credit = dispenceProduct(&totalCredit,productCost[3],3);
    showOneTime = false;
  } else if (digitalRead(prod4button) == LOW && productCost[4] > 0.0f) {
    welcomeMessage = false;
    credit = dispenceProduct(&totalCredit,productCost[4],4);
    showOneTime = false;
  }else if(credit == true && showOneTime == false){
    showOneTime = showCredit(totalCredit);
    credit = checkCredit(totalCredit, 0.0);
  }
}

bool dispenceProduct(float *_totalCredit,float _productCost,int _index){
  bool credit = false;

  if (*_totalCredit >= _productCost){
    *_totalCredit -= _productCost;
    showProduct(_index);
    credit = checkCredit(*_totalCredit, 0.0);
  }else{
    showMenuCreditInsuficient();
    credit = checkCredit(*_totalCredit, 0.0);
  }
  
  return credit;
}

bool checkCredit(float credit, float cost){
  if (credit > cost){
    return true;
  }else{
    return false;
  }
}

void showWelcomeMessage(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Bienvenidos");
  lcd.setCursor(0, 1);
  lcd.print("Ingrese monedas");
}

void showMenuCreditInsuficient(){
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Credito ");
  lcd.setCursor(2, 1);
  lcd.print("insuficiente");
  delay(2000);
}

bool showConfigurationMode() {

  if (digitalRead(buttonDownPin) == LOW) {
    menuIndex = (menuIndex - 1 + maxMenuItems) % maxMenuItems;
    showMenu();
    delay(200);
  } else if (digitalRead(buttonUpPin) == LOW) {
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
  lcd.print(menuIndex);
  lcd.print("-");
  lcd.print(menuItems[menuIndex]);
  checkProductInfo( productQuantity[menuIndex], 
                    productCost[menuIndex],
                    pumpTime[menuIndex], 1, 15);
}

bool showSubMenu() {
  unsigned long selectButtonStartTime = millis();
  bool cursorVisible = false; // Variable para alternar el cursor
  float data = 0.0;

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

  while (true) {
      if (digitalRead(buttonUpPin) == LOW) {
        productQuantity[menuIndex] += 1;
        writeInEEPROM(productQuantity[menuIndex], menuIndex);
        delay(200);
      } else if (digitalRead(buttonDownPin) == LOW) {
        productQuantity[menuIndex] -= 1;
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
        productCost[menuIndex] += 1;
        writeInEEPROM(productCost[menuIndex], maxMenuItems+menuIndex);
        delay(200);
      } else if (digitalRead(buttonDownPin) == LOW) {
        productCost[menuIndex] -= 1;
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

    lcd.setCursor(0, 1);
    lcd.print("                    ");

    while (true) {
      if (digitalRead(buttonUpPin) == LOW) {
        pumpTime[menuIndex] += 5;
        writeInEEPROM(pumpTime[menuIndex], maxMenuItems*(int)2+menuIndex);
        delay(200);       
      } else if (digitalRead(buttonDownPin) == LOW) {
        pumpTime[menuIndex] -= 5;
        if (pumpTime[menuIndex] <= 0.0){
          pumpTime[menuIndex] = 0.0;
        }
        writeInEEPROM(pumpTime[menuIndex], maxMenuItems*(int)2+menuIndex);
        delay(200);       
      }

      lcd.setCursor(0, 1);
      lcd.print("T: ");
      // Alternar el cursor visible/invisible cada 500 milisegundos
      if (millis() - selectButtonStartTime >= 500) {
        cursorVisible = !cursorVisible;
        if (cursorVisible == true) {
          lcd.print(pumpTime[menuIndex], 1);
          lcd.print(" Seg.");
        }else{
          lcd.print("   ");
        }
        selectButtonStartTime = millis(); // Reinicia el temporizador
      }

      lcd.setCursor(3, 2);
      lcd.print(pumpTime[menuIndex], 1);
      if (digitalRead(buttonMenuPin) == LOW || digitalRead(buttonSelectPin) == LOW) {
        lcd.print(pumpTime[menuIndex], 1);
        delay(200);
        break;
      }
    }

    return false;
}



void writeInEEPROM(float valor, int direccion) {
  // Obtener un puntero al valor flotante para obtener sus bytes
  byte* pValor = (byte*)&valor;

  direccion = direccion*sizeof(float);
  // Verificar que la dirección sea válida (entre 0 y el tamaño de la EEPROM)
  if (direccion >= 0 && direccion + sizeof(float) <= EEPROM.length()) {
    // Guardar los bytes del valor flotante en la dirección especificada
    for (int i = 0; i < sizeof(float); i++) {
      EEPROM.write(direccion + i, pValor[i]);
    }
    Serial.println("Escritura en EEPROM exitosa!.");
  } else {
    // Mostrar un mensaje de error si la dirección no es válida
    Serial.println("Error: Dirección inválida para EEPROM o valor demasiado grande.");
  }
}

float readFromEEPROM(int direccion) {
  float valorLeido;

  // Obtener un puntero al valor flotante para obtener sus bytes
  byte* pValor = (byte*)&valorLeido;
  direccion = direccion*sizeof(float);
  // Verificar que la dirección sea válida (entre 0 y el tamaño de la EEPROM)
  if (direccion >= 0 && direccion + sizeof(float) <= EEPROM.length()) {
    // Leer los bytes de la dirección especificada y reconstruir el valor flotante
    for (int i = 0; i < sizeof(float); i++) {
      pValor[i] = EEPROM.read(direccion + i);
    }
    Serial.println("Leectura en EEPROM exitosa!.");
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
    pumpTime[i] = readFromEEPROM((int)2*maxMenuItems+i);
    Serial.print(" lt: ");
    Serial.print(productQuantity[i]);
    Serial.print(", ");
    Serial.print(productCost[i]);
    Serial.print(", ");
    Serial.println(pumpTime[i]);
  }
}

void setZeroEeprom(int lengthData){
  for (int i = 0; i < lengthData; i++) {
    writeInEEPROM(0.0, i);
    writeInEEPROM(0.0, maxMenuItems+i);
    writeInEEPROM(0.0, (int)2*maxMenuItems+i);
  }
}

bool showCredit(float credit) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ingrese monedas");
  
  lcd.setCursor(0, 1);
  lcd.print("Credito: $");
  lcd.print(credit, 2); // Muestra el crédito con dos decimales
  return true;
}

void displayProgressBar(int percent, const char* message = "", int index = 0) {
  lcd.clear();
  lcd.setCursor(0, 0);  // Establece el cursor en la segunda fila
  lcd.print(menuItems[index]);
  lcd.print(" $:");
  lcd.print(productCost[index], 1);
  lcd.print(" lt");
  lcd.setCursor(2, 1);
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
  lcd.setCursor(4, 0);
  lcd.print("Gracias");
  lcd.setCursor(1, 1);
  lcd.print("Vuelva pronto");
  delay(2000);
  lcd.clear();
}

void displayStatus(int row, int col, bool condition) {
  lcd.setCursor(col, row);
  
  if (condition) {
    lcd.print("1");  // Caracter de palomita para éxito
  } else {
    lcd.print("0");  // Caracter de advertencia
  }
}

void checkProductInfo(float quantity, float price, float time, int row, int col) {
  bool condition = false;

  if (quantity > 0.0 && price > 0.0 && time > 0.0) {
    condition = true;
  }
  displayStatus(row, col, condition);
}
























































// bool showSubMenu() {
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print(">> ");
//   lcd.print(menuItems[menuIndex]);

//   lcd.setCursor(0, 1);
//   lcd.print("Lt: ");
//   lcd.print(productQuantity[menuIndex], 1);
//   lcd.setCursor(7, 1);
//   lcd.print(" $: ");
//   lcd.print(productCost[menuIndex], 1);

//   unsigned long selectButtonStartTime = millis();
//   bool cursorVisible = false; // Variable para alternar el cursor
  
//   while (true) {
//       if (digitalRead(buttonUpPin) == LOW) {
//         productQuantity[menuIndex] += 1;
//         writeInEEPROM(productQuantity[menuIndex], menuIndex);
//         delay(200);
//       } else if (digitalRead(buttonDownPin) == LOW) {
//         productQuantity[menuIndex] -= 1;
//         if (productQuantity[menuIndex] <= 0.0){
//           productQuantity[menuIndex] = 0.0;
//         }
//         writeInEEPROM(productQuantity[menuIndex], menuIndex);
//         delay(200);
//       }
//       lcd.setCursor(4, 1);
//       // Alternar el cursor visible/invisible cada 500 milisegundos
//       if (millis() - selectButtonStartTime >= 500) {
//         cursorVisible = !cursorVisible;
//         if (cursorVisible == true) {
//           lcd.print(productQuantity[menuIndex], 1);
//         }else{
//           lcd.print("   ");
//         }
//         selectButtonStartTime = millis(); // Reinicia el temporizador
//       }
//       if (digitalRead(buttonSelectPin) == LOW) {
//         lcd.print(productQuantity[menuIndex], 1);
//         delay(1000);
//         break;
//       }
//       if (digitalRead(buttonMenuPin) == LOW) {
//         lcd.print(productQuantity[menuIndex], 1);
//         delay(200);
//         return false;
//       }
//     }

//     while (true) {
//       if (digitalRead(buttonUpPin) == LOW) {
//         productCost[menuIndex] += 1;
//         writeInEEPROM(productCost[menuIndex], maxMenuItems+menuIndex);
//         delay(200);
//       } else if (digitalRead(buttonDownPin) == LOW) {
//         productCost[menuIndex] -= 1;
//         if (productCost[menuIndex] <= 0.0){
//           productCost[menuIndex] = 0.0;
//         }
//         writeInEEPROM(productCost[menuIndex], maxMenuItems+menuIndex);
//         delay(200);
//       }
//       lcd.setCursor(11, 1);

//       // Alternar el cursor visible/invisible cada 500 milisegundos
//       if (millis() - selectButtonStartTime >= 500) {
//         cursorVisible = !cursorVisible;
//         // Muestra u oculta el cursor
//         if (cursorVisible == true) {
//           lcd.print(productCost[menuIndex], 1);
//         }else{
//           lcd.print("   ");
//         }
//         selectButtonStartTime = millis(); // Reinicia el temporizador
//       }
//       if (digitalRead(buttonMenuPin) == LOW || digitalRead(buttonSelectPin) == LOW) {
//         lcd.print(productCost[menuIndex], 1);
//         delay(200);
//         break;
//       }
//     }
//     return false;
// }























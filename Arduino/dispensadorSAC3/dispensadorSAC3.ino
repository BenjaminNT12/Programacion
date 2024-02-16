#include <Wire.h> // Biblioteca para la comunicación I2C
#include <LiquidCrystal_I2C.h> // Biblioteca para controlar la pantalla LCD
#include <EEPROM.h> // Biblioteca para acceder a la memoria EEPROM
#include <ShiftIn.h>

ShiftIn<2> shift;

// Conexión de la pantalla LCD
const int LCD_WIDTH = 20;
const int LCD_HEIGHT = 4;
LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);

const unsigned long TUTORIAL_WAIT_TIME = 5;
const unsigned long DYNO_GAME_WAIT_TIME = 10;

// Pines para los botones
const int BUTTON_DOWN_PIN = 0;
const int BUTTON_UP_PIN = 1;
const int BUTTON_MENU_PIN = 2;
const int BUTTON_SELECT_PIN = 3;

const int BUTTON_PRODUCT1_PIN = 4;
const int BUTTON_PRODUCT2_PIN = 5;
const int BUTTON_PRODUCT3_PIN = 6;
const int BUTTON_PRODUCT4_PIN = 7;

// pin para la ENTRADA de monedas
const int COIN_INPUT_PIN = 7;
// pin para la ENTRADA del HOOPER_PIN, contabiliza cuantas 
// monedas salen de HOOPER_PIN
const int HOOPER_OUTPUT_PIN = 8;

// Pines para la SALIDAS de las bombas
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
byte leds = 0;		// Variable to hold the pattern of which LEDs are currently turned on or off

// Pines para la SALIDA de activacion del rele del HOOPER_PIN
const int HOOPER_PIN = 38; 

#define JUMP_HIGH 1
#define JUMP_LOW 2
#define JUMP_NULL 0

#define PROD0_BUTTON BUTTON_DOWN_PIN
#define PROD1_BUTTON BUTTON_UP_PIN
#define PROD2_BUTTON BUTTON_MENU_PIN
#define PROD3_BUTTON BUTTON_SELECT_PIN
#define PROD4_BUTTON BUTTON_PRODUCT1_PIN
#define PROD5_BUTTON BUTTON_PRODUCT2_PIN
#define PROD6_BUTTON BUTTON_PRODUCT3_PIN
#define PROD7_BUTTON BUTTON_PRODUCT4_PIN

#define ACTIVATE_HOOPER_OUTPUT HOOPER_PIN
#define COIN_OUTPUT HOOPER_OUTPUT_PIN
// #define COIN_OUTPUT BUTTON_PRODUCT1_PIN
// Variables para el menú
int menuIndex = 0; // Índice del elemento del menú actual
const int MAX_MENU_ITEMS = 8; // Número total de elementos del menú
const int PROD_BUTTONS[MAX_MENU_ITEMS] = {PROD0_BUTTON, PROD1_BUTTON, PROD2_BUTTON, PROD3_BUTTON, PROD4_BUTTON, PROD5_BUTTON, PROD6_BUTTON, PROD7_BUTTON};


float productQuantity[MAX_MENU_ITEMS] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; // Cantidad de producto a dispensar en litros
float productCost[MAX_MENU_ITEMS] = {10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0}; // Costo del producto
float pumpTime[MAX_MENU_ITEMS] = {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0}; // Tiempo de dispensado del producto

const int GAME_SPEED = 50;

// Texto para cada elemento del menú
String menuItems[] = {
  "Cloralex",
  "Pinol",
  "Maestro Limpio",
  "Fabuloso",
  "Downy",
  "Mas color",
  "Roma",
  "Zote"
};

const PROGMEM byte CHARDINO_1[8] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x18, 0x1C};
const PROGMEM byte CHARDINO_2[8] = {0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x0F, 0x1F};
const PROGMEM byte CHARDINO_3[8] = {0x1F, 0x17, 0x1F, 0x1F, 0x1C, 0x1F, 0x1C, 0x1C};
const PROGMEM byte CHARDINO_4[8] = {0x10, 0x18, 0x18, 0x18, 0x00, 0x10, 0x00, 0x00};
const PROGMEM byte CHARDINO_5[8] = {0x1F, 0x1F, 0x0F, 0x07, 0x03, 0x03, 0x02, 0x03};
const PROGMEM byte CHARDINO_6[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x16, 0x02, 0x02, 0x03};
const PROGMEM byte CHARDINO_6T[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x06, 0x12, 0x02, 0x03};
const PROGMEM byte CHARDINO_5T[8] = {0x1F, 0x1F, 0x0F, 0x07, 0x03, 0x03, 0x00, 0x00};
const PROGMEM byte CHARDINO_7T[8] = {0x1F, 0x19, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00};
const PROGMEM byte CHARDINO_5D[8] = {0x1F, 0x1F, 0x0F, 0x07, 0x03, 0x03, 0x02, 0x03};
const PROGMEM byte CHARDINO_6D[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x16, 0x03, 0x00, 0x00};
const PROGMEM byte CHARDINO_7D[8] = {0x1F, 0x19, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00};

const char message1[] PROGMEM = "Bienvenidos";
const char message2[] PROGMEM = "1: Deposite sus monedas. ";
const char message3[] PROGMEM = "2: Coloque su envase . ";
const char message4[] PROGMEM = "3: Presione el boton . ";

const char* const tutorialMessages[] PROGMEM = {
  message1,
  message2,
  message3,
  message4
};

// Variables para el desplazamiento del mensaje
char message[] = "Dispensador..."; // Mensaje de desplazamiento
int messageLength = sizeof(message) - 1; // Longitud del mensaje sin el carácter nulo
int scrollPosition = 0; // Posición actual del desplazamiento
unsigned long scrollDelay = 100; // Retardo entre cada paso del desplazamiento
float totalCredit = 0.0; // Variable para el crédito total acumulado
bool service = false; // Variable para el crédito total acumulado
unsigned long startTime = millis(); // Tiempo de inicio de la dispensación
char ledState = 0x1; // Variable booleana para el estado del LED incorporado
int score = 0;  
int scoreHi = 0;
bool firstRun = true;

bool configurationMode = false; // Variable booleana estática para indicar si el dispositivo está en modo de configuración
bool welcomeMessage = false; // Variable booleana estática para indicar si se ha mostrado el mensaje de bienvenida
bool showOneTime = false; // Variable booleana estática para indicar si se ha mostrado el crédito del usuario
bool change = false; // Variable booleana estática para indicar si se ha mostrado el crédito del usuario
bool credit = false; // Variable booleana estática para indicar si el crédito del usuario es suficiente para comprar un 
bool tutorialShow = false; // Variable booleana estática para indicar si se ha mostrado el tutorial

// Declaración de funciones
void costOfProduct(const char*, int index);
void displayProgressBar(int percent);
void dinoCaminar(int pos, unsigned long tiempo);
void mostrarTutorialLCD();

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

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);  
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);


  // Mostrar el mensaje de desplazamiento
  const unsigned long duration = 3000; // Duración del mensaje de desplazamiento en milisegundos
  unsigned long startTime = millis(); // Tiempo de inicio del mensaje de desplazamiento
  totalCredit = 0.0; // Inicializa el crédito total en cero

  for(int i = 0; i < 8; i++) setOutput(i, false);

  while (millis() - startTime < duration) { // Mientras el tiempo transcurrido sea menor que la duración del mensaje de desplazamiento
    lcd.clear(); // Borra la pantalla LCD
    lcd.setCursor(15 - scrollPosition, 0); // Establece la posición del cursor en la pantalla LCD
    lcd.print(message); // Imprime el mensaje de desplazamiento en la pantalla LCD
    lcd.setCursor(0, 1); // Establece la posición del cursor en la pantalla LCD
    lcd.print("Version 0.0.1"); // Imprime el mensaje de desplazamiento en la pantalla LCD
    delay(scrollDelay); // Espera un tiempo para el desplazamiento
    scrollPosition++; // Incrementa la posición de desplazamiento
    if (scrollPosition > messageLength + LCD_WIDTH) { // Si la posición de desplazamiento es mayor que la longitud del mensaje más LCD_WIDTH
      scrollPosition = 0; // Reinicia la posición de desplazamiento
    }
  }
  // setZeroEeprom(MAX_MENU_ITEMS);
  loadFromEEPROM(MAX_MENU_ITEMS); // Carga los datos de la EEPROM
  showMenu(); // Muestra el menú en la pantalla LCD
}


void loop() {
  static unsigned long lastPrintedTime = 0;
  unsigned long currentTime = (millis() - startTime) / 1000;
  static bool dynoGameShow = false; // Variable booleana estática para indicar si se ha mostrado el juego del dinosaurio

  handleButtons(); // Maneja los botones
  handleTimeEvents(currentTime, lastPrintedTime, startTime);
}

bool hasTimeElapsed(unsigned long startTime, int waitTimeInSeconds) {
    return millis() - startTime > waitTimeInSeconds * 1000;
}

void handleTimeEvents(unsigned long currentTime, unsigned long lastPrintedTime, unsigned long startTime) {
    if (hasTimeElapsed(startTime, DYNO_GAME_WAIT_TIME)) {
        tutorialShow = true;
        Serial.println("entro en la funcion dynoGame");
        dynoGame();
    } else if (hasTimeElapsed(startTime, TUTORIAL_WAIT_TIME) && !tutorialShow) {
        Serial.println("entro en la funcion mostrar mostrarTutorialLCD");
        mostrarTutorialLCD();
    } else if (currentTime != lastPrintedTime) {
        lastPrintedTime = currentTime;
        Serial.print("StartTime: "); Serial.println(currentTime);
    }
}


void enterConfigurationMode() {
  configurationMode = true; // El dispositivo entra en modo de configuración
  showMenu(); // Muestra el menú en la pantalla LCD
  Serial.println("delay(1000)");
  delay(1000); // Espera 1 segundo
  while(getState(BUTTON_MENU_PIN) == 1 || getState(BUTTON_SELECT_PIN) == 1){;} // Espera hasta que se suelten los botones de menú y selección
  while (configurationMode) { // Mientras el dispositivo esté en modo de configuración
    showConfigurationMode(); // Muestra el modo de configuración en la pantalla LCD
    if (getState(BUTTON_MENU_PIN) == 1) { // Si se presiona el botón de menú
      configurationMode = false; // El dispositivo sale del modo de configuración
      welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
      Serial.println("delay(200)");
      delay(200); // Espera 200 milisegundos
      break; // Sale del bucle while
    }
  }
  Serial.println("entro en la condicion 1");
}

void resetScoreAndTime() {
  if (score > scoreHi) {
    scoreHi = score;
    writeInEEPROM(scoreHi, MAX_MENU_ITEMS * 2 + MAX_MENU_ITEMS * 2 + 2);
  }
  score = 0;
  startTime = millis();
  firstRun = true;
  tutorialShow = false;
}

void handleProductButton(int button, float cost) {
  if (getState(button) == 1 && cost > 0.0f) {
    welcomeMessage = false;
    service = false;
    credit = dispenceProduct(&totalCredit, cost, button);
    showOneTime = false;
    change = true;
    Serial.println("entro en la condicion " + String(button));
    resetScoreAndTime();
  }
}

void handleCredit() {
  if (credit == true && showOneTime == false) {
    showOneTime = showCredit(totalCredit);
    credit = checkCredit(totalCredit, 0.0);
    resetScoreAndTime();

    if (totalCredit > 0.0 && change == true && service == true) {
      showChangeMessage();
      digitalWrite(ACTIVATE_HOOPER_OUTPUT, HIGH);

      while (totalCredit > 0.0) {
        if (getState(COIN_OUTPUT) == LOW) {
          totalCredit -= 1.0;
          Serial.println("delay(200)");
          delay(200);
        }
      }

      digitalWrite(ACTIVATE_HOOPER_OUTPUT, LOW);
      showGoodbyeMessage();
      credit = checkCredit(totalCredit, 0.0);
      change = false;
      service = false;
    }
    Serial.println("entro en la condicion 12");
  }
}

void handleButtons() {
  if (getState(BUTTON_MENU_PIN) == 1 && getState(BUTTON_SELECT_PIN) == 1) {
    enterConfigurationMode();
  } else if (!configurationMode && !welcomeMessage && !credit) {
    welcomeMessage = true;
    showWelcomeMessage();
    Serial.println("entro en la condicion 2");
    resetScoreAndTime();
  } else if (getState(COIN_INPUT_PIN) == HIGH) {
    totalCredit += 1.0;
    Serial.println("delay(40)");
    delay(40);
    credit = checkCredit(totalCredit, 0.0);
    showOneTime = false;
    service = false;
    Serial.println("entro en la condicion 3");
    resetScoreAndTime();
  } else {
    for (int i = 0; i < 8; i++) {
      handleProductButton(PROD_BUTTONS[i], productCost[i]);
    }
  }

  handleCredit();
}
/**
 * Muestra un mensaje en la pantalla LCD indicando el cambio que se debe entregar al usuario.
 */
void showChangeMessage(){
  lcd.clear(); // Limpia la pantalla LCD
  lcd.setCursor(0, 0); // Establece el cursor en la primera fila y primera columna
  lcd.print("Tome su cambio: "); // Muestra el mensaje "Tome su cambio: "
  lcd.setCursor(0, 1); // Establece el cursor en la segunda fila y primera columna
  lcd.print("$: "); // Muestra el símbolo de dólar
  lcd.print(totalCredit); // Muestra el valor del crédito restante como cambio
}


void mostrarTutorialLCD() {
  static unsigned long lastUpdate = 0;
  static int i = 1;
  static int j = 0;
  char buffer[100];

  if (millis() - lastUpdate >= 100) { // Si han pasado 3 segundos
    lastUpdate = millis(); // Actualiza el tiempo de la última actualización

    if (i < sizeof(tutorialMessages) / sizeof(tutorialMessages[0])) {
      lcd.setCursor(0, i);
      lcd.print("                "); // Limpia la línea

      strcpy_P(buffer, (char*)pgm_read_word(&(tutorialMessages[i])));

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
      i = 1;
    }
  }
}
/**
 * Muestra un mensaje de despedida en la pantalla LCD después de que el usuario ha realizado una compra.
 */
void showGoodbyeMessage(){
  lcd.clear(); // Limpia la pantalla LCD
  lcd.setCursor(0, 0); // Establece el cursor en la primera fila y primera columna
  lcd.print("Gracias por su"); // Muestra el mensaje "Gracias por su"
  lcd.setCursor(5, 1); // Establece el cursor en la segunda fila y sexta columna
  lcd.print("compra"); // Muestra el mensaje "compra"
  Serial.println("delay(2000)");delay(2000);; // Espera 2 segundos antes de continuar
}


/**
 * Dispensa un producto si el crédito del usuario es suficiente.
 * 
 * @param _totalCredit Un puntero al crédito total del usuario.
 * @param _productCost El costo del producto.
 * @param _index El índice del producto a dispensar.
 * 
 * @return Devuelve un valor booleano que indica si el crédito es suficiente para dispensar el producto.
 */
bool dispenceProduct(float *_totalCredit, float _productCost, int _index){
  bool credit = false; // Inicializa la variable credit como false

  if (*_totalCredit >= _productCost){ // Si el crédito es suficiente para comprar el producto
    *_totalCredit -= _productCost; // Resta el costo del producto del crédito total
    showProduct(_index); // Muestra el producto dispensado en la pantalla LCD
    credit = checkCredit(*_totalCredit, 0.0); // Verifica si el crédito restante es suficiente para comprar otro producto
  }else{ // Si el crédito no es suficiente para comprar el producto
    showMenuCreditInsuficient(_productCost, _index); // Muestra un mensaje en la pantalla LCD indicando que el crédito es insuficiente
    credit = checkCredit(*_totalCredit, 0.0); // Verifica si el crédito restante es suficiente para comprar otro producto
  }
  
  return credit; // Devuelve un valor booleano que indica si el crédito es suficiente para dispensar el producto
}





/**
 * Verifica si el crédito del usuario es suficiente para comprar un producto.
 * 
 * @param credit El crédito actual del usuario.
 * @param cost El costo del producto.
 * 
 * @return Devuelve un valor booleano que indica si el crédito es suficiente para comprar el producto.
 */
bool checkCredit(float credit, float cost){
  if (credit > cost){ // Si el crédito es mayor que el costo del producto
    return true; // Devuelve true para indicar que el crédito es suficiente
  }else{
    return false; // Devuelve false para indicar que el crédito no es suficiente
  }
}

/**
 * Imprime cuatro líneas de texto en la pantalla LCD.
 * 
 * @param line1 El texto para la primera línea.
 * @param line2 El texto para la segunda línea.
 * @param line3 El texto para la tercera línea.
 * @param line4 El texto para la cuarta línea.
 */
void printLines(const char* line1, const char* line2, const char* line3, const char* line4) {
  lcd.clear(); // Limpia la pantalla LCD

  // Define un array con las líneas de texto
  const char* lines[] = {line1, line2, line3, line4};

  // Recorre cada línea de texto
  for (int i = 0; i < 4; i++) {
    // Si la línea de texto no es NULL, la imprime en la pantalla LCD
    if (lines[i] != 0) {
      int length = strlen(lines[i]); // Obtiene la longitud de la línea de texto
      int position = (20 - length) / 2; // Calcula la posición para centrar el texto
      lcd.setCursor(position, i); // Posiciona el cursor
      lcd.print(lines[i]); // Imprime la línea de texto
    }
  }
}

/**
 * Muestra un mensaje de bienvenida en la pantalla LCD.
 */
void showWelcomeMessage(){
  int length = 0;
  int posicion = 0;

  // const char* text3 = "SAC de Mexico";
  const char* text = "Bienvenidos";
  const char* text2 = "Ingrese monedas";

  printLines(text, text2, NULL, NULL);
}

/**
 * Obtiene el nombre del producto por el número de índice.
 * 
 * @param index El índice del producto.
 * @return El nombre del producto.
 */
String getProductName(int index) {
  // Comprueba si el índice es válido
  if (index >= 0 && index < sizeof(menuItems) / sizeof(menuItems[0])) {
    return menuItems[index]; // Devuelve el nombre del producto
  } else {
    return "Índice inválido"; // Devuelve un mensaje de error si el índice no es válido
  }
}

void showMenuCreditInsuficient(float costPerLiter, int index){
  int posicion = 0;
  const char* text = "Credito";
  const char* text2 = "Insuficiente";

  printLines(text, text2, getProductName(index).c_str(), 0);

  posicion = (20 - 7)/2;
  lcd.setCursor(posicion, 3); // Posiciona el cursor en la segunda línea de la pantalla
  lcd.print("$:"); // Imprime el costo por litro
  lcd.print(costPerLiter); // Imprime el costo por litro
  Serial.println("delay(2000)");delay(2000);;
}

/**
 * Muestra el modo de configuración y permite al usuario navegar por los productos y acceder a la configuración de cada uno.
 * 
 * @return Devuelve un valor booleano que indica si se ha salido del modo de configuración.
 */
bool showConfigurationMode() {
  if (getState(BUTTON_DOWN_PIN) == 1) { // Si se presiona el botón de abajo
    menuIndex = (menuIndex - 1 + MAX_MENU_ITEMS) % MAX_MENU_ITEMS; // Decrementa el índice del producto actual
    showMenu(); // Muestra el menú actualizado
    Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar rebotes en el botón
  } else if (getState(BUTTON_UP_PIN) == 1) { // Si se presiona el botón de arriba
    menuIndex = (menuIndex + 1) % MAX_MENU_ITEMS; // Incrementa el índice del producto actual
    showMenu(); // Muestra el menú actualizado
    Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar rebotes en el botón
  } else if (getState(BUTTON_SELECT_PIN) == 1) { // Si se presiona el botón de selección
    Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar rebotes en el botón
    showSubMenu(); // Muestra el submenú para configurar el producto actual
    showMenu(); // Muestra el menú actualizado
  }
  return false; // Devuelve false para indicar que no se ha salido del modo de configuración
}


/**
 * Muestra el menú en la pantalla LCD y llama a la función checkProductInfo para verificar y actualizar la información del producto.
 */
void showMenu() {
  lcd.clear(); // Limpia la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Configurar Producto"); // Imprime el título del menú
  lcd.setCursor(0, 1);
  lcd.print(menuIndex); // Imprime el índice del producto actual
  lcd.print("-");
  lcd.print(menuItems[menuIndex]); // Imprime el nombre del producto actual
  checkProductInfo( productQuantity[menuIndex], 
                    productCost[menuIndex],
                    pumpTime[menuIndex], 1, 15); // Llama a la función checkProductInfo para verificar y actualizar la información del producto
}

bool showSubMenu() {
  unsigned long selectButtonStartTime = millis(); // Variable para medir el tiempo de pulsación del botón
  bool cursorVisible = false; // Variable para alternar el cursor
  float data = 0.0; // Variable para almacenar datos

  lcd.clear(); // Limpia la pantalla LCD
  lcd.setCursor(0, 0); // Establece el cursor en la primera fila, primera columna
  lcd.print(">> "); // Imprime el indicador de menú
  lcd.print(menuItems[menuIndex]); // Imprime el nombre del elemento de menú seleccionado

  lcd.setCursor(0, 1); // Establece el cursor en la segunda fila, primera columna
  lcd.print("Lt: "); // Imprime la etiqueta de cantidad
  lcd.print(productQuantity[menuIndex], 1); // Imprime la cantidad del producto seleccionado
  lcd.setCursor(7, 1); // Establece el cursor en la segunda fila, octava columna
  lcd.print(" $: "); // Imprime la etiqueta de costo
  lcd.print(productCost[menuIndex], 1); // Imprime el costo del producto seleccionado

  while (true) {
      if (getState(BUTTON_UP_PIN) == 1) { // Si se presiona el botón de arriba
        productQuantity[menuIndex] += 1; // Incrementa la cantidad del producto seleccionado
        writeInEEPROM(productQuantity[menuIndex], menuIndex); // Escribe la cantidad en la memoria EEPROM
        Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar múltiples pulsaciones
      } else if (getState(BUTTON_DOWN_PIN) == 1) { // Si se presiona el botón de abajo
        productQuantity[menuIndex] -= 1; // Decrementa la cantidad del producto seleccionado
        if (productQuantity[menuIndex] <= 0.0){ // Si la cantidad es menor o igual a cero
          productQuantity[menuIndex] = 0.0; // Establece la cantidad en cero
        }
        writeInEEPROM(productQuantity[menuIndex], menuIndex); // Escribe la cantidad en la memoria EEPROM
        Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar múltiples pulsaciones
      }
      lcd.setCursor(4, 1); // Establece el cursor en la segunda fila, quinta columna
      // Alternar el cursor visible/invisible cada 500 milisegundos
      if (millis() - selectButtonStartTime >= 500) {
        cursorVisible = !cursorVisible; // Alterna el valor de la variable cursorVisible
        if (cursorVisible == true) { // Si el cursor es visible
          lcd.print(productQuantity[menuIndex], 1); // Imprime la cantidad del producto seleccionado
        }else{ // Si el cursor no es visible
          lcd.print("   "); // Imprime tres espacios en blanco
        }
        selectButtonStartTime = millis(); // Reinicia el temporizador
      }
      if (getState(BUTTON_SELECT_PIN) == 1) { // Si se presiona el botón de selección
        lcd.print(productQuantity[menuIndex], 1); // Imprime la cantidad del producto seleccionado
        Serial.println("delay(1000)");delay(1000);; // Espera 1 segundo
        break; // Sale del bucle while
      }
      if (getState(BUTTON_MENU_PIN) == 1) { // Si se presiona el botón de menú
        lcd.print(productQuantity[menuIndex], 1); // Imprime la cantidad del producto seleccionado
        Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar múltiples pulsaciones
        return false; // Retorna falso
      }
    }

    while (true) {
      if (getState(BUTTON_UP_PIN) == 1) { // Si se presiona el botón de arriba
        productCost[menuIndex] += 1; // Incrementa el costo del producto seleccionado
        writeInEEPROM(productCost[menuIndex], MAX_MENU_ITEMS+menuIndex); // Escribe el costo en la memoria EEPROM
        Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar múltiples pulsaciones
      } else if (getState(BUTTON_DOWN_PIN) == 1) { // Si se presiona el botón de abajo
        productCost[menuIndex] -= 1; // Decrementa el costo del producto seleccionado
        if (productCost[menuIndex] <= 0.0){ // Si el costo es menor o igual a cero
          productCost[menuIndex] = 0.0; // Establece el costo en cero
        }
        writeInEEPROM(productCost[menuIndex], MAX_MENU_ITEMS+menuIndex); // Escribe el costo en la memoria EEPROM
        Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar múltiples pulsaciones
      }
      lcd.setCursor(11, 1); // Establece el cursor en la segunda fila, duodécima columna

      // Alternar el cursor visible/invisible cada 500 milisegundos
      if (millis() - selectButtonStartTime >= 500) {
        cursorVisible = !cursorVisible; // Alterna el valor de la variable cursorVisible
        // Muestra u oculta el cursor
        if (cursorVisible == true) { // Si el cursor es visible
          lcd.print(productCost[menuIndex], 1); // Imprime el costo del producto seleccionado
        }else{ // Si el cursor no es visible
          lcd.print("   "); // Imprime tres espacios en blanco
        }
        selectButtonStartTime = millis(); // Reinicia el temporizador
      }
      if (getState(BUTTON_MENU_PIN) == 1 || getState(BUTTON_SELECT_PIN) == 1) { // Si se presiona el botón de menú o el de selección
        lcd.print(productCost[menuIndex], 1); // Imprime el costo del producto seleccionado
        Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar múltiples pulsaciones
        break; // Sale del bucle while
      }
    }

    lcd.setCursor(0, 1); // Establece el cursor en la segunda fila, primera columna
    lcd.print("                    "); // Imprime 20 espacios en blanco

    while (true) {
      if (getState(BUTTON_UP_PIN) == 1) { // Si se presiona el botón de arriba
        pumpTime[menuIndex] += 5; // Incrementa el tiempo de bombeo del producto seleccionado
        writeInEEPROM(pumpTime[menuIndex], MAX_MENU_ITEMS*(int)2+menuIndex); // Escribe el tiempo de bombeo en la memoria EEPROM
        Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar múltiples pulsaciones
      } else if (getState(BUTTON_DOWN_PIN) == 1) { // Si se presiona el botón de abajo
        pumpTime[menuIndex] -= 5; // Decrementa el tiempo de bombeo del producto seleccionado
        if (pumpTime[menuIndex] <= 0.0){ // Si el tiempo de bombeo es menor o igual a cero
          pumpTime[menuIndex] = 0.0; // Establece el tiempo de bombeo en cero
        }
        writeInEEPROM(pumpTime[menuIndex], MAX_MENU_ITEMS*(int)2+menuIndex); // Escribe el tiempo de bombeo en la memoria EEPROM
        Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar múltiples pulsaciones
      }

      lcd.setCursor(0, 1); // Establece el cursor en la segunda fila, primera columna
      lcd.print("T: "); // Imprime la etiqueta de tiempo
      // Alternar el cursor visible/invisible cada 500 milisegundos
      if (millis() - selectButtonStartTime >= 500) {
        cursorVisible = !cursorVisible; // Alterna el valor de la variable cursorVisible
        if (cursorVisible == true) { // Si el cursor es visible
          lcd.print(pumpTime[menuIndex], 1); // Imprime el tiempo de bombeo del producto seleccionado
          lcd.print(" Seg."); // Imprime la etiqueta de segundos
        }else{ // Si el cursor no es visible
          lcd.print("   "); // Imprime tres espacios en blanco
        }
        selectButtonStartTime = millis(); // Reinicia el temporizador
      }

      // lcd.setCursor(3, 2); // Establece el cursor en la tercera columna, segunda fila
      // lcd.print(pumpTime[menuIndex], 1); // Imprime el tiempo de bombeo del producto seleccionado
      if (getState(BUTTON_MENU_PIN) == 1 || getState(BUTTON_SELECT_PIN) == 1) { // Si se presiona el botón de menú o el de selección
        lcd.print(pumpTime[menuIndex], 1); // Imprime el tiempo de bombeo del producto seleccionado
        Serial.println("delay(200)");delay(200);; // Espera 200 milisegundos para evitar múltiples pulsaciones
        break; // Sale del bucle while
      }
    }

    return false; // Retorna falso
}

/**
 * Escribe un valor flotante en la EEPROM en la dirección especificada.
 * 
 * @param valor El valor flotante que se escribirá en la EEPROM.
 * @param direccion La dirección en la EEPROM donde se escribirá el valor flotante.
 */
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
    Serial.println("Escritura en EEPROM exitosa!.");  // Muestra un mensaje en el monitor serial
  } else {
    // Mostrar un mensaje de error si la dirección no es válida
    Serial.println("Error: Dirección inválida para EEPROM o valor demasiado grande.");
  }
}

/**
 * Lee un valor flotante de la EEPROM en la dirección especificada.
 * 
 * @param direccion La dirección en la EEPROM donde se encuentra el valor flotante.
 * @return El valor flotante leído de la EEPROM.
 */
float readFromEEPROM(int direccion) {
  float valorLeido;  // Variable para almacenar el valor flotante leído de la EEPROM

  // Obtener un puntero al valor flotante para obtener sus bytes
  byte* pValor = (byte*)&valorLeido;
  direccion = direccion*sizeof(float);
  // Verificar que la dirección sea válida (entre 0 y el tamaño de la EEPROM)
  if (direccion >= 0 && direccion + sizeof(float) <= EEPROM.length()) {
    // Leer los bytes de la dirección especificada y reconstruir el valor flotante
    for (int i = 0; i < sizeof(float); i++) {
      pValor[i] = EEPROM.read(direccion + i);
    }
    Serial.println("Lectura en EEPROM exitosa!.");  // Muestra un mensaje en el monitor serial
  } else {
    // Mostrar un mensaje de error si la dirección no es válida
    Serial.println("Error: Dirección inválida para EEPROM.");
    return 0.0; // Valor de retorno predeterminado en caso de error
  }

  return valorLeido;  // Retorna el valor flotante leído de la EEPROM
}

/**
 * Carga los valores almacenados en la EEPROM en los arreglos correspondientes.
 * 
 * @param lengthData La longitud de los datos que se almacenarán en la EEPROM.
 */
void loadFromEEPROM(int lengthData){
  // Recorre todos los valores de la EEPROM y los carga en los arreglos correspondientes
  for (int i = 0; i < lengthData; i++) {
    if (readFromEEPROM(i) != 0.0f) {
      productQuantity[i] = readFromEEPROM(i);  // Carga el valor de la cantidad del producto en el arreglo productQuantity
    }
    if (readFromEEPROM(MAX_MENU_ITEMS+i) != 0.0f) {
      productCost[i] = readFromEEPROM(MAX_MENU_ITEMS+i);  // Carga el valor del costo del producto en el arreglo productCost
    }
    if (readFromEEPROM((int)2*MAX_MENU_ITEMS+i) != 0.0f) {
      pumpTime[i] = readFromEEPROM((int)2*MAX_MENU_ITEMS+i);  // Carga el valor del tiempo de bombeo en el arreglo pumpTime
    }

    Serial.print(" lt: ");  // Muestra un mensaje en el monitor serial
    Serial.print(productQuantity[i]);  // Muestra la cantidad del producto
    Serial.print(", ");  // Muestra una coma
    Serial.print(productCost[i]);  // Muestra el costo del producto
    Serial.print(", ");  // Muestra una coma
    Serial.println(pumpTime[i]);  // Muestra el tiempo de bombeo del producto
  }
  scoreHi = readFromEEPROM(MAX_MENU_ITEMS*(int)2+MAX_MENU_ITEMS*(int)2+2);
}

/**
 * Establece todos los valores de la EEPROM en cero.
 * 
 * @param lengthData La longitud de los datos que se almacenarán en la EEPROM.
 */
void setZeroEeprom(int lengthData){
  // Recorre todos los valores de la EEPROM y los establece en cero
  for (int i = 0; i < lengthData; i++) {
    writeInEEPROM(0.0, i);  // Establece el valor en cero en la posición i
    writeInEEPROM(0.0, MAX_MENU_ITEMS+i);  // Establece el valor en cero en la posición MAX_MENU_ITEMS+i
    writeInEEPROM(0.0, (int)2*MAX_MENU_ITEMS+i);  // Establece el valor en cero en la posición 2*MAX_MENU_ITEMS+i
  }
  writeInEEPROM(0, MAX_MENU_ITEMS*(int)2+MAX_MENU_ITEMS*(int)2+2); 
}

/**
 * Muestra el crédito actual en la pantalla LCD.
 * 
 * @param credit El crédito actual que se mostrará en la pantalla LCD.
 * @return true si se muestra el crédito correctamente, false en caso contrario.
 */
bool showCredit(float credit) {
  lcd.clear();  // Borra la pantalla LCD
  lcd.setCursor(0, 0);  // Establece el cursor en la primera fila
  lcd.print("Ingrese monedas");  // Muestra un mensaje para que el usuario ingrese monedas
  
  lcd.setCursor(0, 1);  // Establece el cursor en la segunda fila
  lcd.print("Credito: $");  // Muestra el símbolo de dólar
  lcd.print(credit, 2);  // Muestra el crédito actual con dos decimales
  return true;  // Retorna true para indicar que se ha mostrado el crédito correctamente
}


/**
 * Muestra el costo de un producto en la pantalla LCD.
 * 
 * @param message El mensaje que se mostrará en la pantalla LCD (opcional).
 * @param index El índice del producto cuyo costo se mostrará en la pantalla LCD.
 */
void costOfProduct(const char* message = "", int index = 0){
  lcd.clear();  // Borra la pantalla LCD
  lcd.setCursor(0, 0);  // Establece el cursor en la primera fila
  lcd.print(menuItems[index]);  // Muestra el nombre del producto
  lcd.print(" $:");  // Muestra el símbolo de dólar
  lcd.print(productCost[index], 1);  // Muestra el costo del producto con un decimal
  lcd.print(" lt");  // Muestra la unidad de medida del producto
  lcd.setCursor(2, 1);  // Establece el cursor en la segunda fila
  lcd.print(message);  // Muestra el mensaje (si se proporciona)
}

/**
 * Muestra una barra de progreso en la pantalla LCD que representa el porcentaje especificado.
 * 
 * @param percent El porcentaje de progreso que se mostrará en la barra de progreso.
 */
void displayProgressBar(int percent) {
  int progressBarWidth = map(percent, 0, 100, 0, LCD_WIDTH);  // Mapea el porcentaje a la anchura de la barra
  
  lcd.setCursor(0, 1);  // Establece el cursor en la segunda fila
  
  // Recorre cada posición de la barra de progreso y escribe un carácter en la pantalla LCD
  for (int i = 0; i < LCD_WIDTH; i++) {
    if (i < progressBarWidth) {
      lcd.write(0xFF);  // Carácter de barra llena
    } 
  }
}

/**
 * Muestra el proceso de dispensación de un producto en la pantalla.
 * 
 * @param index El índice del producto que se va a dispensar.
 */
void showProduct(int index) {
  const char* message = "Llenando...";  // Mensaje que se muestra en la pantalla mientras se dispensa el producto

  // Borra la pantalla y muestra el costo del producto
  lcd.clear();
  costOfProduct(message, index);

  activeOutput(1, index);
  // Muestra una barra de progreso mientras se dispensa el producto
  for (int percent = 0; percent <= 100; percent++) {
    displayProgressBar(percent);
    delay((int)((float)(pumpTime[index]/100.0)*1000.0));  // Espera el tiempo de dispensación del producto
  }
  activeOutput(0, index);
  service = true;
  // Espera dos segundos y muestra un mensaje de agradecimiento
  Serial.println("delay(2000)");delay(2000);;
  goodBye();
}

void goodBye(){
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Gracias ");
  lcd.setCursor(1, 1);
  lcd.print("Vuelva pronto");
  Serial.println("delay(2000)");delay(2000);;
  lcd.clear();
}

void activeOutput(int active, int index){
  if (active == 1){
    if (index == 0){
      // digitalWrite(OUTPUT_PIN_0, HIGH);  // Enciende la salida del producto 1
      setOutput(OUTPUT_PIN_0, HIGH);
    }else if(index == 1){
      // digitalWrite(OUTPUT_PIN_1, HIGH);  // Enciende la salida del producto 2
      setOutput(OUTPUT_PIN_1, HIGH);
    }else if(index == 2){
      // digitalWrite(OUTPUT_PIN_2, HIGH);  // Enciende la salida del producto 3
      setOutput(OUTPUT_PIN_2, HIGH);
    }else if(index == 3){
      // digitalWrite(OUTPUT_PIN_3, HIGH);  // Enciende la salida del producto 4
      setOutput(OUTPUT_PIN_3, HIGH);
    }else if(index == 4){
      // digitalWrite(OUTPUT_PIN_4, HIGH);  // Enciende la salida del producto 5
      setOutput(OUTPUT_PIN_4, HIGH);
    }else if(index == 5){
      // digitalWrite(OUTPUT_PIN_5, HIGH);  // Enciende la salida del producto 6
      setOutput(OUTPUT_PIN_5, HIGH);
    }else if(index == 6){
      // digitalWrite(OUTPUT_PIN_6, HIGH);  // Enciende la salida del producto 7
      setOutput(OUTPUT_PIN_6, HIGH);
    }else if(index == 7){
      // digitalWrite(OUTPUT_PIN_7, HIGH);  // Enciende la salida del producto 8
      setOutput(OUTPUT_PIN_7, HIGH);
    }
  }else if(active == 0){
    if(index == 0){
      setOutput(OUTPUT_PIN_0, LOW);  // Apaga la salida del producto 1
    }else if(index == 1){
      setOutput(OUTPUT_PIN_1, LOW);  // Apaga la salida del producto 2
    }else if(index == 2){
      setOutput(OUTPUT_PIN_2, LOW);  // Apaga la salida del producto 3
    }else if(index == 3){
      setOutput(OUTPUT_PIN_3, LOW);  // Apaga la salida del producto 4
    }else if(index == 4){
      setOutput(OUTPUT_PIN_4, LOW);  // Apaga la salida del producto 5
    }else if(index == 5){
      setOutput(OUTPUT_PIN_5, LOW);  // Apaga la salida del producto 6
    }else if(index == 6){
      setOutput(OUTPUT_PIN_6, LOW);  // Apaga la salida del producto 7
    }else if(index == 7){
      setOutput(OUTPUT_PIN_7, LOW);  // Apaga la salida del producto 8
    }
  }
}

/**
 * Muestra el estado en la pantalla en la posición especificada.
 * 
 * @param row La fila en la que se mostrará el estado en la pantalla.
 * @param col La columna en la que se mostrará el estado en la pantalla.
 * @param condition El estado que se mostrará en la pantalla (true para éxito, false para advertencia).
 */
void displayStatus(int row, int col, bool condition) {
  // Establece la posición del cursor en la pantalla
  lcd.setCursor(col, row);
  
  // Muestra el estado en la pantalla
  if (condition) {
    lcd.print("1");  // Caracter de palomita para éxito
  } else {
    lcd.print("0");  // Caracter de advertencia
  }
}

/**
 * Comprueba si la información del producto es válida y muestra el estado en la pantalla.
 * 
 * @param quantity La cantidad del producto.
 * @param price El precio del producto.
 * @param time El tiempo de dispensación del producto.
 * @param row La fila en la que se mostrará el estado en la pantalla.
 * @param col La columna en la que se mostrará el estado en la pantalla.
 */
void checkProductInfo(float quantity, float price, float time, int row, int col) {
  bool condition = false;

  // Comprueba si la cantidad, el precio y el tiempo son mayores que cero
  if (quantity > 0.0 && price > 0.0 && time > 0.0) {
    condition = true;
  }

  // Muestra el estado en la pantalla
  displayStatus(row, col, condition);
}

/**
 * Muestra el estado de la EEPROM en la pantalla.
 */
void updateShiftRegister()
{
   digitalWrite(LATCH_PIN, LOW);
   shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds);
   digitalWrite(LATCH_PIN, HIGH);
}

/**
 * Establece el estado de una salida del registro de desplazamiento.
 * 
 * @param outputNumber El número de salida del registro de desplazamiento.
 * @param status El estado de la salida del registro de desplazamiento.
 */
void setOutput(int outputNumber, bool status) 
{
  if (status) 
  {
    bitSet(leds, outputNumber); // Activa la salida
  } 
  else 
  {
    bitClear(leds, outputNumber); // Desactiva la salida
  }
  updateShiftRegister(); // Actualiza el registro de desplazamiento
}


/**
 * 
*/
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


/**
 * 
*/
int getState(int pinNumber) {
  static int estados = 0;

  if (shift.update()) { // Si hay un cambio en las entradas
    for (int i = 0; i < shift.getDataWidth(); i++){
      estados = estadoEntrada(i, shift.state(i));
    }
  }
  return (0x01&(estados>>pinNumber));
}

void ClearLCD() {
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(0, i);
    lcd.print("                    ");
  }
}


void dinoPieTraseroArriba(int pos){
    const byte* charDino[] = {CHARDINO_1, CHARDINO_2, CHARDINO_3, CHARDINO_4, CHARDINO_5T, CHARDINO_6T, CHARDINO_7T};

    byte buffer[8];
    for (int i = 0; i < 7; i++) {
        for(int j = 0; j < 8; j++) {
            buffer[j] = pgm_read_byte_near(charDino[i] + j);
        }
        lcd.createChar(i + 1, buffer);
    }

    for (int i = 0; i < 4; i++) {
        lcd.setCursor(i + pos, 2);
        lcd.write(i + 1);
    }

    for (int i = 0; i < 3; i++) {
        lcd.setCursor(i + pos, 3);
        lcd.write(i + 5);
    }
}

void dinoPieDelanteroArriba(int pos){
    const byte* charDino[] = {CHARDINO_1, CHARDINO_2, CHARDINO_3, CHARDINO_4, CHARDINO_5D, CHARDINO_6D, CHARDINO_7D};

    byte buffer[8];
    for (int i = 0; i < 7; i++) {
        for(int j = 0; j < 8; j++) {
            buffer[j] = pgm_read_byte_near(charDino[i] + j);
        }
        lcd.createChar(i + 1, buffer);
    }

    for (int i = 0; i < 4; i++) {
        lcd.setCursor(i + pos, 2);
        lcd.write(i + 1);
    }

    for (int i = 0; i < 3; i++) {
        lcd.setCursor(i + pos, 3);
        lcd.write(i + 5);
    }
}

void dinoAmbosPies(int posH = 1, int posV = 0){
    const byte* charDino[] = {CHARDINO_1, CHARDINO_2, CHARDINO_3, CHARDINO_4, CHARDINO_5, CHARDINO_6, CHARDINO_7T};

    byte buffer[8];
    for (int i = 0; i < 7; i++) {
        for(int j = 0; j < 8; j++) {
            buffer[j] = pgm_read_byte_near(charDino[i] + j);
        }
        lcd.createChar(i + 1, buffer);
    }

    for (int i = 0; i < 4; i++) {
        lcd.setCursor(i + posH, 2 - posV);
        lcd.write(i + 1);
    }

    for (int i = 0; i < 3; i++) {
        lcd.setCursor(i + posH, 3 - posV);
        lcd.write(i + 5);
    }
}

void dinoCaminar(int pos = 1, unsigned long tiempo = 50) {
  static bool estado = false;
  static unsigned long lastChange = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastChange >= tiempo) {
    lastChange = currentMillis;
    if (estado == false) {
      dinoPieDelanteroArriba(pos);
      estado = true;
    } else {
      dinoPieTraseroArriba(pos);
      estado = false;
    }
  }
}


void dinoAvanzar(unsigned long intervalo) {
  static unsigned long ultimoMovimiento = 0;
  unsigned long tiempoActual = millis();
  static int posicion = 0;

  if (tiempoActual - ultimoMovimiento >= intervalo) {
    if (posicion <= LCD_WIDTH){
      posicion++;
      lcd.clear();
    }else{
      posicion = 0;
    }
    ultimoMovimiento = tiempoActual;
  }
  dinoCaminar(posicion, 150);

}

bool dinoSaltarHigh() {
    static unsigned int temporizador1 = 0;
    const int intervalo1 = 1;
    const int intervalo2 = 5;

    if (temporizador1 == 0 || temporizador1 == intervalo1 || temporizador1 == intervalo2) {
        for (int i = 0; i < 4; i++) {
            lcd.setCursor(1, i);
            lcd.print("    ");
        }
    }

    if (temporizador1 < intervalo1) {
        dinoAmbosPies(1, 1);
        temporizador1++;
        return true;
    } else if (temporizador1 >= intervalo1 && temporizador1 < intervalo2) {
        dinoAmbosPies(1, 2);
        temporizador1++;
        return true;
    } else if (temporizador1 == intervalo2) {
        temporizador1 = 0;
    }

    return false;
}

bool dinoSaltarSmall() {
    static unsigned int temporizador1 = 0;
    const int intervalo1 = 5;

    if (temporizador1 == 0 || temporizador1 == intervalo1) {
        for (int i = 0; i < 4; i++) {
            lcd.setCursor(1, i);
            lcd.print("    ");
        }
    }

    if (temporizador1 < intervalo1) {
        dinoAmbosPies(1, 1);
        temporizador1++;
        return true;
    } else if (temporizador1 == intervalo1) {
        temporizador1 = 0;
    }

    return false;
}



int dinoSaltarObstaculo(byte typeObstaculo) {
  static bool saltoAlto = false;
  static bool saltoBajo = false;
  static int tipoSalto = 0;

  if (typeObstaculo == 1 && !saltoAlto) { 
    saltoAlto = true; 
    tipoSalto = JUMP_HIGH;
  } else if(typeObstaculo == 2 && !saltoBajo) {
    saltoBajo = true;
    tipoSalto = JUMP_LOW;
  }

  saltoAlto = saltoAlto ? dinoSaltarHigh() : false;
  saltoBajo = saltoBajo ? dinoSaltarSmall() : false;

  if(!saltoAlto && !saltoBajo) { 
   dinoCaminar(1, 2);
   tipoSalto = 0;
  }
  return tipoSalto;
}

void updateCaracteres(char* caracteres, char* caracteres2, unsigned long& ultimoMovimiento, unsigned long tiempoActual) {
    memmove(&caracteres[1], &caracteres[0], 19);
    memmove(&caracteres2[1], &caracteres2[0], 19);

    if (tiempoActual - ultimoMovimiento >= random(1500, 5000)) {
        ultimoMovimiento = tiempoActual;
        caracteres[0] = random(33, 127);
        if (random(2) == 0) {
            caracteres2[0] = caracteres[0];
            caracteres[0] = 0x20;
        }
    } else {
        caracteres[0] = 0x20;
        caracteres2[0] = 0x20;
    }
}

void writeCaracteres(int tipo_salto, char* caracteres, char* caracteres2) {
    int limit = (tipo_salto == JUMP_NULL) ? 16 : LCD_WIDTH;
    for (int i = 0; i < limit; i++) {
        if (tipo_salto == JUMP_LOW && i <= 15) {
            lcd.setCursor(LCD_WIDTH - i - 1, 2);
            lcd.write(caracteres2[i]);
        } 
        if (tipo_salto == JUMP_HIGH || i < 15) {
            lcd.setCursor(LCD_WIDTH - i - 1, 2);
            lcd.write(caracteres2[i]);
        }
        lcd.setCursor(LCD_WIDTH - i - 1, 3);
        lcd.write(caracteres[i]);
    }
}


void updateScore(int& tipo_salto, char* caracteres, char* caracteres2, int& score) {
    if ((caracteres[15] != 0x20 || caracteres2[15] != 0x20) && tipo_salto == JUMP_NULL) {
        tipo_salto = dinoSaltarObstaculo(caracteres[15] != 0x20 ? 2 : 1);
        score = (score + 1) % 100000;
    } else {
        tipo_salto = dinoSaltarObstaculo(0);
    }
}

void printScore(int scoreHi, int score) {
    char scoreHiStr[6];
    char scoreStr[6];

    lcd.setCursor(5, 0);
    lcd.print("Hi: ");
    sprintf(scoreHiStr, "%05d", scoreHi);
    lcd.print(scoreHiStr);
    lcd.print(" ");
    sprintf(scoreStr, "%05d", score);
    lcd.print(scoreStr);
}

void dynoGame() {
    static unsigned long ultimoMovimiento = 0;
    unsigned long tiempoActual = millis();
    static unsigned long lastChange2 = 0;
    unsigned long currentTime2 = millis();
    static int tipo_salto = false;
    static bool dobleAltura = false;
    static char caracteres[20] = {0x20, 0x20, 0x20, 0x20, 0x20,
                                   0x20, 0x20, 0x20, 0x20, 0x20,
                                   0x20, 0x20, 0x20, 0x20, 0x20,
                                   0x20, 0x20, 0x20, 0x20, 0x20};
    static char caracteres2[20] = {0x20, 0x20, 0x20, 0x20, 0x20,
                                    0x20, 0x20, 0x20, 0x20, 0x20,
                                    0x20, 0x20, 0x20, 0x20, 0x20,
                                    0x20, 0x20, 0x20, 0x20, 0x20};

    if (firstRun) {
        lcd.clear();
        firstRun = false;
    }

    if (currentTime2 - lastChange2 >= GAME_SPEED) {
        lastChange2 = currentTime2;

        updateCaracteres(caracteres, caracteres2, ultimoMovimiento, tiempoActual);
        writeCaracteres(tipo_salto, caracteres, caracteres2);
    }

    updateScore(tipo_salto, caracteres, caracteres2, score);
    printScore(scoreHi, score);
}

// void dynoGame() {
//     static unsigned long ultimoMovimiento = 0;
//     unsigned long tiempoActual = millis();
//     static unsigned long lastChange2 = 0;
//     unsigned long currentTime2 = millis();
//     static int tipo_salto = false;
//     static bool dobleAltura = false;

//     // Use dynamic memory allocation
//     char* caracteres = new char[20];
//     char* caracteres2 = new char[20];
//     for (int i = 0; i < 20; i++) {
//         caracteres[i] = 0x20;
//         caracteres2[i] = 0x20;
//     }

//     if (firstRun) {
//         lcd.clear();
//         firstRun = false;
//     }

//     if (currentTime2 - lastChange2 >= GAME_SPEED) {
//         lastChange2 = currentTime2;

//         updateCaracteres(caracteres, caracteres2, ultimoMovimiento, tiempoActual);
//         writeCaracteres(tipo_salto, caracteres, caracteres2);
//     }

//     updateScore(tipo_salto, caracteres, caracteres2, score);
//     printScore(scoreHi, score);

//     // Don't forget to free the memory
//     delete[] caracteres;
//     delete[] caracteres2;
// }

























// Función para mostrar tutorialMessages en el LCD
// void mostrarTutorialLCD() {
//   char buffer[100]; 

//   strcpy_P(buffer, (char*)pgm_read_word(&(tutorialMessages[0])));
//   lcd.setCursor((20 - strlen(buffer)) / 2, 0);
//   lcd.print(buffer);

//   for (int i = 1; i < sizeof(tutorialMessages) / sizeof(tutorialMessages[0]); i++) {
//     lcd.setCursor(0, i);
//     lcd.print("                "); // Limpia la línea

//     strcpy_P(buffer, (char*)pgm_read_word(&(tutorialMessages[i])));

//     // Si el mensaje es más largo de 20 caracteres, se desplaza de derecha a izquierda
//     if (strlen(buffer) > 20) {
//       for (int j = 0; j < strlen(buffer); j++) {
//         lcd.setCursor(0, i);
//         lcd.print(String(buffer).substring(j, j + 20));
//         delay(300);
//       }
//       lcd.setCursor(0, i);
//       lcd.print(String(buffer).substring(0, 20)); // Muestra la primera parte del texto
//     } else {
//       lcd.setCursor((20 - strlen(buffer)) / 2, i);
//       lcd.print(buffer);
//     }

//     // Esperar 3 segundos
//     delay(3000);
//   }
// }

//  if (millis() - startTime > TUTORIAL_WAIT_TIME * 1000) {
//       Serial.println("entro en la funcion mostrar TutorialLCD");
//       mostrarTutorialLCD();
//   } else {
//       if (currentTime != lastPrintedTime) {
//           lastPrintedTime = currentTime;
//           Serial.print("StartTime: "); Serial.println(currentTime);
//       }
//   }


// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 14342 bytes (46%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1120 bytes (54%) of dynamic memory, leaving 928 bytes for local variables. Maximum is 2048 bytes.
// IntelliSense configuration already up to date. To manually rebuild your IntelliSense configuration run "Ctrl+Alt+I"

// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 14328 bytes (46%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1120 bytes (54%) of dynamic memory, leaving 928 bytes for local variables. Maximum is 2048 bytes.

// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 14210 bytes (46%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1120 bytes (54%) of dynamic memory, leaving 928 bytes for local variables. Maximum is 2048 bytes.
// IntelliSense configuration already up to date. To manually rebuild your IntelliSense configuration run "Ctrl+Alt+I"

// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 13990 bytes (45%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1120 bytes (54%) of dynamic memory, leaving 928 bytes for local variables. Maximum is 2048 bytes.

// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 13892 bytes (45%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1162 bytes (56%) of dynamic memory, leaving 886 bytes for local variables. Maximum is 2048 bytes.

// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 13676 bytes (44%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1162 bytes (56%) of dynamic memory, leaving 886 bytes for local variables. Maximum is 2048 bytes.

// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 13748 bytes (44%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1162 bytes (56%) of dynamic memory, leaving 886 bytes for local variables. Maximum is 2048 bytes.

// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 18370 bytes (59%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1633 bytes (79%) of dynamic memory, leaving 415 bytes for local variables. Maximum is 2048 bytes.

// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 18344 bytes (59%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1621 bytes (79%) of dynamic memory, leaving 427 bytes for local variables. Maximum is 2048 bytes.

// Sketch uses 18344 bytes (59%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1621 bytes (79%) of dynamic memory, leaving 427 bytes for local variables. Maximum is 2048 bytes.

// Please see the build logs in output path: /home/nicolas/Github/ArduinoOutput
// Sketch uses 18440 bytes (60%) of program storage space. Maximum is 30720 bytes.
// Global variables use 1525 bytes (74%) of dynamic memory, leaving 523 bytes for local variables. Maximum is 2048 bytes.


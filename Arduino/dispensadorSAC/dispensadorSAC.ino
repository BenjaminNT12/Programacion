#include <Wire.h> // Biblioteca para la comunicación I2C
#include <LiquidCrystal_I2C.h> // Biblioteca para controlar la pantalla LCD
#include <EEPROM.h> // Biblioteca para acceder a la memoria EEPROM
#include <ShiftIn.h>

ShiftIn<2> shift;

// Conexión de la pantalla LCD
const int logitudLCDH = 20;
const int logitudLCDV = 4;
LiquidCrystal_I2C lcd(0x27, logitudLCDH, logitudLCDV);

// Pines para los botones
const int buttonDownPin = 0;
const int buttonUpPin = 1;
const int buttonMenuPin = 2;
const int buttonSelectPin = 3;

const int buttonProduct1Pin = 4;
const int buttonProduct2Pin = 5;
const int buttonProduct3Pin = 6;
const int buttonProduct4Pin = 7;

// pin para la ENTRADA de monedas
const int EnterCoin = 7;
// pin para la ENTRADA del hooper, contabiliza cuantas 
// monedas salen de hooper
const int outCoin = 8;

// Pines para la SALIDAS de las bombas
const int outputPin  = 0; 
const int outputPin1 = 1; 
const int outputPin2 = 2; 
const int outputPin3 = 3; 
const int outputPin4 = 4; 
const int outputPin5 = 5; 
const int outputPin6 = 6; 
const int outputPin7 = 7; 

const int dataPin  = 13;	// Data pin of 74HC595 is connected to Digital pin 13
const int latchPin = A0;	// Latch pin of 74HC595 is connected to Digital pin A0
const int clockPin = A1;	// Clock pin of 74HC595 is connected to Digital pin A1
byte leds = 0;		// Variable to hold the pattern of which LEDs are currently turned on or off

// Pines para la SALIDA de activacion del rele del hooper
const int hooper = 38; 

#define prod0button buttonDownPin
#define prod1button buttonUpPin
#define prod2button buttonMenuPin
#define prod3button buttonSelectPin
#define prod4button buttonProduct1Pin
#define prod5button buttonProduct2Pin
#define prod6button buttonProduct3Pin
#define prod7button buttonProduct4Pin

#define activaHooperSALIDA hooper
#define salidaDeMONEDAS outCoin
// #define salidaDeMONEDAS buttonProduct1Pin
// Variables para el menú
int menuIndex = 0; // Índice del elemento del menú actual
const int maxMenuItems = 8; // Número total de elementos del menú

float productQuantity[maxMenuItems] = {0.0}; // Cantidad de producto a dispensar en litros
float productCost[maxMenuItems] = {0.0}; // Costo del producto
float pumpTime[maxMenuItems] = {0.0}; // Tiempo de dispensado del producto
// bool saveVal[] = false;

const int tiempo = 400;
// const int t = 100;

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

// Crea un carácter personalizado para el dinosaurio
byte dinosaur[8] = {
  B00000,
  B00000,
  B01100,
  B01110,
  B00110,
  B01100,
  B11000,
  B00000
};



byte chardino1[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11100
};

byte chardino2[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte chardino3[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11100
};
byte chardino4[8] = {
  B10000,
  B11000,
  B11000,
  B11000,
  B00000,
  B10000,
  B00000,
  B00000
};
byte chardino5[8] = {
  B11111,
  B11111,
  B01111,
  B00111,
  B00011,
  B00011,
  B00010,
  B00011
};
byte chardino6[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B10110,
  B00010,
  B00010,
  B00011
};

byte chardino7[8] = {
  B11111,
  B11001,
  B10000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};


// Variables para el desplazamiento del mensaje
char message[] = "Dispensador..."; // Mensaje de desplazamiento
int messageLength = sizeof(message) - 1; // Longitud del mensaje sin el carácter nulo
int scrollPosition = 0; // Posición actual del desplazamiento
unsigned long scrollDelay = 100; // Retardo entre cada paso del desplazamiento
float totalCredit = 0.0; // Variable para el crédito total acumulado
bool servicio = false; // Variable para el crédito total acumulado
unsigned long startTime = 0; // Tiempo de inicio de la dispensación


// Declaración de funciones
void costOfProduct(const char*, int index);
void displayProgressBar(int percent);

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial a 115200 baudios
  shift.begin(10, 9, 11, 12);
  lcd.init(); // Inicializa la pantalla LCD
  lcd.backlight(); // Enciende la luz de fondo de la pantalla LCD
  lcd.createChar(0, customChar); // Crea un carácter personalizado en la posición 0 del conjunto de caracteres
  lcd.createChar(1, dinosaur); // Crea el carácter personalizado
  // lcd.write((byte)0);
  // Mostrar el custom char en la pantalla

  pinMode(buttonUpPin, INPUT_PULLUP); // Configura el pin del botón de subida como entrada con resistencia pull-up
  pinMode(buttonDownPin, INPUT_PULLUP); // Configura el pin del botón de bajada como entrada con resistencia pull-up
  pinMode(buttonSelectPin, INPUT_PULLUP); // Configura el pin del botón de selección como entrada con resistencia pull-up
  pinMode(buttonMenuPin, INPUT_PULLUP); // Configura el pin del botón de menú como entrada con resistencia pull-up
  pinMode(EnterCoin, INPUT); // Configura el pin de inserción de moneda como entrada
  pinMode(buttonProduct1Pin, INPUT_PULLUP); // Configura el pin del botón del producto 1 como entrada con resistencia pull-up
  pinMode(outCoin, INPUT_PULLUP); // Configura el pin del botón del producto 1 como entrada con resistencia pull-up

  pinMode(LED_BUILTIN, OUTPUT); // Configura el pin del LED incorporado como salida  

  pinMode(hooper, OUTPUT); // Configura el pin del LED como salida

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
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
    if (scrollPosition > messageLength + logitudLCDH) { // Si la posición de desplazamiento es mayor que la longitud del mensaje más logitudLCDH
      scrollPosition = 0; // Reinicia la posición de desplazamiento
    }
  }
  // setZeroEeprom(maxMenuItems);
  loadFromEEPROM(maxMenuItems); // Carga los datos de la EEPROM
  showMenu(); // Muestra el menú en la pantalla LCD
}


void loop() {

  static bool configurationMode = false; // Variable booleana estática para indicar si el dispositivo está en modo de configuración
  static bool welcomeMessage = false; // Variable booleana estática para indicar si se ha mostrado el mensaje de bienvenida
  static bool showOneTime = false; // Variable booleana estática para indicar si se ha mostrado el crédito del usuario
  static bool change = false; // Variable booleana estática para indicar si se ha mostrado el crédito del usuario
  static bool credit = false; // Variable booleana estática para indicar si el crédito del usuario es suficiente para comprar un producto
  const char* message = "Despachando..."; // Mensaje de dispensación
  bool STATE = false; // Estado del LED
  

  startTime++;
  digitalWrite(LED_BUILTIN, !STATE); // Enciende o apaga el LED
  if (getState(buttonMenuPin) == 1 && getState(buttonSelectPin) == 1) { // Si se presionan los botones de menú y selección al mismo tiempo
    configurationMode = true; // El dispositivo entra en modo de configuración
    showMenu(); // Muestra el menú en la pantalla LCD
    delay(1000); // Espera 1 segundo
    while(getState(buttonMenuPin) == 1 || getState(buttonSelectPin) == 1){;} // Espera hasta que se suelten los botones de menú y selección
    while (configurationMode) { // Mientras el dispositivo esté en modo de configuración
      showConfigurationMode(); // Muestra el modo de configuración en la pantalla LCD
      if (getState(buttonMenuPin) == 1) { // Si se presiona el botón de menú
        configurationMode = false; // El dispositivo sale del modo de configuración
        welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
        delay(200); // Espera 200 milisegundos
        break; // Sale del bucle while
      }
    }
  } else if (configurationMode == false && welcomeMessage == false && credit == false) { // Si el dispositivo no está en modo de configuración, no se ha mostrado el mensaje de bienvenida y el crédito del usuario no es suficiente para comprar un producto
      welcomeMessage = true; // Muestra el mensaje de bienvenida en la pantalla LCD
      showWelcomeMessage();
  } else if (getState(EnterCoin) == HIGH) { // Si se inserta una moneda
    totalCredit += 1.0; // Añade 1.0 al crédito total del usuario
    delay(40); // Espera 40 milisegundos
    credit = checkCredit(totalCredit, 0.0); // Verifica si el crédito es suficiente para comprar un producto
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
    servicio = false;
  } else if (getState(prod0button) == 1 && productCost[0] > 0.0f) { // Si se presiona el botón del producto 0 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    servicio = false; // Establece la variable booleana de servicio en falso
    credit = dispenceProduct(&totalCredit, productCost[0], 0); // Dispensa el producto 0 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
    change = true; // Establece la variable booleana de cambio en verdadero
  } else if (getState(prod1button) == 1 && productCost[1] > 0.0f) { // Si se presiona el botón del producto 1 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    servicio = false; // Establece la variable booleana de servicio en falso
    credit = dispenceProduct(&totalCredit, productCost[1], 1); // Dispensa el producto 1 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
    change = true; // Establece la variable booleana de cambio en verdadero
  } else if (getState(prod2button) == 1 && productCost[2] > 0.0f) { // Si se presiona el botón del producto 2 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    servicio = false; // Establece la variable booleana de servicio en falso
    credit = dispenceProduct(&totalCredit, productCost[2], 2); // Dispensa el producto 2 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
    change = true; // Establece la variable booleana de cambio en verdadero
  } else if (getState(prod3button) == 1 && productCost[3] > 0.0f) { // Si se presiona el botón del producto 3 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    servicio = false; // Establece la variable booleana de servicio en falso
    credit = dispenceProduct(&totalCredit, productCost[3], 3); // Dispensa el producto 3 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
    change = true; // Establece la variable booleana de cambio en verdadero
  } else if (getState(prod4button) == 1 && productCost[4] > 0.0f) { // Si se presiona el botón del producto 4 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    servicio = false; // Establece la variable booleana de servicio en falso
    credit = dispenceProduct(&totalCredit, productCost[4], 4); // Dispensa el producto 4 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
    change = true; // Establece la variable booleana de cambio en verdadero
  } else if (getState(prod5button) == 1 && productCost[5] > 0.0f) { // Si se presiona el botón del producto 5 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    servicio = false; // Establece la variable booleana de servicio en falso
    credit = dispenceProduct(&totalCredit, productCost[5], 5); // Dispensa el producto 5 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
    change = true; // Establece la variable booleana de cambio en verdadero
  } else if (getState(prod6button) == 1 && productCost[6] > 0.0f) { // Si se presiona el botón del producto 6 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    servicio = false; // Establece la variable booleana de servicio en falso
    credit = dispenceProduct(&totalCredit, productCost[6], 6); // Dispensa el producto 6 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
    change = true; // Establece la variable booleana de cambio en verdadero
  } else if (getState(prod7button) == 1 && productCost[7] > 0.0f) { // Si se presiona el botón del producto 7 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    servicio = false; // Establece la variable booleana de servicio en falso
    credit = dispenceProduct(&totalCredit, productCost[7], 7); // Dispensa el producto 7 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
    change = true; // Establece la variable booleana de cambio en verdadero
  }else if(credit == true && showOneTime == false){ // Si el crédito es suficiente y el crédito no se ha mostrado
  showOneTime = showCredit(totalCredit); // Muestra el crédito en la pantalla LCD y actualiza la variable booleana de crédito mostrado
  credit = checkCredit(totalCredit, 0.0); // Verifica si el crédito restante es suficiente para comprar otro producto
  
    // Si hay crédito restante, se ha solicitado cambio y se ha seleccionado el servicio
    if (totalCredit > 0.0 && change == true && servicio == true){
      showChangeMessage(); // Muestra el mensaje de cambio en la pantalla LCD
      digitalWrite(activaHooperSALIDA, HIGH); // Activa la salida del dispensador de monedas
      
      // Mientras haya crédito restante, se espera a que se retiren las monedas
      while (totalCredit > 0.0){
        if(getState(salidaDeMONEDAS) == LOW){ // Si se detecta una moneda en la salida
          totalCredit -= 1.0; // Se resta el valor de la moneda al crédito restante
          delay(200); // Se espera un tiempo para evitar contar varias veces la misma moneda
        }
      }
      
      digitalWrite(activaHooperSALIDA, LOW); // Desactiva la salida del dispensador de monedas
      showGoodbyeMessage(); // Muestra el mensaje de despedida en la pantalla LCD
      credit = checkCredit(totalCredit, 0.0); // Verifica si el crédito restante es suficiente para comprar otro producto
      change = false; // Reinicia la variable booleana de cambio solicitado
      servicio = false; // Reinicia la variable booleana de servicio seleccionado
    }
  }
 // si el contador pasa de 10000 que se muestre el dinosaurio
  if (startTime > 1000UL){
    desplazar_dino();
  }
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

/**
 * Muestra un mensaje de despedida en la pantalla LCD después de que el usuario ha realizado una compra.
 */
void showGoodbyeMessage(){
  lcd.clear(); // Limpia la pantalla LCD
  lcd.setCursor(0, 0); // Establece el cursor en la primera fila y primera columna
  lcd.print("Gracias por su"); // Muestra el mensaje "Gracias por su"
  lcd.setCursor(5, 1); // Establece el cursor en la segunda fila y sexta columna
  lcd.print("compra"); // Muestra el mensaje "compra"
  delay(2000); // Espera 2 segundos antes de continuar
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

  printLines(NULL, text, text2, NULL);
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
  delay(2000);
}

/**
 * Muestra el modo de configuración y permite al usuario navegar por los productos y acceder a la configuración de cada uno.
 * 
 * @return Devuelve un valor booleano que indica si se ha salido del modo de configuración.
 */
bool showConfigurationMode() {
  if (getState(buttonDownPin) == 1) { // Si se presiona el botón de abajo
    menuIndex = (menuIndex - 1 + maxMenuItems) % maxMenuItems; // Decrementa el índice del producto actual
    showMenu(); // Muestra el menú actualizado
    delay(200); // Espera 200 milisegundos para evitar rebotes en el botón
  } else if (getState(buttonUpPin) == 1) { // Si se presiona el botón de arriba
    menuIndex = (menuIndex + 1) % maxMenuItems; // Incrementa el índice del producto actual
    showMenu(); // Muestra el menú actualizado
    delay(200); // Espera 200 milisegundos para evitar rebotes en el botón
  } else if (getState(buttonSelectPin) == 1) { // Si se presiona el botón de selección
    delay(200); // Espera 200 milisegundos para evitar rebotes en el botón
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
      if (getState(buttonUpPin) == 1) { // Si se presiona el botón de arriba
        productQuantity[menuIndex] += 1; // Incrementa la cantidad del producto seleccionado
        writeInEEPROM(productQuantity[menuIndex], menuIndex); // Escribe la cantidad en la memoria EEPROM
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
      } else if (getState(buttonDownPin) == 1) { // Si se presiona el botón de abajo
        productQuantity[menuIndex] -= 1; // Decrementa la cantidad del producto seleccionado
        if (productQuantity[menuIndex] <= 0.0){ // Si la cantidad es menor o igual a cero
          productQuantity[menuIndex] = 0.0; // Establece la cantidad en cero
        }
        writeInEEPROM(productQuantity[menuIndex], menuIndex); // Escribe la cantidad en la memoria EEPROM
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
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
      if (getState(buttonSelectPin) == 1) { // Si se presiona el botón de selección
        lcd.print(productQuantity[menuIndex], 1); // Imprime la cantidad del producto seleccionado
        delay(1000); // Espera 1 segundo
        break; // Sale del bucle while
      }
      if (getState(buttonMenuPin) == 1) { // Si se presiona el botón de menú
        lcd.print(productQuantity[menuIndex], 1); // Imprime la cantidad del producto seleccionado
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
        return false; // Retorna falso
      }
    }

    while (true) {
      if (getState(buttonUpPin) == 1) { // Si se presiona el botón de arriba
        productCost[menuIndex] += 1; // Incrementa el costo del producto seleccionado
        writeInEEPROM(productCost[menuIndex], maxMenuItems+menuIndex); // Escribe el costo en la memoria EEPROM
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
      } else if (getState(buttonDownPin) == 1) { // Si se presiona el botón de abajo
        productCost[menuIndex] -= 1; // Decrementa el costo del producto seleccionado
        if (productCost[menuIndex] <= 0.0){ // Si el costo es menor o igual a cero
          productCost[menuIndex] = 0.0; // Establece el costo en cero
        }
        writeInEEPROM(productCost[menuIndex], maxMenuItems+menuIndex); // Escribe el costo en la memoria EEPROM
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
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
      if (getState(buttonMenuPin) == 1 || getState(buttonSelectPin) == 1) { // Si se presiona el botón de menú o el de selección
        lcd.print(productCost[menuIndex], 1); // Imprime el costo del producto seleccionado
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
        break; // Sale del bucle while
      }
    }

    lcd.setCursor(0, 1); // Establece el cursor en la segunda fila, primera columna
    lcd.print("                    "); // Imprime 20 espacios en blanco

    while (true) {
      if (getState(buttonUpPin) == 1) { // Si se presiona el botón de arriba
        pumpTime[menuIndex] += 5; // Incrementa el tiempo de bombeo del producto seleccionado
        writeInEEPROM(pumpTime[menuIndex], maxMenuItems*(int)2+menuIndex); // Escribe el tiempo de bombeo en la memoria EEPROM
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
      } else if (getState(buttonDownPin) == 1) { // Si se presiona el botón de abajo
        pumpTime[menuIndex] -= 5; // Decrementa el tiempo de bombeo del producto seleccionado
        if (pumpTime[menuIndex] <= 0.0){ // Si el tiempo de bombeo es menor o igual a cero
          pumpTime[menuIndex] = 0.0; // Establece el tiempo de bombeo en cero
        }
        writeInEEPROM(pumpTime[menuIndex], maxMenuItems*(int)2+menuIndex); // Escribe el tiempo de bombeo en la memoria EEPROM
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
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
      if (getState(buttonMenuPin) == 1 || getState(buttonSelectPin) == 1) { // Si se presiona el botón de menú o el de selección
        lcd.print(pumpTime[menuIndex], 1); // Imprime el tiempo de bombeo del producto seleccionado
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
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
    productQuantity[i] = readFromEEPROM(i);  // Carga el valor de la cantidad del producto en el arreglo productQuantity
    productCost[i] = readFromEEPROM(maxMenuItems+i);  // Carga el valor del costo del producto en el arreglo productCost
    pumpTime[i] = readFromEEPROM((int)2*maxMenuItems+i);  // Carga el valor del tiempo de bombeo en el arreglo pumpTime
    Serial.print(" lt: ");  // Muestra un mensaje en el monitor serial
    Serial.print(productQuantity[i]);  // Muestra la cantidad del producto
    Serial.print(", ");  // Muestra una coma
    Serial.print(productCost[i]);  // Muestra el costo del producto
    Serial.print(", ");  // Muestra una coma
    Serial.println(pumpTime[i]);  // Muestra el tiempo de bombeo del producto
  }
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
    writeInEEPROM(0.0, maxMenuItems+i);  // Establece el valor en cero en la posición maxMenuItems+i
    writeInEEPROM(0.0, (int)2*maxMenuItems+i);  // Establece el valor en cero en la posición 2*maxMenuItems+i
  }
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
  int progressBarWidth = map(percent, 0, 100, 0, logitudLCDH);  // Mapea el porcentaje a la anchura de la barra
  
  lcd.setCursor(0, 1);  // Establece el cursor en la segunda fila
  
  // Recorre cada posición de la barra de progreso y escribe un carácter en la pantalla LCD
  for (int i = 0; i < logitudLCDH; i++) {
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
  servicio = true;
  // Espera dos segundos y muestra un mensaje de agradecimiento
  delay(2000);
  goodBye();
}

void goodBye(){
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Gracias ");
  lcd.setCursor(1, 1);
  lcd.print("Vuelva pronto");
  delay(2000);
  lcd.clear();
}

void activeOutput(int active, int index){
  if (active == 1){
    if (index == 0){
      // digitalWrite(outputPin, HIGH);  // Enciende la salida del producto 1
      setOutput(outputPin, HIGH);
    }else if(index == 1){
      // digitalWrite(outputPin1, HIGH);  // Enciende la salida del producto 2
      setOutput(outputPin1, HIGH);
    }else if(index == 2){
      // digitalWrite(outputPin2, HIGH);  // Enciende la salida del producto 3
      setOutput(outputPin2, HIGH);
    }else if(index == 3){
      // digitalWrite(outputPin3, HIGH);  // Enciende la salida del producto 4
      setOutput(outputPin3, HIGH);
    }else if(index == 4){
      // digitalWrite(outputPin4, HIGH);  // Enciende la salida del producto 5
      setOutput(outputPin4, HIGH);
    }else if(index == 5){
      // digitalWrite(outputPin5, HIGH);  // Enciende la salida del producto 6
      setOutput(outputPin5, HIGH);
    }else if(index == 6){
      // digitalWrite(outputPin6, HIGH);  // Enciende la salida del producto 7
      setOutput(outputPin6, HIGH);
    }else if(index == 7){
      // digitalWrite(outputPin7, HIGH);  // Enciende la salida del producto 8
      setOutput(outputPin7, HIGH);
    }
  }else if(active == 0){
    if(index == 0){
      setOutput(outputPin, LOW);  // Apaga la salida del producto 1
    }else if(index == 1){
      setOutput(outputPin1, LOW);  // Apaga la salida del producto 2
    }else if(index == 2){
      setOutput(outputPin2, LOW);  // Apaga la salida del producto 3
    }else if(index == 3){
      setOutput(outputPin3, LOW);  // Apaga la salida del producto 4
    }else if(index == 4){
      setOutput(outputPin4, LOW);  // Apaga la salida del producto 5
    }else if(index == 5){
      setOutput(outputPin5, LOW);  // Apaga la salida del producto 6
    }else if(index == 6){
      setOutput(outputPin6, LOW);  // Apaga la salida del producto 7
    }else if(index == 7){
      setOutput(outputPin7, LOW);  // Apaga la salida del producto 8
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
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
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
  // int estadosActual = 0;
  static int estados = 0;

  if (shift.update()) { // Si hay un cambio en las entradas
    for (int i = 0; i < shift.getDataWidth(); i++){
      estados = estadoEntrada(i, shift.state(i));
    }
  }
  return (0x01&(estados>>pinNumber));
}



void desplazar_dino()
 {lcd.createChar(1,chardino1);
  lcd.createChar(2,chardino2);
  lcd.createChar(3,chardino3);
  lcd.createChar(4,chardino4);
  lcd.createChar(5,chardino5);
  lcd.createChar(6,chardino6);
  lcd.createChar(7,chardino7);
  for (int a=0; a<=18; a++)
  {


  if(a>=3){
  lcd.setCursor(a-3,0);
  lcd.write(1);}
  if(a>=2)
  {lcd.setCursor(a-2,0);
  lcd.write(2);}
  if(a>=1)
  {lcd.setCursor(a-1,0);
  lcd.write(3);}
  lcd.setCursor(a,0);
  lcd.write(4);
  
  if(a>=3){
  lcd.setCursor(a-3,1);
  lcd.write(5);}
  if(a>=2){
  lcd.setCursor(a-2,1);
  lcd.write(6);}
  if(a>=1){
  lcd.setCursor(a-1,1);
  lcd.write(7);}
  
  delay(tiempo);
    lcd.clear();
 }
}
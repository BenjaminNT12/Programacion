#include <Wire.h> // Biblioteca para la comunicación I2C
#include <LiquidCrystal_I2C.h> // Biblioteca para controlar la pantalla LCD
#include <EEPROM.h> // Biblioteca para acceder a la memoria EEPROM

// Conexión de la pantalla LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines para los botones
const int buttonDownPin = 2;
const int buttonUpPin = 3;
const int buttonMenuPin = 4;
const int buttonSelectPin = 5;
const int EnterCoin = 6;
const int buttonProduct1Pin = 7;

const int outputPin  = 30; 
const int outputPin1 = 31; 
const int outputPin2 = 32; 
const int outputPin3 = 33; 
const int outputPin4 = 34; 
const int outputPin5 = 35; 
const int outputPin6 = 36; 
const int outputPin7 = 37; 

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
char message[] = "Dispensador..."; // Mensaje de desplazamiento
int messageLength = sizeof(message) - 1; // Longitud del mensaje sin el carácter nulo
int scrollPosition = 0; // Posición actual del desplazamiento
unsigned long scrollDelay = 100; // Retardo entre cada paso del desplazamiento
float totalCredit = 0.0; // Variable para el crédito total acumulado

// Declaración de funciones
void costOfProduct(const char* message = "", int index = 0);
void displayProgressBar(int percent);

void setup() {
  Serial.begin(115200); // Inicializa la comunicación serial a 115200 baudios
  lcd.init(); // Inicializa la pantalla LCD
  lcd.backlight(); // Enciende la luz de fondo de la pantalla LCD
  lcd.createChar(0, customChar); // Crea un carácter personalizado en la posición 0 del conjunto de caracteres
  // lcd.write((byte)0);
  // Mostrar el custom char en la pantalla

  pinMode(buttonUpPin, INPUT_PULLUP); // Configura el pin del botón de subida como entrada con resistencia pull-up
  pinMode(buttonDownPin, INPUT_PULLUP); // Configura el pin del botón de bajada como entrada con resistencia pull-up
  pinMode(buttonSelectPin, INPUT_PULLUP); // Configura el pin del botón de selección como entrada con resistencia pull-up
  pinMode(buttonMenuPin, INPUT_PULLUP); // Configura el pin del botón de menú como entrada con resistencia pull-up
  pinMode(EnterCoin, INPUT); // Configura el pin de inserción de moneda como entrada
  pinMode(buttonProduct1Pin, INPUT_PULLUP); // Configura el pin del botón del producto 1 como entrada con resistencia pull-up

  pinMode(LED_BUILTIN, OUTPUT); // Configura el pin del LED incorporado como salida
  pinMode(outputPin, OUTPUT); // Configura el pin del LED como salida
  pinMode(outputPin1, OUTPUT); // Configura el pin del LED como salida
  pinMode(outputPin2, OUTPUT); // Configura el pin del LED como salida
  pinMode(outputPin3, OUTPUT); // Configura el pin del LED como salida
  pinMode(outputPin4, OUTPUT); // Configura el pin del LED como salida
  pinMode(outputPin5, OUTPUT); // Configura el pin del LED como salida
  pinMode(outputPin6, OUTPUT); // Configura el pin del LED como salida
  pinMode(outputPin7, OUTPUT); // Configura el pin del LED como salida
  // Mostrar el mensaje de desplazamiento
  const unsigned long duration = 3000; // Duración del mensaje de desplazamiento en milisegundos
  unsigned long startTime = millis(); // Tiempo de inicio del mensaje de desplazamiento
  totalCredit = 0.0; // Inicializa el crédito total en cero

  while (millis() - startTime < duration) { // Mientras el tiempo transcurrido sea menor que la duración del mensaje de desplazamiento
    lcd.clear(); // Borra la pantalla LCD
    lcd.setCursor(15 - scrollPosition, 0); // Establece la posición del cursor en la pantalla LCD
    lcd.print(message); // Imprime el mensaje de desplazamiento en la pantalla LCD
    lcd.setCursor(0, 1); // Establece la posición del cursor en la pantalla LCD
    lcd.print("Version 0.0.1"); // Imprime el mensaje de desplazamiento en la pantalla LCD
    delay(scrollDelay); // Espera un tiempo para el desplazamiento
    scrollPosition++; // Incrementa la posición de desplazamiento
    if (scrollPosition > messageLength + 16) { // Si la posición de desplazamiento es mayor que la longitud del mensaje más 16
      scrollPosition = 0; // Reinicia la posición de desplazamiento
    }
  }
  // setZeroEeprom(maxMenuItems);
  loadFromEEPROM(maxMenuItems); // Carga los datos de la EEPROM
  showMenu(); // Muestra el menú en la pantalla LCD
}


void loop() {
  static bool configurationMode = false; // Variable booleana estática para indicar si el dispositivo está en modo de configuración
  static bool welcomeMessage =  false; // Variable booleana estática para indicar si se ha mostrado el mensaje de bienvenida
  static bool showOneTime =  false; // Variable booleana estática para indicar si se ha mostrado el crédito del usuario
  static bool credit =  false; // Variable booleana estática para indicar si el crédito del usuario es suficiente para comprar un producto
  const char* message =  "Despachando..."; // Mensaje de dispensación
  bool STATE = false; // Estado del LED

  digitalWrite(LED_BUILTIN, !STATE); // Enciende o apaga el LED
  if (digitalRead(buttonMenuPin) == LOW && digitalRead(buttonSelectPin) == LOW) { // Si se presionan los botones de menú y selección al mismo tiempo
    configurationMode = true; // El dispositivo entra en modo de configuración
    showMenu(); // Muestra el menú en la pantalla LCD
    delay(1000); // Espera 1 segundo
    while(digitalRead(buttonMenuPin) == LOW || digitalRead(buttonSelectPin) == LOW){;} // Espera hasta que se suelten los botones de menú y selección
    while (configurationMode) { // Mientras el dispositivo esté en modo de configuración
      showConfigurationMode(); // Muestra el modo de configuración en la pantalla LCD
      if (digitalRead(buttonMenuPin) == LOW) { // Si se presiona el botón de menú
        configurationMode = false; // El dispositivo sale del modo de configuración
        welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
        delay(200); // Espera 200 milisegundos
        break; // Sale del bucle while
      }
    }
  } else if (configurationMode == false && welcomeMessage == false && credit == false) { // Si el dispositivo no está en modo de configuración, no se ha mostrado el mensaje de bienvenida y el crédito del usuario no es suficiente para comprar un producto
      welcomeMessage = true; // Muestra el mensaje de bienvenida en la pantalla LCD
      showWelcomeMessage();
  } else if (digitalRead(EnterCoin) == HIGH) { // Si se inserta una moneda
    totalCredit += 1.0; // Añade 1.0 al crédito total del usuario
    delay(40); // Espera 40 milisegundos
    credit = checkCredit(totalCredit, 0.0); // Verifica si el crédito es suficiente para comprar un producto
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
  }else if(digitalRead(prod0button) == LOW && productCost[0] > 0.0f){ // Si se presiona el botón del producto 0 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    credit = dispenceProduct(&totalCredit,productCost[0],0); // Dispensa el producto 0 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
  }else if(digitalRead(prod1button) == LOW && productCost[1] > 0.0f){ // Si se presiona el botón del producto 1 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    credit = dispenceProduct(&totalCredit,productCost[1],1); // Dispensa el producto 1 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
  }else if (digitalRead(prod2button) == LOW && productCost[2] > 0.0f) { // Si se presiona el botón del producto 2 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    credit = dispenceProduct(&totalCredit,productCost[2],2); // Dispensa el producto 2 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
  } else if (digitalRead(prod3button) == LOW && productCost[3] > 0.0f) { // Si se presiona el botón del producto 3 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    credit = dispenceProduct(&totalCredit,productCost[3],3); // Dispensa el producto 3 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
  } else if (digitalRead(prod4button) == LOW && productCost[4] > 0.0f) { // Si se presiona el botón del producto 4 y el costo del producto es mayor que 0
    welcomeMessage = false; // Reinicia la variable booleana de mensaje de bienvenida
    credit = dispenceProduct(&totalCredit,productCost[4],4); // Dispensa el producto 4 si el crédito es suficiente
    showOneTime = false; // Reinicia la variable booleana de crédito mostrado
  }else if(credit == true && showOneTime == false){ // Si el crédito es suficiente y el crédito no se ha mostrado
    showOneTime = showCredit(totalCredit); // Muestra el crédito en la pantalla LCD y actualiza la variable booleana de crédito mostrado
    credit = checkCredit(totalCredit, 0.0); // Verifica si el crédito restante es suficiente para comprar otro producto
  }
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
    showMenuCreditInsuficient(); // Muestra un mensaje en la pantalla LCD indicando que el crédito es insuficiente
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
 * Muestra un mensaje de bienvenida en la pantalla LCD.
 */
void showWelcomeMessage(){
  lcd.clear(); // Limpia la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("  Bienvenidos"); // Imprime el mensaje de bienvenida en la primera línea
  lcd.setCursor(0, 1);
  lcd.print("Ingrese monedas"); // Imprime el mensaje de instrucciones en la segunda línea
}

void showMenuCreditInsuficient(){
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Credito ");
  lcd.setCursor(2, 1);
  lcd.print("insuficiente");
  delay(2000);
}

/**
 * Muestra el modo de configuración y permite al usuario navegar por los productos y acceder a la configuración de cada uno.
 * 
 * @return Devuelve un valor booleano que indica si se ha salido del modo de configuración.
 */
bool showConfigurationMode() {
  if (digitalRead(buttonDownPin) == LOW) { // Si se presiona el botón de abajo
    menuIndex = (menuIndex - 1 + maxMenuItems) % maxMenuItems; // Decrementa el índice del producto actual
    showMenu(); // Muestra el menú actualizado
    delay(200); // Espera 200 milisegundos para evitar rebotes en el botón
  } else if (digitalRead(buttonUpPin) == LOW) { // Si se presiona el botón de arriba
    menuIndex = (menuIndex + 1) % maxMenuItems; // Incrementa el índice del producto actual
    showMenu(); // Muestra el menú actualizado
    delay(200); // Espera 200 milisegundos para evitar rebotes en el botón
  } else if (digitalRead(buttonSelectPin) == LOW) { // Si se presiona el botón de selección
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
  lcd.print("Configurar Produc"); // Imprime el título del menú
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
      if (digitalRead(buttonUpPin) == LOW) { // Si se presiona el botón de arriba
        productQuantity[menuIndex] += 1; // Incrementa la cantidad del producto seleccionado
        writeInEEPROM(productQuantity[menuIndex], menuIndex); // Escribe la cantidad en la memoria EEPROM
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
      } else if (digitalRead(buttonDownPin) == LOW) { // Si se presiona el botón de abajo
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
      if (digitalRead(buttonSelectPin) == LOW) { // Si se presiona el botón de selección
        lcd.print(productQuantity[menuIndex], 1); // Imprime la cantidad del producto seleccionado
        delay(1000); // Espera 1 segundo
        break; // Sale del bucle while
      }
      if (digitalRead(buttonMenuPin) == LOW) { // Si se presiona el botón de menú
        lcd.print(productQuantity[menuIndex], 1); // Imprime la cantidad del producto seleccionado
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
        return false; // Retorna falso
      }
    }

    while (true) {
      if (digitalRead(buttonUpPin) == LOW) { // Si se presiona el botón de arriba
        productCost[menuIndex] += 1; // Incrementa el costo del producto seleccionado
        writeInEEPROM(productCost[menuIndex], maxMenuItems+menuIndex); // Escribe el costo en la memoria EEPROM
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
      } else if (digitalRead(buttonDownPin) == LOW) { // Si se presiona el botón de abajo
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
      if (digitalRead(buttonMenuPin) == LOW || digitalRead(buttonSelectPin) == LOW) { // Si se presiona el botón de menú o el de selección
        lcd.print(productCost[menuIndex], 1); // Imprime el costo del producto seleccionado
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
        break; // Sale del bucle while
      }
    }

    lcd.setCursor(0, 1); // Establece el cursor en la segunda fila, primera columna
    lcd.print("                    "); // Imprime 20 espacios en blanco

    while (true) {
      if (digitalRead(buttonUpPin) == LOW) { // Si se presiona el botón de arriba
        pumpTime[menuIndex] += 5; // Incrementa el tiempo de bombeo del producto seleccionado
        writeInEEPROM(pumpTime[menuIndex], maxMenuItems*(int)2+menuIndex); // Escribe el tiempo de bombeo en la memoria EEPROM
        delay(200); // Espera 200 milisegundos para evitar múltiples pulsaciones
      } else if (digitalRead(buttonDownPin) == LOW) { // Si se presiona el botón de abajo
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

      lcd.setCursor(3, 2); // Establece el cursor en la tercera fila, cuarta columna
      lcd.print(pumpTime[menuIndex], 1); // Imprime el tiempo de bombeo del producto seleccionado
      if (digitalRead(buttonMenuPin) == LOW || digitalRead(buttonSelectPin) == LOW) { // Si se presiona el botón de menú o el de selección
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
  int progressBarWidth = map(percent, 0, 100, 0, 16);  // Mapea el porcentaje a la anchura de la barra
  
  lcd.setCursor(0, 1);  // Establece el cursor en la segunda fila
  
  // Recorre cada posición de la barra de progreso y escribe un carácter en la pantalla LCD
  for (int i = 0; i < 16; i++) {
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
      digitalWrite(outputPin, HIGH);  // Enciende la salida del producto 1
    }else if(index == 1){
      digitalWrite(outputPin1, HIGH);  // Enciende la salida del producto 2
    }else if(index == 2){
      digitalWrite(outputPin2, HIGH);  // Enciende la salida del producto 3
    }else if(index == 3){
      digitalWrite(outputPin3, HIGH);  // Enciende la salida del producto 4
    }else if(index == 4){
      digitalWrite(outputPin4, HIGH);  // Enciende la salida del producto 5
    }else if(index == 5){
      digitalWrite(outputPin5, HIGH);  // Enciende la salida del producto 6
    }else if(index == 6){
      digitalWrite(outputPin6, HIGH);  // Enciende la salida del producto 7
    }else if(index == 7){
      digitalWrite(outputPin7, HIGH);  // Enciende la salida del producto 8
    }
  }else if(active == 0){
    if(index == 0){
      digitalWrite(outputPin, LOW);  // Apaga la salida del producto 1
    }else if(index == 1){
      digitalWrite(outputPin1, LOW);  // Apaga la salida del producto 2
    }else if(index == 2){
      digitalWrite(outputPin2, LOW);  // Apaga la salida del producto 3
    }else if(index == 3){
      digitalWrite(outputPin3, LOW);  // Apaga la salida del producto 4
    }else if(index == 4){
      digitalWrite(outputPin4, LOW);  // Apaga la salida del producto 5
    }else if(index == 5){
      digitalWrite(outputPin5, LOW);  // Apaga la salida del producto 6
    }else if(index == 6){
      digitalWrite(outputPin6, LOW);  // Apaga la salida del producto 7
    }else if(index == 7){
      digitalWrite(outputPin7, LOW);  // Apaga la salida del producto 8
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

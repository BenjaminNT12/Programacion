// Last update: 2021-08-01 20:00:00
// video para configurar el monedero
// https://www.youtube.com/watch?v=oxiUWSNfdiY&ab_channel=ElHendri




#include "serve.h"  
#include "game.h"
#include "tutorial.h"
#include <LiquidCrystal_I2C.h> // Biblioteca para controlar la pantalla LCD
#include <EEPROM.h> // Biblioteca para acceder a la memoria EEPROM
#include <ShiftIn.h>

extern ShiftIn<2> shift;
extern LiquidCrystal_I2C lcd;

byte leds = 0;		
int menuIndex = 0;

extern const int PROD_BUTTONS[];

float productQuantity[MAX_MENU_ITEMS] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}; 
float productCost[MAX_MENU_ITEMS] = {10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0};
float pumpTime[MAX_MENU_ITEMS] = {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0}; 

// Texto para cada elemento del menú
String menuItems[] = {
  "Cloralex",
  "Pinol",
  "Maestro Lim",
  "Fabuloso",
  "Downy",
  "Mas color",
  "Roma",
  "Zote"
};

extern unsigned long startTime; // Tiempo de inicio de la dispensación
unsigned long scrollDelay = 100; // Retardo entre cada paso del desplazamiento
float totalCredit = 0.0; // Variable para el crédito total acumulado

int score = 0;  
int scoreHi = 0;

bool service = false; // Variable para el crédito total acumulado
bool firstRun = true;
bool configurationMode = false; // Variable booleana estática para indicar si el dispositivo está en modo de configuración
bool welcomeMessage = false; // Variable booleana estática para indicar si se ha mostrado el mensaje de bienvenida
bool showOneTime = false; // Variable booleana estática para indicar si se ha mostrado el crédito del usuario
bool change = false; // Variable booleana estática para indicar si se ha mostrado el crédito del usuario
bool credit = false; // Variable booleana estática para indicar si el crédito del usuario es suficiente para comprar un 
bool pendingCoin = false; // Variable booleana estática para indicar si el crédito del usuario es suficiente para comprar un
extern bool tutorialShow; // Variable booleana estática para indicar si se ha mostrado el tutorial

void resetOutputs() {
  for(int i = 0; i < 8; i++) {
    setOutput(i, false);
  }
}

void displayScrollingMessage(const String& message, int& scrollPosition, const int messageLength) {
  lcd.clear();
  lcd.setCursor(15 - scrollPosition, 0);
  lcd.print(message);
  lcd.setCursor(0, 1);
  lcd.print("Version 0.0.1");
  delay(scrollDelay);
  scrollPosition++;
  if (scrollPosition > messageLength + LCD_WIDTH) {
    scrollPosition = 0;
  }
}

void showScrollingMessage(const String& message, const int messageLength) {
  const unsigned long duration = 3000;
  unsigned long startTime2 = millis();
  int scrollPosition = 0;

  while (millis() - startTime2 < duration) {
    displayScrollingMessage(message, scrollPosition, messageLength);
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

// void handleCoin(void){
//   if (digitalRead(COIN_INPUT_PIN) == HIGH){
//     pendingCoin = true;
//   }
// }

void handleButtons() {
  if (getState(BUTTON_MENU_PIN) == 1 && getState(BUTTON_SELECT_PIN) == 1) {
    enterConfigurationMode();
  } else if (!configurationMode && !welcomeMessage && !credit) {
    welcomeMessage = true;
    showWelcomeMessage();
    Serial.println("entro en la condicion 2");
    resetScoreAndTime();
  } else if (digitalRead(COIN_INPUT_PIN) == HIGH || pendingCoin == true) {
    pendingCoin = false;
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

  const char* message1 = "Tome su cambio:";
  int startPosition1 = (20 - strlen(message1)) / 2;  // Asume que el ancho del LCD es de 20 caracteres
  lcd.setCursor(startPosition1, 1); // Establece el cursor en la primera fila
  lcd.print(message1); // Muestra el mensaje "Tome su cambio: "

  String message2 = "$: " + String(totalCredit);
  int startPosition2 = (20 - message2.length()) / 2;  // Asume que el ancho del LCD es de 20 caracteres
  lcd.setCursor(startPosition2, 2); // Establece el cursor en la segunda fila
  lcd.print(message2); // Muestra el símbolo de dólar y el valor del crédito restante como cambio
}


/**
 * Muestra un mensaje de despedida en la pantalla LCD después de que el usuario ha realizado una compra.
 */



void showGoodbyeMessage(){
  lcd.clear(); // Limpia la pantalla LCD

  const char* message1 = "Gracias por su";
  int startPosition1 = (20 - strlen(message1)) / 2;  // Asume que el ancho del LCD es de 20 caracteres
  lcd.setCursor(startPosition1, 1); // Establece el cursor en la primera fila
  lcd.print(message1); // Muestra el mensaje "Gracias por su"

  const char* message2 = "compra";
  int startPosition2 = (20 - strlen(message2)) / 2;  // Asume que el ancho del LCD es de 20 caracteres
  lcd.setCursor(startPosition2, 2); // Establece el cursor en la segunda fila
  lcd.print(message2); // Muestra el mensaje "compra"

  Serial.println("delay(2000)");
  delay(2000); // Espera 2 segundos antes de continuar
  lcd.clear();
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
  const char* text3 = "SAC de Mexico";

  printLines(text, text2, NULL, text3);
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

  int messageLength = strlen(message);
  int lcdWidth = 20;  // Asume que el ancho del LCD es de 20 caracteres
  int startPosition = (lcdWidth - messageLength) / 2;

  lcd.setCursor(startPosition, 1);  // Establece el cursor en la segunda fila
  lcd.print(message);  // Muestra el mensaje (si se proporciona)
}

/**
 * Muestra una barra de progreso en la pantalla LCD que representa el porcentaje especificado.
 * 
 * @param percent El porcentaje de progreso que se mostrará en la barra de progreso.
 */


void displayProgressBar(int percent) {
  int progressBarWidth = map(percent, 0, 100, 0, LCD_WIDTH);  // Mapea el porcentaje a la anchura de la barra
  
  lcd.setCursor(0, 2);  // Establece el cursor en la segunda fila
  
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

  const char* message1 = "Gracias";
  int startPosition1 = (20 - strlen(message1)) / 2;  // Asume que el ancho del LCD es de 20 caracteres
  lcd.setCursor(startPosition1, 1);
  lcd.print(message1);

  const char* message2 = "Vuelva pronto";
  int startPosition2 = (20 - strlen(message2)) / 2;  // Asume que el ancho del LCD es de 20 caracteres
  lcd.setCursor(startPosition2, 2);
  lcd.print(message2);

  Serial.println("delay(2000)");
  delay(2000);
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


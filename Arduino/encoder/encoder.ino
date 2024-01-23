// Declaramos las variables para los encoders
int encoder1PinA = 2;
int encoder2PinB = 3;
// Declaramos el pin de salida
const int outputPin = 12;
const int outputPin2 = 13;

// Declaramos las variables para almacenar los valores de los encoders
volatile int encoder1Pos = 0;
volatile int encoder2Pos = 0;

volatile bool interruptFlag1 = false;
volatile bool interruptFlag2 = false;

long contador = 0;

// Función de interrupción para el encoder 1
void encoder1Interrupt() {
  // Obtenemos el valor actual de los pines A y B del encoder
    encoder1Pos++;
    interruptFlag1 = true;
}

// Función de interrupción para el encoder 2
void encoder2Interrupt() {
  // Obtenemos el valor actual de los pines A y B del encoder
    encoder2Pos++;
    interruptFlag2 = true;
}

// Configuración del setup
void setup() {
  // Inicializamos el puerto serie a 9600 baudios
  Serial.begin(115200);
  // Configuramos los pines de los encoders como entradas
  pinMode(encoder1PinA, INPUT_PULLUP);
  pinMode(encoder2PinB, INPUT_PULLUP);
  // Configuramos el pin de salida
  pinMode(outputPin, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
 // Activamos las interrupciones para los encoders
  attachInterrupt(digitalPinToInterrupt(encoder1PinA), encoder1Interrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoder2PinB), encoder2Interrupt, FALLING);
}

// Bucle principal
void loop() {
  // Imprimimos los valores de los encoders
  if (interruptFlag1 == true || interruptFlag2 == true) {
    interruptFlag1 = false;
    interruptFlag2 = false;
    Serial.print("Encoder 1: ");
    Serial.print(encoder1Pos);
    Serial.print(" Encoder 2: ");
    Serial.println(encoder2Pos);
  }
  // contador++;

  // if (contador%10 == 0) {
  //   digitalWrite(outputPin, !digitalRead(outputPin));
  // }
  // if (contador%15 == 0) {
  //   digitalWrite(outputPin2, !digitalRead(outputPin2));
  // }
  // // Esperamos 1 ms
  // delay(1);
}
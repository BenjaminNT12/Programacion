#include <Wire.h> // Biblioteca para la comunicación I2C

// Definimos los pines de control del multiplexor
const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;


void setup() {
  Serial.begin(115200);
  // Configuramos los pines de control del multiplexor como salidas
  pinMode(S0, INPUT_PULLUP);
  pinMode(S1, INPUT_PULLUP);e
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);

  // Inicializamos la comunicación serial para imprimir los resultados
}

void loop() {

  // Leemos el valor de la entrada seleccionada y lo imprimimos en binario
  value0 = digitalRead(S0);
  value1 = digitalRead(S1);
  value2 = digitalRead(S2);
  value2 = digitalRead(S3);
  delay(200);
 
  // Leemos el valor de la entrada seleccionada y lo imprimimos en binario
  Serial.print(value3);
  Serial.print(value2);
  Serial.print(value1);
  Serial.print(value0);
  Serial.println();

  // Esperamos un segundo antes de volver a leer las entradas
  readMultiplexer(value0, value1, value2, value3);
}

void readMultiplexer(int value0, int value1, int value2, int value3) {

  // Determinamos cuál de las entradas se ha activado
  int input = -1;
  if (value0 == LOW && value1 == LOW && value2 == LOW && value3 == LOW) {
    input = 0;
  } else if (value0 == HIGH && value1 == LOW && value2 == LOW && value3 == LOW) {
    input = 1;
  } else if (value0 == LOW && value1 == HIGH && value2 == LOW && value3 == LOW) {
    input = 2;
  } else if (value0 == HIGH && value1 == HIGH && value2 == LOW && value3 == LOW) {
    input = 3;
  } else if (value0 == LOW && value1 == LOW && value2 == HIGH && value3 == LOW) {
    input = 4;
  } else if (value0 == HIGH && value1 == LOW && value2 == HIGH && value3 == LOW) {
    input = 5;
  } else if (value0 == LOW && value1 == HIGH && value2 == HIGH && value3 == LOW) {
    input = 6;
  } else if (value0 == HIGH && value1 == HIGH && value2 == HIGH && value3 == LOW) {
    input = 7;
  } else if (value0 == LOW && value1 == LOW && value2 == LOW && value3 == HIGH) {
    input = 8;
  } else if (value0 == HIGH && value1 == LOW && value2 == LOW && value3 == HIGH) {
    input = 9;
  } else if (value0 == LOW && value1 == HIGH && value2 == LOW && value3 == HIGH) {
    input = 10;
  } else if (value0 == HIGH && value1 == HIGH && value2 == LOW && value3 == HIGH) {
    input = 11;
  } else if (value0 == LOW && value1 == LOW && value2 == HIGH && value3 == HIGH) {
    input = 12;
  } else if (value0 == HIGH && value1 == LOW && value2 == HIGH && value3 == HIGH) {
    input = 13;
  } else if (value0 == LOW && value1 == HIGH && value2 == HIGH && value3 == HIGH) {
    input = 14;
  } else if (value0 == HIGH && value1 == HIGH && value2 == HIGH && value3 == HIGH) {
    input = 15;
  }

  // Imprimimos el resultado
  if (input != -1) {
    Serial.print("Input ");
    Serial.print(input);
    Serial.println(" activated");
  }
}
//Declaramos el pin de entrada
unsigned char boton = 5;

// Declaramos el pin de salida
const int encoderA = 3;
const int encoderB = 4;

// Declaramos las variables para almacenar los valores de los encoders
volatile int encoderAalm = 0;
volatile int encoderBalm = 0;
volatile int botonalm = 0;

// Configuración del setup
void setup() {
  // Inicializamos el puerto serie a 9600 baudios
  Serial.begin(115200);
  // Configuramos el pines como entradas
  pinMode(boton, INPUT);
  // Configuramos los pin de salida
  pinMode(encoderA, OUTPUT);
  pinMode(encoderB, OUTPUT);


// Bucle principal
void loop() {
  //leemos el valor del boton 
  botonalm = digitalRead(boton);
  // Imprimimos los valores del boton
    if (botonalm == 1){
    digitalWrite(boton, HIGH);
    delay(100);
  }
  else if (botonalm == 0){
      digitalWrite(boton, LOW);
    }
}
#define BOTON_RESET 13
#define IMPRIMIR_VALORES  7

// Declaramos las variables para los encoders
#define ENCODER1_PIN_A 2
#define ENCODER2_PIN_B 3

// Declaramos las variables para almacenar los valores de los encoders
volatile long encoder1Pos = 0;
volatile long encoder2Pos = 0;

volatile bool interruptFlag1 = false;
volatile bool interruptFlag2 = false;

// Función de interrupción para el encoder 1
void encoder1Interrupt() {
    encoder1Pos++;
    interruptFlag1 = true;
}

// Función de interrupción para el encoder 2
void encoder2Interrupt() {
    encoder2Pos++;
    interruptFlag2 = true;
}

void readButtons() {
    if(digitalRead(BOTON_RESET) == HIGH){
        encoder1Pos = 0;
        encoder2Pos = 0;
    }
    if(digitalRead(IMPRIMIR_VALORES) == HIGH){
        interruptFlag1 = false;
        interruptFlag2 = false;
        printEncoderValues();
    }
}

void printEncoderValues() {
    Serial.print("Encoder 1: ");
    Serial.print(encoder1Pos);
    Serial.print(" Encoder 2: ");
    Serial.println(encoder2Pos);
}

// Configuración del setup
void setup() {
    Serial.begin(115200);
    pinMode(ENCODER1_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER2_PIN_B, INPUT_PULLUP);
    pinMode(BOTON_RESET, INPUT);
    pinMode(IMPRIMIR_VALORES,INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER1_PIN_A), encoder1Interrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(ENCODER2_PIN_B), encoder2Interrupt, FALLING);
}

// Bucle principal
void loop() {
    readButtons();
}
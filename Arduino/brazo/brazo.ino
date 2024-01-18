// Definición de los pines
#define BR 32       // Botón derecho
#define BL 33       // Botón izquierdo
#define IN1 25      // Estado del motor 1
#define IN2 26      // Estado del motor 2
#define ENA 27      // PWM del motor
#define CHA 14      // Encoder A
#define Lr1 12      // Home
#define MAH 34      // Mandar a Home
#define HOME0 39    // Home 0
#define reset 36    // Reset
#define CHB 13      // Encoder B

// Variables para el sentido de giro
int contador0 = 0, contador1 = 1, contador = 0, contador2 = 0, contador3 = 1, contadorH, cont = 0;

// Declaración de funciones de interrupción
void Interrupt();
void Interrup();

// Variables para el control del motor
int spmr = 0;  // Velocidad del motor
float stL = 0; // Estados de los botones izquierdo y derecho
float stR = 0; // Estados de los botones izquierdo y derecho

// Variables para la lectura de Home
long lectura; // Lectura del sensor de Home
float Tension_de_trabajo = 5.0; // Tensión de trabajo del sensor
float Voltaje_R2; // Voltaje leído en el sensor

// Variables para la función Mandar a Home
bool MaH, RST, HOME; // Estados de los botones Mandar a Home, Reset y Home

// Resto del código
void setup() {
  // Inicializar la comunicación serial a 115200 baudios
  Serial.begin(115200);

  // Configurar los pines de entrada
  pinMode(BR, INPUT);    // Sentido de giro
  pinMode(BL, INPUT);    // Sentido de giro
  pinMode(CHA, INPUT);   // Entrada CHA
  pinMode(Lr1, INPUT);   // Home
  pinMode(MAH, INPUT);   // Mandar a Home
  pinMode(HOME0, INPUT); // Entrada HOME0
  pinMode(reset, INPUT); // Resetear contadores
  pinMode(CHB, INPUT);   // Entrada CHB

  // Configurar los pines de salida
  pinMode(IN1, OUTPUT);  // Estados
  pinMode(IN2, OUTPUT);  // Estados
  pinMode(ENA, OUTPUT);  // PWM

  // Apagar el motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  // Declarar variables volátiles para los contadores
  volatile int contador, contador1, contador0, contador2, contador3, contadorH, cont;
}

void loop() {
  // Lectura de Home
  lectura = 0;
  for(int i = 0; i < 5; i++){
    lectura += analogRead(Lr1);
  }
  lectura = trunc(lectura / 5);
  Voltaje_R2 = ((Tension_de_trabajo / 1023.0) * lectura) / 6.02710843373;

  // Lectura de los estados de los botones
  stR = digitalRead(BR);
  MaH = digitalRead(MAH);
  stL = digitalRead(BL);
  RST = digitalRead(reset);
  HOME = digitalRead(HOME0);

  // Inicialización de los pines del motor
  spmr = 0;
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  // Si se presiona el botón de reset
  if(RST == 1){
    contador = 0; 
    contador2 = 0;
    contador1 = 1;
    contador3 = 1;
    Serial.println("RESET");
    contador0 = 0;
  }

  // Si se presiona el botón de Mandar a Home
  if(MaH == 1){
    // Proceso de ir a la posición 0
    if(contador0 == 0){
      if(contador != contador1){
        attachInterrupt(CHA, Interrupt ,RISING);
        contador1 = contador;
        spmr = 250; 
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, HIGH);
        Interrupt;
        Serial.println("Llendo a posicion 0...");
        contador2 = 0; 
        contador3 = 1; 
        contador0 = 0;
      } else {
        contador0 = 1;
        contador = 0;
        contador1 = 1;
      }
    } 

    // Proceso de medir pasos
    if(contador0 == 1 ){
      if(contador1 != contador){
        attachInterrupt(CHA, Interrupt ,RISING);
        contador1 = contador;
        spmr = 250; 
        digitalWrite(IN1, HIGH); 
        digitalWrite(IN2, LOW);
        Interrupt;
        Serial.println("Midiendo pasos...");
      } else {
        contador0 = 3;
        contadorH = 15000;
      }    
    }

    // Proceso de ir a Home
    if(contador0 == 3){
      if(contador > -40000){
        attachInterrupt(CHA, Interrup ,RISING);
        spmr = 250; 
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, HIGH);
        Interrup;
        Serial.println("Llendo a Home...");
      } else {
        contador0 = 4; 
        Serial.println("HOME");
      }
    }
  }

  // Si se presiona el botón de Home
  if(HOME == 1){
    // Proceso de ir a la posición 0
    if(cont == 0){
      if(contador != contador1){
        attachInterrupt(CHA, Interrupt ,RISING);
        contador1 = contador;
        spmr = 250; 
        digitalWrite(IN1, HIGH); 
        digitalWrite(IN2, LOW);
        Interrupt;
        Serial.println("Llendo a posicion 0...");
        contador0 = 0;
      } else {
        cont = 1;
        contador = 0;
        contador1 = 1;
      }
    } 

    // Proceso de ir a Home
    if(cont == 1){
      if(Voltaje_R2 > 1.00){
        attachInterrupt(CHA, Interrup ,RISING);
        spmr = 250; 
        digitalWrite(IN1, LOW); 
        digitalWrite(IN2, HIGH);
        Interrup;
        Serial.println("Llendo a Home...");
      } else {
        Serial.println("HOME");
        cont = 2;
      }
    }
  }

  // Si se presiona el botón de Derecha
  if(stR == 1){
    attachInterrupt(CHA, Interrupt ,RISING);
    spmr = 250;
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    Interrupt;
    Serial.println("Derecha");
  }

  // Si se presiona el botón de Izquierda
  if(stL == 1){
    attachInterrupt(CHA, Interrup ,RISING);
    spmr = 250;
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    Interrup;
    Serial.println("Izquierda");
  }

  // Control de la velocidad del motor
  analogWrite(ENA, spmr);

  delay(1500);
}


// Esta función se llama cuando ocurre la interrupción asociada a 'Interrupt'.
// Incrementa el valor de 'contador'.
void Interrupt() {
  contador++;
}

// Esta función se llama cuando ocurre la interrupción asociada a 'Interrup'.
// Decrementa el valor de 'contador'.
void Interrup() {
  contador--;
}

// Esta función se llama cuando ocurre la interrupción asociada a 'Interrupt2'.
// Incrementa el valor de 'contador2'.
void Interrupt2() {
  contador2++;
}

// Esta función se llama cuando ocurre la interrupción asociada a 'Interrupt3'.
// Decrementa el valor de 'contador2'.
void Interrupt3() {
  contador2--;
}
//Declaramos las variables 
int estado1 = 2;
int estado2  = 3;
int estado3 = 4;

int pinled1 = 8
int pinled2 = 9
int pinled3 = 10

bool izquierda
bool home
bool derecha

void setup() {
   //Inicializamos el puerto serie a 115200 baudios
  Serial.begin(115200);
  // Configuramos los pines entradas
  pinMode(estado1, INPUT_PULLUP);
  pinMode(estado2, INPUT_PULLUP);
  pinMode(estado3, INPUT_PULLUP);

  //inicializamos el led
  pinMode(pinled1, OUTPUT);
  pinMode(pinled2, OUTPUT);
  pinMode(pinled3, OUTPUT);
}

void loop() {
  // leeemos el valor del final de carrera
    bool izquierda = digitalRead(estado1);
    bool home = digitalRead(estado2);
    bool derecha = digitalRead(estado3);


  if (izquierda == 1){
    digitalWrite(led1, HIGH); 
    } 
    else if (izquierda == 0){
      digitalWrite(pinled1, LOW);
    }
    Serial.println(izquierda);
    delay(1);

  if (home == 1){
    digitalWrite(pinled2, HIGH); 
    } 
    else if (home == 0){
      digitalWrite(pinled2, LOW);
    }
    Serial.println(home);
    delay(1);

  if (derecha == 1){
    digitalWrite(pinled3, HIGH); 
    } 
    else if (derecha == 0){
      digitalWrite(pinled3, LOW);
    }
    Serial.println(derecha);
    delay(1);

}
#include <Arduino.h> // la libreria de arduino.h para poder vincular la plataforma

// Se definen los pines 
#define BR 32 // DEFINICION DE PINES Se define la variable que permite leer el valor logico del boton Derecho
#define BL 33 // Se define la variable que permite leer el valor logico del boton Izquierdo
#define IN1 25 // Se define la variable que hace referencia al estado 1 del motor 
#define IN2 26 // Se define la variable que hace referencia al estado 2 del motor
#define ENA 27 // Se define la variable del PWM hace referencia a la entrada del puente H 
#define CHA 14 // Se define el canal de señal del enconder A 
#define Lr1 12 // Se define la variable que se encarga de leer el valor analogico del voltaje de HOME
#define MAH 34 // Se define la variable que se encarga de leer el valor logico y ejecutar HOME por medio de pasos
#define HOME0 39 // Se define la variable que lee un valor logico para realizar la secuencia de home por medio de la señal de home
#define reset 36 // Se define la variable que lee un valor logico para reescribir valores a los contadores
#define CHB 13 // Se define el canal de señal del enconder B

// Variables para el sentido de giro
int contador0 = 0, contador1 = 1, contador = 0, contador2 = 0, contador3 = 1, contadorH, cont = 0; // definicion de variables

// Declaración de funciones de interrupción
void Interrupt(); //declaracion de funcion 
void Interrup(); //declaracion de funcion 

// Variables para el control del motor
int spmr = 0; // definicion de variable de la velocidad del motor 
int stL, stR; // definicion de variable de los botones izquierdo y derecho: no puede ser flotante si las iguala con un 1

// Variables para la lectura de Home
long lectura; // Definicion de variable para la lectura del sensor de Home (dato largo)
float Tension_de_trabajo = 5.0; // definicion de variable de la tension de trabajo 
float Voltaje_R2; // definicion de variable del voltaje 

// Variables para la función Mandar a Home
bool MaH, RST, HOME; // definicion de variables 
// Resto del código...
void setup() { // Estructura del programa 
  // Inicializar la comunicación serial a 115200 baudios
  Serial.begin(115200); // Comunicacion con el ordenador a dicha velocidad

  // Configurar los pines de entrada
  // CONFIGURACION DE PINES DE ENTRADA
  pinMode(BR, INPUT);    // Configura el sentido de giro derecho como entrada 
  pinMode(BL, INPUT);    // Configura el sentido de giro izquierdo como entrada
  pinMode(CHA, INPUT);   // Configura el canal del encoder A como entrada 
  pinMode(Lr1, INPUT);   // Configura la la variable que se encarga de leer el valor analogico del voltaje de HOME
  pinMode(MAH, INPUT);   // Configura la la variable que se encarga de leer el valor analogico y ejecutar HOME por medio de pasos.
  pinMode(HOME0, INPUT); // Configura la variable que se encarga de leer el valor logico de la señal de HOME
  pinMode(reset, INPUT); // se configura la variable la cual se encarga de leer el valor logico de resetear contadores
  pinMode(CHB, INPUT);   // Configura el canal del encoder B como entrada 

  // Configurar los pines de salida
  // CONFIGURACION DE LOS PINES DE SALIDA
  pinMode(IN1, OUTPUT);  // Configura la variable que hace referencia al estado 1 del motor como salida
  pinMode(IN2, OUTPUT);  // Configura la variable que hace referencia al estado 2 del motor como salida 
  pinMode(ENA, OUTPUT);  // Configura la variable del PWM hace referencia a la entrada del puente H como salida 

  // Apagar el motor
  //DESACTIVACION DE LOS ESTADOS DEL MOTOR
  digitalWrite(IN1, LOW); //Desactiva el estado 1 del motor 
  digitalWrite(IN2, LOW); //Desactiva el estado 2 del motor

  // Declarar variables volátiles para los contadores
  int contador, contador1, contador0, contador2, contador3, contadorH, cont; // definicion de variables para los contadores
}

void loop() { //Estructura del programa 
  // Lectura de Home
  //LECTURA DE VARIABLES 
  lectura = 0; // Esta es la variable del sensor que esta inicializando a 0
  for(int i = 0; i < 5; i++){ // Funcion que tiene que estar en un rango de 0 a 5 y se tiene que repetir 5 veces  
    lectura += analogRead(Lr1); // El valor de la variable lectura suma el valor de la entrada analogica del voltaje de HOME
  }
  lectura = trunc(lectura / 5); // la variable del sensor es igual a la misma pero dividida entre 5 pero te dara como resultado un numero entero mas cercano pero no mayor.
  Voltaje_R2 = ((Tension_de_trabajo / 1023.0) * lectura) / 6.02710843373; //la variable voltaje es igual una conversion con el valor máximo que se puede almacenar en una variable de tipo entero.

  // Lectura de los estados de los botones
  //LECTURA DE PINES Y ALMACENAMIENTO
  stR = digitalRead(BR); //Lee el valor del pin digital del boton derecho para alamacenarlo en stR
  MaH = digitalRead(MAH); //Lee el valor del pin digital del boton de Mandar a HOME para almacenarlo en MaH
  stL = digitalRead(BL); //Lee el valor del pin digital del boton izquierdo para almacenarlo en stL
  RST = digitalRead(reset); //Lee el valor del pin digital que reescribe valores a los contadores para almacenarlo en RST
  HOME = digitalRead(HOME0); //Lee el valor del pin digital que realiza la secuencia de home por medio de la señal de home que se almacenara en HOME

  // Inicialización de los pines del motor
  //DESACTIVACION DE LADO IZQUIERO Y DERECHO  
  spmr = 0; //Aqui esta es la velocidada del motor la cual esta en 0
  digitalWrite(IN1, LOW); // Aqui esta desactivado el estado del motor 1 (es decir en 0v)
  digitalWrite(IN2, LOW); // Aqui esta desactivado el estado del motor 2 (es decir en 0v)

  // Si se presiona el botón de reset
  //CONDICION PARA QUE SE REALICE EL PROCESO DEL BOTON DE RESET
  if(RST == 1){ //Si el boton de reset es igual a 1 hara el siguiente proceso
    contador = 0; //lo que tenga el contador se ira a un 0 
    contador2 = 0; //lo que contenga el contador2 igual se ira a un 0 asi tenga otro numero sera igual a un 0
    contador1 = 1; //lo que tenga el contador1 sera igual a un 1 
    contador3 = 1; //lo que tenga el contador3 sera igual a un 1
    Serial.println("RESET"); //Iprimira datos al puerto serie como texto en este caso la leyenda "RESET"
    contador0 = 0; // lo que tenga el contador0 se mandara un 0
  }

  // Si se presiona el botón de Mandar a Home
  //PROCESO DEL BOTON DE MANDAR A HOME CON CONDICIONES 
  if(MaH == 1){ //si el boton de Mandar a HOME es igual a un 1 hara el siguiente proceso
    // Proceso de ir a la posición 0
    if(contador0 == 0){ //si el contador0 es igual a un 0 
      if(contador != contador1){ //si el contador es diferente al contador1 
        attachInterrupt(CHA, Interrupt ,RISING); //Se ejecuta una interrupcion por medio del canal A del encoder quien recibira la señal
        contador1 = contador; //El valor que tenga el contador1 sera igual al contador
        spmr = 250; // Esta es la velocidad del motor que esta igualada a 250
        digitalWrite(IN1, LOW); //Se desactiva el estado del motor 1
        digitalWrite(IN2, HIGH); // Se activa el estado del motor 2
        Interrupt; // Se ejecuta una interrupcion que va ir incrementando 
        Serial.println("Llendo a posicion 0..."); //Iprimira datos al puerto serie como texto en este caso la leyenda "llendo a posicion 0..."
        contador2 = 0; //lo que tenga el contador2 se ira a un 0
        contador3 = 1; //igual lo que contenga el contador3 sera igual a un 1
        contador0 = 0; //lo que tenga el contador0 sera igual a un 0 
      } else { //si no se cumple lo anterior entonces, hara o siguiente
        contador0 = 1; //el valor que tenga el contador0 se ira a un valor de 1
        contador = 0; //el valor que tenga el contador se ira a al valor de un 0
        contador1 = 1; //el valor que tenga el contador1 tendra un valor de un 1
      }
    } 

    // Proceso de medir pasos
    //CONDICIONES CON LAS QUE SE DEBE DE REALIZAR EL PROCESO DE MEDIR PASOS
    if(contador0 == 1 ){ //si el contador0 es igual a un 1 se hara el proceso para medir pasos
      if(contador1 != contador){ //igual si el contador1 es diferente al contador
        attachInterrupt(CHA, Interrupt ,RISING); //se ejecuta una interrumpcion por medio del canal A que recibira la señal
        contador1 = contador; //el valor del contador1 sera igual al valor del contador
        spmr = 250; //Esta es la velocidad del motor que esta igualada a 250
        digitalWrite(IN1, HIGH); //se activa el estado del motor 1
        digitalWrite(IN2, LOW); //se desactiva el estado del motor 2
        Interrupt; //Ejecuta una interrupcion la cual hace que el contador vaya incrementando
        Serial.println("Midiendo pasos..."); //Iprimira datos al puerto serie como texto en este caso la leyenda "Midiendo pasos..."
      } else { //si no se cumple lo anterior entonces
        contador0 = 3; //el valor del contador0 sera igual a un 3
        contadorH = 15000; //el valor del contadorH sera igual a 150000 (que es un promedio de los pasos)
      }    
    }

    // Proceso de ir a Home
    //PROCESO PARA IR A HOME CON DICHAS CONDICIONES 
    if(contador0 == 3){ //si el contador0 es igual a un 3 hara el proceso de ir a HOME
      if(contador > -32768){ //si el contador es mayor a -32768 (que es el rango del contador)
        attachInterrupt(CHA, Interrup ,RISING); //se ejecuta una interrumpcion por medio del canal A que recibira la señal
        spmr = 250; //La velocidad del motor es igual a 250
        digitalWrite(IN1, LOW); //se desactiva el estado del motor 1
        digitalWrite(IN2, HIGH); //se activa el estado del motor 2
        Interrup; //Ejecuta una interrupcion la cual hace que el contador sea decremental
        Serial.println("Llendo a Home..."); //Iprimira datos al puerto serie como texto en este caso la leyenda "llendo a Home..."
      } else { //si no hace el proceso anterior entonces
        contador0 = 4; //el valor del contador0 sera igual a un 4
        Serial.println("HOME"); //Iprimira datos al puerto serie como texto en este caso la leyenda "HOME"
      }
    }
  }

  // Si se presiona el botón de Home
  //PROCESO A REALIZAR DE ACUERDO A LAS COMDICIONES QUE SE PRESENTAN
  if(HOME == 1){ //Si el boton de HOME es igual a 1 entonces hara lo siguiente.
    // Proceso de ir a la posición 0
    if(cont == 0){ //igual si el cont es igual a 0 
      if(contador != contador1){ //si el contador es diferente al contador1
        attachInterrupt(CHA, Interrupt ,RISING); //se ejecuta una interrumpcion por medio del canal A que recibira la señal
        contador1 = contador; //el valor del contador1 sera igual al contador 
        spmr = 250; //la velocidad del motor esta en 250
        digitalWrite(IN1, HIGH); //se activa el estado del motor 1
        digitalWrite(IN2, LOW); //se desactiva el estado del motor 2
        Interrupt; //Ejecuta una interrupcion la cual hace que el contador sea incremental
        Serial.println("Llendo a posicion 0..."); //Iprimira datos al puerto serie como texto en este caso la leyenda "llendo a posicion 0..."
        contador0 = 0; //el valor del contador0 se igualara a 0
      } else { //si no cumple la funcion anterior entonces hara lo siguiente
        cont = 1; //el valor del cont se igualara a 1
        contador = 0; //el valor del contador se igualara a 0
        contador1 = 1; //el valor del contador 1 se igualara a 1
      }
    } 

    // Proceso de ir a Home
    //PROCESO DE IR A HOME CON LAS SIGUIENTES CONDICIONES 
    if(cont == 1){ //si el cont es igual a 1 entonces hara el siguiente proceso
      if(Voltaje_R2 > 1.00){ //si el voltaje de R2 es mayor a 1 entonces:
        attachInterrupt(CHA, Interrup ,RISING); //se ejecuta una interrumpcion por medio del canal A que recibira la señal
        spmr = 250; //la velocidad del motor estara en 250
        digitalWrite(IN1, LOW); //se desactiva el estado del motor 1
        digitalWrite(IN2, HIGH); //se activa el estado del motor 2
        Interrup; //Ejecuta una interrupcion la cual hace que el contador sea decremental
        Serial.println("Llendo a Home..."); //Iprimira datos al puerto serie como texto en este caso la leyenda "llendo a Home..."
      } else { //si no se cumple lo antyerior entonces hara lo siguiente
        Serial.println("HOME"); //Iprimira datos al puerto serie como texto en este caso la leyenda "HOME"
        cont = 2; //el valor del contador sera igual a un 2
      }
    }
  }

  // Si se presiona el botón de Derecha
  //PROCESO DE QUE SI SE PRECIOSA EL BOTON DERECHO SE REALIZARA DE ACUERDO A LAS CONDICIONES
  if(stR == 1){ //si el boton de la derecha es igual a un 1 
    attachInterrupt(CHA, Interrupt ,RISING); //se ejecuta una interrumpcion por medio del canal A que recibira la señal
    spmr = 250; //la velocidad del motor esta en 250 
    digitalWrite(IN1, HIGH); //se activa el estado del motor 1
    digitalWrite(IN2, LOW); //se desactiva el estado del motor 2
    Interrupt; //Ejecuta una interrupcion la cual hace que el contador sea incremental
    Serial.println("Derecha"); //Iprimira datos al puerto serie como texto en este caso la leyenda "Derecha"
  }

  // Si se presiona el botón de Izquierda
  //DE ACUERDO A LAS COMDICIONES QUE SE PRESENTAN SI SE PRESIONA EL BOTON IZQUIERDO SE REALIZARA EL PROCESO
  if(stL == 1){ //si el boton de la izquierda es igual a un 1
    attachInterrupt(CHA, Interrup ,RISING); //se ejecuta una interrumpcion por medio del canal A que recibira la señal
    spmr = 250; //la velocidad del motor esta en 250
    digitalWrite(IN1, LOW); //se desactiva el estado del motor 1
    digitalWrite(IN2, HIGH); //se activa el estado del motor 2
    Interrup; //Ejecuta una interrupcion la cual hace que el contador sea decremental
    Serial.println("Izquierda"); //Iprimira datos al puerto serie como texto en este caso la leyenda "Izquierda"
  }

  // Control de la velocidad del motor
  //GENERA UNA SEÑAL DE FRECUENCIA PARA ACCIONAR EL MOTOR A CIERTA VELOCIDAD CON UN RETARDO 
  analogWrite(ENA, spmr); //Esribir el valor analogico de la velocidad del motor al pin de la entrada del puente H

  delay(1500); //Un retardo de 1.5seg
}

//INTERRUPCIONES QUE GENERAN EL INCREMENTO O DECREMENTO EN LOS CONTADORES
// Esta función se llama cuando ocurre la interrupción asociada a 'Interrupt'.
// Incrementa el valor de 'contador'.
void Interrupt() { //interrupcion incremental
  contador++; //Suma una unidad de manera constante
}

// Esta función se llama cuando ocurre la interrupción asociada a 'Interrup'.
// Decrementa el valor de 'contador'.
void Interrup() { //interrupcion decremental 
  contador--; //resta una unidad de manera contante
}

// Esta función se llama cuando ocurre la interrupción asociada a 'Interrupt2'.
// Incrementa el valor de 'contador2'.
void Interrupt2() { //interrupcion incremental
  contador2++; //Suma una unidad de manera constante
}

// Esta función se llama cuando ocurre la interrupción asociada a 'Interrupt3'.
// Decrementa el valor de 'contador2'.
void Interrupt3() { //interrupcion decremental
  contador2--; //Resta una unidad de manera constante
}
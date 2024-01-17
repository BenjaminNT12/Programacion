#include <SoftwareSerial.h>

// Configura los pines de RX y TX para la comunicación con el SIM800L
SoftwareSerial sim800l(5, 4); // RX, TX

void setup() {
  // Inicia la comunicación serial con el SIM800L y el monitor serial
  sim800l.begin(9600);
  Serial.begin(9600);

  // Espera a que el módulo SIM800L esté listo
  delay(1000);

  // Configura el módulo SIM800L para enviar SMS
  sim800l.print("AT+CMGF=1\r");
  delay(1000);
}

void loop() {
  // Nada en el loop principal
    sendSMS("771", const char* message) {
}

void sendSMS(const char* phoneNumber, const char* message) {
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.print("\"\r");
  delay(1000);
  
  sim800l.print(message);
  delay(1000);
  
  sim800l.print((char)26);  // Código ASCII de Ctrl+Z
  delay(1000);
}
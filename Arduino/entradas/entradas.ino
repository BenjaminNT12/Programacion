#include <ShiftIn.h>

ShiftIn<2> shift;

void setup() {
  Serial.begin(9600);
  shift.begin(10, 9, 11, 12);
  Serial.print("Hola \n"); // get state of button i
}



// int estadoEntrada(int id, int estado) { // almacenal el estado del sensor en la variable StateSLAVE[x].val
//     static unsigned char retorno = 0;

//     for (unsigned char i = 0, unsigned char C1 = 0; i < 8; i = i + 8) {
//         if (id > i && id <= (i + 8)) {
//             if (estado == 1){
//                 retorno |= (0x01 << id);
//             }else {
//                 retorno &= (0xFF^(0x01 << id));
//             }
//         }
//         C1++;
//     }
//     return retorno;
// }

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






// void displayValues() {
//   int estados = 0;
//   if (shift.update()) { // Si hay un cambio en las entradas
//     for (int i = 0; i < shift.getDataWidth(); i++){
//       estados = estadoEntrada(i, shift.state(i));
//     }
//     Serial.print(estados, BIN);
//   }
// }

int getState(int pinNumber) {
  // int estadosActual = 0;
  static int estados = 0;

  if (shift.update()) { // Si hay un cambio en las entradas
    for (int i = 0; i < shift.getDataWidth(); i++){
      estados = estadoEntrada(i, shift.state(i));
    }
  }
  return (0x01&(estados>>pinNumber));
}

void loop() {
  if (getState(0) == 1) {
    Serial.print("pulsado 1 on \n"); // get state of button i
    delay(500);
  }
  if (getState(1) == 1) {
    // Serial.print(getState(1));
    Serial.print("pulsado 2 error \n"); // get state of button i
    delay(100);
  }
  if (getState(2) == 1) {
    Serial.print("pulsado 3 error \n"); // get state of button i
    delay(100);
  }
  if (getState(3) == 1) {
    Serial.print("pulsado 4 error \n"); // get state of button i
    delay(100);
  }
  if (getState(4) == 1) {
    Serial.print("pulsado 5 error \n"); // get state of button i
    delay(100);
  }
  if (getState(5) == 1) {
    Serial.print("pulsado 6 error \n"); // get state of button i
    delay(100);
  }
  if (getState(6) == 1) {
    Serial.print("pulsado 7 error \n"); // get state of button i
    delay(100);
  }
  if (getState(7) == 1){
    Serial.print("pulsado 8 error \n"); // get state of button i
    delay(100);
  }
}

// bool checkPinChange(int pinNumber) {
//   if (shift.update()) { // Si hay un cambio en las entradas
//     Serial.print("cambio \n");
//     return shift.state(pinNumber);
//   }
// }
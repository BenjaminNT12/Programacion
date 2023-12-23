#include <ShiftIn.h>

ShiftIn<2> shift;

void setup() {
  Serial.begin(9600);
  // declare pins: pLoadPin, clockEnablePin, dataPin, clockPin
  shift.begin(8, 9, 11, 12);
  Serial.print("Hola \n"); // get state of button i
}

void displayValues() {
  // print out all 8 buttons
  for (int i = 0; i < shift.getDataWidth(); i++)
    Serial.print( shift.state(i) ); // get state of button i
  Serial.println();
}

void loop() {
  if (shift.update()) // read in all values. returns true if any button has changed
    displayValues();
  delay(500);
}

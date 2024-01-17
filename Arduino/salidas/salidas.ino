#include <Wire.h>

int dataPin = 13;	// Data pin of 74HC595 is connected to Digital pin 13
int latchPin = A0;	// Latch pin of 74HC595 is connected to Digital pin A0
int clockPin = A1;	// Clock pin of 74HC595 is connected to Digital pin A1

byte leds = 0;		// Variable to hold the pattern of which LEDs are currently turned on or off

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{
  delay(500);
  for (int i = 0; i < 8; i++)	// Turn all the LEDs ON one by one.
  {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(100);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(100);   
  }
//   setOutput(1, true);
//   setOutput(2, true);
//   delay(500);
//   setOutput(1, false);
//   delay(500);
//   setOutput(2, false);
  // for(int i=0; i<8; i++)
  // {
  //   setOutput(i, true);
  //   delay(500);
  //   setOutput(i, false);
  // }

}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void setOutput(int outputNumber, bool status) 
{
  if (status) 
  {
    bitSet(leds, outputNumber); // Activa la salida
  } 
  else 
  {
    bitClear(leds, outputNumber); // Desactiva la salida
  }
  updateShiftRegister(); // Actualiza el registro de desplazamiento
}
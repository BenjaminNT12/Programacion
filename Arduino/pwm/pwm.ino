const int analogOutPin = 11;
const int ledPIN = 5;
byte outputValue = 0;  

void setup()
{  
   Serial.begin(9600);         // Iniciar puerto serie
   pinMode(ledPIN , OUTPUT); 

   bitSet(DDRB, 5);      // LED pin (13)
   bitSet(PCICR, PCIE0);       // enable pin change interrupts on bank 0  
   bitSet(PCMSK0, PCINT3);     // enable PCINT3 (PB3) pin change interrupt 
}

void loop() 
{
   if (Serial.available()>0)  // Si hay datos disponibles
   {
      if(outputValue >= '0' && outputValue <= '9')
      {
         outputValue = Serial.read();  // Leemos la opción
         outputValue -= '0';    // Restamos '0' para convertir a un número
         outputValue *= 25;    // Multiplicamos x25 para pasar a una escala 0 a 250
         analogWrite(ledPIN , outputValue);
      }
   }
}  

ISR(PCINT0_vect)
{
   if(bitRead(PINB, 3))
   { 
      bitSet(PORTB, 5);   // LED on 
   }
   else
   { 
      bitClear(PORTB, 5); // LED off  
   } 
}
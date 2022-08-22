#include <mega328p.h>
#include <delay.h>
#include <stdlib.h>

// Declare your global variables here


#define LED1 PORTD.7
#define LED2 PORTD.6
#define LED3 PORTD.5
#define LED4 PORTD.4

#define BUTTON1 PIND.2
#define BUTTON2 PIND.3
#define BUTTON3 PINB.0
#define BUTTON4 PINB.1

#define START PINB.2

void resetVariables(void);
void toggleLed(unsigned char nToggle, unsigned char nLed, int _delay);
void correcto(void);
void incorrecto(void);
void StartGAME(void);

char enc1 = 0;
char enc2 = 0;
char enc3 = 0;
char enc4 = 0;

char ContadorButton1 = 0;
char ContadorButton2 = 0;
char ContadorButton3 = 0;
char ContadorButton4 = 0;

char randButton1 = 0;
char randButton2 = 0;
char randButton3 = 0;
char randButton4 = 0;

void main(void)
{

int __delay = 500;
char flag = 0;

int counter = 0 ;

#pragma optsize-
CLKPR = (1<<CLKPCE);
CLKPR = (0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

DDRB   = 0b00000000;
PORTB  = 0b00000111;
DDRC   = 0b00000000;
PORTC  = 0b00000000;
DDRD   = 0b11110000;
PORTD  = 0b00001100;

TCCR0A = 0b00000000;
TCCR0B = 0b00000000;
TCNT0  = 0x00;
OCR0A  = 0x00;
OCR0B  = 0x00;

TCCR1A = 0b00000000;
TCCR1B = 0b00000000;
TCNT1H = 0x00;
TCNT1L = 0x00;
ICR1H  = 0x00;
ICR1L  = 0x00;
OCR1AH = 0x00;
OCR1AL = 0x00;
OCR1BH = 0x00;
OCR1BL = 0x00;

ASSR   = (0<<EXCLK) | (0<<AS2);
TCCR2A = (0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
TCCR2B = (0<<WGM22) | (0<<CS22) | (0<<CS21) | (0<<CS20);
TCNT2  = 0x00;
OCR2A  = 0x00;
OCR2B  = 0x00;


TIMSK0 = (0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);
TIMSK1 = (0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);
TIMSK2 = (0<<OCIE2B) | (0<<OCIE2A) | (0<<TOIE2);
EICRA  = (0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
EIMSK  = (0<<INT1) | (0<<INT0);
PCICR  = (0<<PCIE2) | (0<<PCIE1) | (0<<PCIE0);

UCSR0B = (0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (0<<RXEN0) | (0<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);

ACSR   = (1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
ADCSRB = (0<<ACME);
DIDR1  = (0<<AIN0D) | (0<<AIN1D);
ADCSRA = (0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
SPCR   = (0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);
TWCR   = (0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);




while (1){
        counter++;

        if (START == 1){
            srand(counter);
            randButton1 = 0x03 & rand();
            delay_us(5);
            randButton2 = 0x03 & rand();
            delay_us(2);
            randButton3 = 0x03 & rand();
            delay_us(9);
            randButton4 = 0x03 & rand();

            StartGAME();
            flag = 1;
        }while(START == 1){};


        if(randButton1 != 0 && enc1 == 0 ){
            toggleLed(randButton1,1 , __delay);
            enc1 = 1;
            delay_ms(200);
        }


        if(randButton2 != 0 && enc2 == 0 ){
            toggleLed(randButton2, 2, __delay);
            enc2 = 1;
            delay_ms(200);
        }


        if(randButton3 != 0 && enc3 == 0 ){
            toggleLed(randButton3, 3, __delay);
            enc3 = 1;
        }


        if(randButton4 != 0 && enc4 == 0 ){
            toggleLed(randButton4, 4, __delay);
            enc4 = 1;
        }

        if (BUTTON1 == 1 && flag == 1){
            ContadorButton1++;
            toggleLed(1 , 1, 100);
        }else{
            LED1 = 0;
        }while(BUTTON1 == 1){};

        if (BUTTON2 == 1 && flag == 1){
            ContadorButton2++;
            toggleLed(1 , 2, 100);
        }else{
            LED2 = 0;
        }while(BUTTON2 == 1){};

        if (BUTTON3 == 1 && flag == 1){
            ContadorButton3++;
            toggleLed(1 , 3, 100);
        }else{
            LED3 = 0;
        }while(BUTTON3 == 1){};

        if (BUTTON4 == 1 && flag == 1){
            ContadorButton4++;
            toggleLed(1 , 4, 100);
        }else{
            LED4 = 0;
        }while(BUTTON4 == 1){};

        if ((ContadorButton1 == randButton1) && (ContadorButton2 == randButton2) && (ContadorButton3 == randButton3) && (ContadorButton4 == randButton4) && flag != 0 ){
            correcto();
            resetVariables();
            flag = 0;
        }

        if ((ContadorButton1 > randButton1) || (ContadorButton2 > randButton2) || (ContadorButton3 > randButton3) || (ContadorButton4 > randButton4) ){
            incorrecto();
            resetVariables();

        }
    }
}


void correcto(void){
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    delay_ms(2000);
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
}



void incorrecto(void){
    toggleLed(1, 1, 100);
    toggleLed(1, 2, 100);
    toggleLed(1, 3, 100);
    toggleLed(1, 4, 100);
    toggleLed(1, 4, 100);
    toggleLed(1, 3, 100);
    toggleLed(1, 2, 100);
    toggleLed(1, 1, 100);
}

void resetVariables(void){
    ContadorButton1 = 0;
    ContadorButton2 = 0;
    ContadorButton3 = 0;
    ContadorButton4 = 0;   

    randButton1 = 0;
    randButton2 = 0;
    randButton3 = 0;
    randButton4 = 0;

    enc1 = 0;
    enc2 = 0;
    enc3 = 0;
    enc4 = 0;
}


void toggleLed(unsigned char nToggle, unsigned char nLed, int _delay){
    unsigned char i = 0;


    switch (nLed){
           case 1:
                for (i = 0 ;i < nToggle; i++){
                    LED1 = 1;
                    delay_ms(_delay);
                    LED1 = 0;
                    delay_ms(_delay);
                }
           break;

           case 2:
                for (i = 0 ;i < nToggle; i++){
                    LED2 = 1;
                    delay_ms(_delay);
                    LED2 = 0;
                    delay_ms(_delay);
                }
           break;

           case 3:
                for (i = 0 ;i < nToggle; i++){
                    LED3 = 1;
                    delay_ms(_delay);
                    LED3 = 0;
                    delay_ms(_delay);
                }
           break;

           case 4:
                for (i = 0 ;i < nToggle; i++){
                    LED4 = 1;
                    delay_ms(_delay);
                    LED4 = 0;
                    delay_ms(_delay);
                }
           break;
    }
}


void StartGAME(void){
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
    delay_ms(500);
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    delay_ms(2000);
}

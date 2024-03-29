
#ifndef ARDUINO_GAME_H
#define ARDUINO_GAME_H
#include <Arduino.h>

#define JUMP_HIGH 1
#define JUMP_LOW 2
#define JUMP_NULL 0

const int LCD_WIDTH = 20;
const int LCD_HEIGHT = 4;
const int GAME_SPEED = 200;
const int detectOsbtacleH = 6;
const int detectOsbtacleL = 5;
const int duracionSaltoH = 5;
const int duracionSaltoL = 4;


const PROGMEM byte CHARDINO_1[8] = {0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x18, 0x1C};
const PROGMEM byte CHARDINO_2[8] = {0x00, 0x01, 0x01, 0x01, 0x01, 0x03, 0x0F, 0x1F};
const PROGMEM byte CHARDINO_3[8] = {0x1F, 0x17, 0x1F, 0x1F, 0x1C, 0x1F, 0x1C, 0x1C};
const PROGMEM byte CHARDINO_4[8] = {0x10, 0x18, 0x18, 0x18, 0x00, 0x10, 0x00, 0x00};
const PROGMEM byte CHARDINO_5[8] = {0x1F, 0x1F, 0x0F, 0x07, 0x03, 0x03, 0x02, 0x03};
const PROGMEM byte CHARDINO_6[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x16, 0x02, 0x02, 0x03};
const PROGMEM byte CHARDINO_6T[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x06, 0x12, 0x02, 0x03};
const PROGMEM byte CHARDINO_5T[8] = {0x1F, 0x1F, 0x0F, 0x07, 0x03, 0x03, 0x00, 0x00};
const PROGMEM byte CHARDINO_7T[8] = {0x1F, 0x19, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00};
const PROGMEM byte CHARDINO_5D[8] = {0x1F, 0x1F, 0x0F, 0x07, 0x03, 0x03, 0x02, 0x03};
const PROGMEM byte CHARDINO_6D[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x16, 0x03, 0x00, 0x00};
const PROGMEM byte CHARDINO_7D[8] = {0x1F, 0x19, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00};


void dinoPieTraseroArriba(int pos);
void dinoPieDelanteroArriba(int pos);
void dinoAmbosPies(int posH, int posV);
void dinoCaminar(int pos, unsigned long tiempo);
void dinoAvanzar(unsigned long intervalo);
bool dinoSaltarHigh(unsigned char duracionSalto);
bool dinoSaltarSmall(unsigned char duracionSalto);
int dinoSaltarObstaculo(byte typeObstaculo);
void updateCaracteres(char* caracteres, char* caracteres2, unsigned long& ultimoMovimiento, unsigned long tiempoActual);
void writeCaracteres(int tipo_salto, char* caracteres, char* caracteres2);
void updateScore(int& tipo_salto, char* caracteres, char* caracteres2, unsigned long& score,
                 unsigned char detectObstacleH, unsigned char detectObstacleL);
void printScore(int scoreHi, int score);
void dynoGame();
void createFirstDino();

#endif

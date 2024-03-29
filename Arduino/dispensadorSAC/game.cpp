#include "game.h"  
#include <LCD_I2C.h> // Biblioteca para controlar la pantalla LCD

extern LCD_I2C lcd;
extern unsigned long score;
extern unsigned long scoreHi;
extern bool firstRun;

void dinoPieTraseroArriba(int pos){
    const byte* charDino[] = {CHARDINO_1, CHARDINO_2, CHARDINO_3, CHARDINO_4, CHARDINO_5T, CHARDINO_6T, CHARDINO_7T};

    byte buffer[8];
    for (int i = 4; i < 7; i++) {
        for(int j = 0; j < 8; j++) {
            buffer[j] = pgm_read_byte_near(charDino[i] + j);
        }
        lcd.createChar(i + 1, buffer);
    }

    for (int i = 0; i < 4; i++) {
        if(i == 0)lcd.setCursor(i + pos, 2);
        lcd.write(i + 1);
    }

    for (int i = 0; i < 3; i++) {
        if(i == 0)lcd.setCursor(i + pos, 3);
        lcd.write(i + 5);
    }
}

void dinoPieDelanteroArriba(int pos){
    const byte* charDino[] = {CHARDINO_1, CHARDINO_2, CHARDINO_3, CHARDINO_4, CHARDINO_5D, CHARDINO_6D, CHARDINO_7D};

    byte buffer[8];
    for (int i = 4; i < 7; i++) {
        for(int j = 0; j < 8; j++) {
            buffer[j] = pgm_read_byte_near(charDino[i] + j);
        }
        lcd.createChar(i + 1, buffer);
    }
    for (int i = 0; i < 4; i++) {
        if(i == 0)lcd.setCursor(i + pos, 2);
        lcd.write(i + 1);
    }

    for (int i = 0; i < 3; i++) {
        if(i == 0)lcd.setCursor(i + pos, 3);
        lcd.write(i + 5);
    }
}

void createFirstDino(){
    const byte* charDino[] = {CHARDINO_1, CHARDINO_2, CHARDINO_3, CHARDINO_4, CHARDINO_5, CHARDINO_6, CHARDINO_7T};

    byte buffer[8];
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 8; j++) {
            buffer[j] = pgm_read_byte_near(charDino[i] + j);
        }
        lcd.createChar(i + 1, buffer);
    }
}

void dinoAmbosPies(int posH = 1, int posV = 0){
    const byte* charDino[] = {CHARDINO_1, CHARDINO_2, CHARDINO_3, CHARDINO_4, CHARDINO_5, CHARDINO_6, CHARDINO_7T};

    byte buffer[8];
    for (int i = 4; i < 7; i++) {
        for(int j = 0; j < 8; j++) {
            buffer[j] = pgm_read_byte_near(charDino[i] + j);
        }
        lcd.createChar(i + 1, buffer);
    }

    for (int i = 0; i < 4; i++) {
        if(i == 0)lcd.setCursor(i + posH, 2 - posV);
        lcd.write(i + 1);
    }

    for (int i = 0; i < 3; i++) {
        if(i == 0)lcd.setCursor(i + posH, 3 - posV);
        lcd.write(i + 5);
    }
}

void dinoCaminar(int pos = 1, unsigned long tiempo = 50) {
  static bool estado = false;
  static unsigned long lastChange = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastChange >= tiempo) {
    lastChange = currentMillis;
    if (estado == false) {
      dinoPieDelanteroArriba(pos);
      estado = true;
    } else {
      dinoPieTraseroArriba(pos);
      estado = false;
    }
  }
}

void dinoAvanzar(unsigned long intervalo) {
  static unsigned long ultimoMovimiento = 0;
  unsigned long tiempoActual = millis();
  static int posicion = 0;

  if (tiempoActual - ultimoMovimiento >= intervalo) {
    if (posicion <= LCD_WIDTH){
      posicion++;
      lcd.clear();
    }else{
      posicion = 0;
    }
    ultimoMovimiento = tiempoActual;
  }
  dinoCaminar(posicion, 150);

}

bool dinoSaltarHigh(unsigned char duracionSalto = 5) {
    static unsigned int temporizador1 = 0;
    const int intervalo1 = 1;
    const int intervalo2 = duracionSalto;


    if (temporizador1 == 0 || temporizador1 == intervalo1 || temporizador1 == intervalo2) {
        for (int i = 0; i < 4; i++) {
            lcd.setCursor(0, i);
            lcd.print("     ");
        }
    }

    if (temporizador1 < intervalo1) {
        dinoAmbosPies(1, 1);
        temporizador1++;
        return true;
    } else if (temporizador1 >= intervalo1 && temporizador1 < intervalo2) {
        dinoAmbosPies(1, 2);
        temporizador1++;
        return true;
    } else if (temporizador1 == intervalo2) {
        temporizador1 = 0;
    }

    return false;
}

bool dinoSaltarSmall(unsigned char duracionSalto = 5) {
    static unsigned int temporizador1 = 0;
    const int intervalo1 = duracionSaltoL;

    if (temporizador1 == 0 || temporizador1 == intervalo1) {
        for (int i = 1; i < 4; i++) {
            lcd.setCursor(0, i);
            lcd.print("     ");
        }
    }

    if (temporizador1 < intervalo1) {
        dinoAmbosPies(1, 1);
        temporizador1++;
        return true;
    } else if (temporizador1 == intervalo1) {
        temporizador1 = 0;
    }

    return false;
}

int dinoSaltarObstaculo(byte typeObstaculo, unsigned char duracionSaltoH = 5,
                        unsigned char duracionSaltoL = 5) {
  static bool saltoAlto = false;
  static bool saltoBajo = false;
  static int tipoSalto = 0;

  if (typeObstaculo == 1 && !saltoAlto) { 
    saltoAlto = true; 
    tipoSalto = JUMP_HIGH;
  } else if(typeObstaculo == 2 && !saltoBajo) {
    saltoBajo = true;
    tipoSalto = JUMP_LOW;
  }

  saltoAlto = saltoAlto ? dinoSaltarHigh(duracionSaltoH) : false;
  saltoBajo = saltoBajo ? dinoSaltarSmall(duracionSaltoL) : false;

  if(!saltoAlto && !saltoBajo) { 
   dinoCaminar(1, 150);
   tipoSalto = 0;
  }
  return tipoSalto;
}

void updateCaracteres(char* caracteres, char* caracteres2, unsigned long& ultimoMovimiento, unsigned long tiempoActual) {
    memmove(&caracteres[1], &caracteres[0], 19);
    memmove(&caracteres2[1], &caracteres2[0], 19);

    if (tiempoActual - ultimoMovimiento >= random(1500, 5000)) {
        ultimoMovimiento = tiempoActual;
        caracteres[0] = random(33, 127);
        if (random(2) == 0) {
            caracteres2[0] = caracteres[0];
            caracteres[0] = 0x20;
        }
    } else {
        caracteres[0] = 0x20;
        caracteres2[0] = 0x20;
    }
}


void writeCaracteres(int tipo_salto, char* caracteres, char* caracteres2) {
    int limit = (tipo_salto == JUMP_NULL) ? 16 : LCD_WIDTH;
    for (int i = 0; i < limit; i++) {
        if (tipo_salto == JUMP_LOW && i <= 15) {
            if (caracteres2[i] != 0x20) {
                lcd.setCursor(LCD_WIDTH - i - 1, 2);
                lcd.write(caracteres2[i]);
                lcd.write(0x20);
                
            }
        }else if (tipo_salto == JUMP_HIGH || i < 16) {
            if (caracteres2[i] != 0x20) {
                lcd.setCursor(LCD_WIDTH - i - 1, 2);
                lcd.write(caracteres2[i]);
                lcd.write(0x20);
            }
        }
        if (caracteres[i] != 0x20) {
            lcd.setCursor(LCD_WIDTH - i - 1, 3);
            lcd.write(caracteres[i]);
            lcd.write(0x20);
        }
    }
}

void updateScore(int& tipo_salto, char* caracteres, char* caracteres2, unsigned long& score,
                 unsigned char detectObstacleH = 6, unsigned char detectObstacleL = 5) {
    unsigned char obstacleH = LCD_WIDTH - detectObstacleH;
    unsigned char obstacleL = LCD_WIDTH - detectObstacleL;

    if ((caracteres[obstacleL] != 0x20 || caracteres2[obstacleH] != 0x20) && tipo_salto == JUMP_NULL) {
        tipo_salto = dinoSaltarObstaculo((caracteres[15] != 0x20 ? 2 : 1), duracionSaltoH, duracionSaltoL) ;
        score = (score + 1) % 100000;
    } else {
        tipo_salto = dinoSaltarObstaculo(0, duracionSaltoH, duracionSaltoL);
    }
}

void printScore(unsigned long scoreHi, unsigned long score) {
    char scoreHiStr[6];
    char scoreStr[6];

    lcd.setCursor(5, 0);
    lcd.print("Hi: ");
    sprintf(scoreHiStr, "%05d", scoreHi);
    lcd.print(scoreHiStr);
    lcd.print(" ");
    sprintf(scoreStr, "%05d", score);
    lcd.print(scoreStr);
}

void dynoGame() {
    static unsigned long ultimoMovimiento = 0;
    unsigned long tiempoActual = millis();
    static unsigned long lastChange2 = 0;
    unsigned long currentTime2 = millis();
    static int tipo_salto = false;
    static bool dobleAltura = false;
    static char caracteres[20] = {0x20, 0x20, 0x20, 0x20, 0x20,
                                   0x20, 0x20, 0x20, 0x20, 0x20,
                                   0x20, 0x20, 0x20, 0x20, 0x20,
                                   0x20, 0x20, 0x20, 0x20, 0x20};
    static char caracteres2[20] = {0x20, 0x20, 0x20, 0x20, 0x20,
                                    0x20, 0x20, 0x20, 0x20, 0x20,
                                    0x20, 0x20, 0x20, 0x20, 0x20,
                                    0x20, 0x20, 0x20, 0x20, 0x20};

    if (firstRun) {
        lcd.clear();
        firstRun = false;
    }

    if (currentTime2 - lastChange2 >= GAME_SPEED) {
        lastChange2 = currentTime2;
        // cuanto tiempo toma la siguiente instrucción?
        updateCaracteres(caracteres, caracteres2, ultimoMovimiento, tiempoActual);
        writeCaracteres(tipo_salto, caracteres, caracteres2);
        updateScore(tipo_salto, caracteres, caracteres2, score, detectOsbtacleH, detectOsbtacleL);
        printScore(scoreHi, score);
    }

}
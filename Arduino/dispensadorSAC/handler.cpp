#include "handler.h"  
#include "tutorial.h"
#include "game.h"
#include "serve.h"


bool tutorialShow = false;

const unsigned long TUTORIAL_WAIT_TIME = 5;
const unsigned long DYNO_GAME_WAIT_TIME = 10;

bool hasTimeElapsed(unsigned long startTime, int waitTimeInSeconds) {
    return millis() - startTime > waitTimeInSeconds * 1000UL;
}

void handleTimeEvents(unsigned long currentTime, unsigned long lastPrintedTime, unsigned long startTime) {
    static bool hasPrintedDynoGame = false;
    static bool hasPrintedTutorialLCD = false;

    if (hasTimeElapsed(startTime, DYNO_GAME_WAIT_TIME)) {
        tutorialShow = true;
        if (!hasPrintedDynoGame) {
            Serial.println("Juego del dinosaurio activado");
            hasPrintedDynoGame = true;
        }
        unsigned long startMillis = millis();  // Guarda el tiempo de inicio
        dynoGame();
        unsigned long duration = millis() - startMillis;  // Calcula la duración
        Serial.print("dynoGame took: ");
        Serial.print(duration);
        Serial.println(" ms");
    } else if (hasTimeElapsed(startTime, TUTORIAL_WAIT_TIME) && !tutorialShow) {
        if (!hasPrintedTutorialLCD) {
            Serial.println("Tutorial Activado");
            hasPrintedTutorialLCD = true;
        }
        unsigned long startMillis = millis();  // Guarda el tiempo de inicio
        mostrarTutorialLCD();
        unsigned long duration = millis() - startMillis;  // Calcula la duración
        Serial.print("mostrarTutorialLCD took: ");
        Serial.print(duration);
        Serial.println(" ms");
    } else if (currentTime != lastPrintedTime) {
        lastPrintedTime = currentTime;
        Serial.print("StartTime: "); Serial.println(currentTime);
    }
}
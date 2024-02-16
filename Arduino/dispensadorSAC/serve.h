
#ifndef ARDUINO_SERVE_H
#define ARDUINO_SERVE_H
#include <Arduino.h>

void resetOutputs();
void displayScrollingMessage(const String& message, int& scrollPosition, const int messageLength);
void showScrollingMessage(const String& message, const int messageLength);
bool hasTimeElapsed(unsigned long startTime, int waitTimeInSeconds);
void handleTimeEvents(unsigned long currentTime, unsigned long lastPrintedTime, unsigned long startTime);
void enterConfigurationMode();
void resetScoreAndTime();
void handleProductButton(int button, float cost);
void handleCredit();
void handleButtons();
void showChangeMessage();
void showGoodbyeMessage();
bool dispenceProduct(float *_totalCredit, float _productCost, int _index);
bool checkCredit(float credit, float cost);
void printLines(const char* line1, const char* line2, const char* line3, const char* line4);
void showWelcomeMessage();
String getProductName(int index);
void showMenuCreditInsuficient(float costPerLiter, int index);
bool showConfigurationMode();
void showMenu();
bool showSubMenu();
void writeInEEPROM(float valor, int direccion);
float readFromEEPROM(int direccion);
void loadFromEEPROM(int lengthData);
void setZeroEeprom(int lengthData);
bool showCredit(float credit);
void costOfProduct(const char* message = "", int index = 0);
void displayProgressBar(int percent);
void showProduct(int index);
void goodBye();
void displayStatus(int row, int col, bool condition);
void checkProductInfo(float quantity, float price, float time, int row, int col);
void updateShiftRegister();
void setOutput(int outputNumber, bool status);
int estadoEntrada(int id, int estado);
int getState(int pinNumber);




#endif

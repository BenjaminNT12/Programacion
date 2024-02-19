
#ifndef ARDUINO_SERVE_H
#define ARDUINO_SERVE_H
#include <Arduino.h>


extern const unsigned long TUTORIAL_WAIT_TIME;
extern const unsigned long DYNO_GAME_WAIT_TIME ;

const int BUTTON_DOWN_PIN = 0;
const int BUTTON_UP_PIN = 1;
const int BUTTON_MENU_PIN = 2;
const int BUTTON_SELECT_PIN = 3;
const int BUTTON_PRODUCT1_PIN = 4;
const int BUTTON_PRODUCT2_PIN = 5;
const int BUTTON_PRODUCT3_PIN = 6;
const int BUTTON_PRODUCT4_PIN = 7;
const int COIN_INPUT_PIN = A3;
const int HOOPER_OUTPUT_PIN = 11;
const int OUTPUT_PIN_0  = 0; 
const int OUTPUT_PIN_1 = 1; 
const int OUTPUT_PIN_2 = 2; 
const int OUTPUT_PIN_3 = 3; 
const int OUTPUT_PIN_4 = 4; 
const int OUTPUT_PIN_5 = 5; 
const int OUTPUT_PIN_6 = 6; 
const int OUTPUT_PIN_7 = 7; 
const int DATA_PIN  = 13;	
const int LATCH_PIN = A0;	
const int CLOCK_PIN = A1;	
const int HOOPER_PIN = 38; 
const int MAX_MENU_ITEMS = 8; 

#define PROD0_BUTTON BUTTON_DOWN_PIN
#define PROD1_BUTTON BUTTON_UP_PIN
#define PROD2_BUTTON BUTTON_MENU_PIN
#define PROD3_BUTTON BUTTON_SELECT_PIN
#define PROD4_BUTTON BUTTON_PRODUCT1_PIN
#define PROD5_BUTTON BUTTON_PRODUCT2_PIN
#define PROD6_BUTTON BUTTON_PRODUCT3_PIN
#define PROD7_BUTTON BUTTON_PRODUCT4_PIN
#define ACTIVATE_HOOPER_OUTPUT HOOPER_PIN
#define COIN_OUTPUT HOOPER_OUTPUT_PIN

const int PROD_BUTTONS[8] = {PROD0_BUTTON, PROD1_BUTTON, PROD2_BUTTON, PROD3_BUTTON, PROD4_BUTTON,  PROD5_BUTTON,  PROD6_BUTTON,  PROD7_BUTTON};


void resetOutputs();
void displayScrollingMessage(const String& message, int& scrollPosition, const int messageLength);
void showScrollingMessage(const String& message, const int messageLength);
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
void activeOutput(int active, int index);
void handleCoin(void);



#endif

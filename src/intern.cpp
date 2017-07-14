/*********************

Example code for the Adafruit RGB Character LCD Shield and Library

This code displays text on the shield, and also reads the buttons on the keypad.
When a button is pressed, the backlight changes color.

**********************/

// include the library code:
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Arduino.h>
#include <User.cpp>
#include <EEPROM.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

User matt;
User jimmy;
User* cur;

String tempUsr = "User = ";
String tempPts = "Points = ";
String tempWin = "Sr. ";
String tempLoser = "Jr. ";

void printUsr(String name) {
  lcd.print(tempUsr + cur->getName());
}

void printPoints(int points) {
  lcd.print(tempPts + cur->getPoints());
}

void printScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  printUsr(cur->getName());
  lcd.setCursor(0, 1);
  printPoints(cur->getPoints());
}

void toggleUser() {
  if(cur == &jimmy) {
    cur = &matt;
  } else {
    cur = &jimmy;
  }
}

void showLeader(){
  lcd.clear();
  lcd.setCursor(0, 0);
  if(jimmy.getPoints() >= matt.getPoints()){
    lcd.print(tempWin + jimmy.getName() + " " + jimmy.getPoints() );
    lcd.setCursor(0, 1);
    lcd.print(tempLoser + matt.getName() + " " + matt.getPoints() );
  } else {
    lcd.print(tempWin + matt.getName() + " " + matt.getPoints() );
    lcd.setCursor(0, 1);
    lcd.print(tempLoser + jimmy.getName() + " " + jimmy.getPoints() );
  }

}

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  Serial.print("Setup");
  lcd.begin(16, 2);

  jimmy = *(new User("Jimmy", 0));
  matt = *(new User("Matt", sizeof(int)*2));

  //jimmy.reset();
  //matt.reset();

  cur = &(jimmy);
  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  printScreen();
  time = millis() - time;
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);
}

uint8_t i=0;
void loop() {
  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      cur->addPoints();
      printScreen();
      lcd.setBacklight(GREEN);
    }
    if (buttons & BUTTON_DOWN) {
      cur->subtractPoints();
      printScreen();
      lcd.setBacklight(RED);
    }
    if (buttons & BUTTON_LEFT) {
      toggleUser();
      printScreen();
      lcd.setBacklight(TEAL);
    }
    if (buttons & BUTTON_RIGHT) {
      toggleUser();
      printScreen();
      lcd.setBacklight(TEAL);
    }

    if (buttons & BUTTON_SELECT) {
      showLeader();
      lcd.setBacklight(VIOLET);
    }
  }
}

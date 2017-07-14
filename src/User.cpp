#pragma once

#include <Arduino.h>
#include <EEPROM.h>
using namespace std;

class User {
  int points;
  String name;
  int address;
  int sign; //0 == pos, 1 == neg
public:
  User() {
    this->name = "NO NAME";
  }
  User(String name, int address) {
    this->name = name;
    this->address = address;
    this->points = EEPROM.read(address);
    if (EEPROM.read(address+sizeof(int)) == 1) {
      this->points *= -1;
    }
  }
  void addPoints() {
    EEPROM.put(this->address, ++this->points);
    if (this->points >= 0) sign = 0;
    if (this->points < 0) sign = 1;
    EEPROM.put(this->address+sizeof(int), sign);
  }
  void subtractPoints() {
    EEPROM.put(this->address, --this->points);
    if (this->points >= 0) sign = 0;
    if (this->points < 0) sign = 1;
    EEPROM.put(this->address + sizeof(int), sign);
    Serial.println(this->points);
  }
  void reset(){
    EEPROM.put(this->address,0);
    EEPROM.put(this->address+sizeof(int), 0);
  }
  void setPoints(int points) {
    this->points = points;
    if (this->points >= 0) sign = 0;
    if (this->points < 0) sign = 1;
    EEPROM.put(address, points);
    EEPROM.put(address + sizeof(int), sign);
  }
  int getPoints() {
    if (this->sign == 1)
      return this->points;
    return this->points;
  }
  String getName() {
    return this->name;
  }
};

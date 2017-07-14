#pragma once

#include <Arduino.h>
using namespace std;

class User {
  int points = 0;
  String name;
public:
  User() {
    this->name = "NO NAME";
  }

  User(String name) {
    this->name = name;
  }
  void addPoints() {
    this->points++;
  }
  void subtractPoints() {
    this->points--;
  }
  int getPoints() {
    return this->points;
  }
  String getName() {
    return this->name;
  }
};

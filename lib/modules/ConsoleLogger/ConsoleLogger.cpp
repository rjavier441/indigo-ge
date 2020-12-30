// PROJECT:         Indigo
// Author:          R. Javier
// File:            ConsoleLogger.cpp
// Created:         2020-12-29
// Last Modified:   2020-12-29
// Details:
//                  Defines implementation of class ConsoleLogger.
// Dependencies:
//                  n/a

// @includes
#include <cstdio>
#include <string>
#include "ConsoleLogger.hpp"
using namespace std;

// @ctor
Indigo::ConsoleLogger::ConsoleLogger() {}

// @dtor
Indigo::ConsoleLogger::~ConsoleLogger() {
  // Do nothing
}

// @function        getInstance()
// @description     Returns a reference to the ConsoleLogger singleton,
//                  initializing one if it doesn't yet exist.
// @parameters      n/a
// @returns         (ConsoleLogger&) ref
//                                      Refernce to the singleton.
Indigo::ConsoleLogger& Indigo::ConsoleLogger::getInstance() {
  
  // Initialize a single instance
  static ConsoleLogger instance;
  return instance;
}

// @function        log()
// @description     Prints a message
// @parameters      (string) msg        The message to print.
//                  (~string) src       (Optional) A message prefix
//                                      to identify the sender.
// @returns         n/a
void Indigo::ConsoleLogger::log(string msg, string src) {
  printf("%s%s\n", src.c_str(), msg.c_str());
}
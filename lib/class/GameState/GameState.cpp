// PROJECT:         Indigo
// Author:          R. Javier
// File:            GameState.cpp
// Created:         2021-01-23
// Last Modified:   2021-01-23
// Details:
//                  Defines implementation for class GameState.
// Dependencies:
//                  n/a

// @includes
#include <string>
#include "GameState.hpp"
using namespace std;
using namespace Indigo;

// @function        getName()
// @description     Name accessor.
// @parameters      n/a
// @returns         (string) name_
//                                      The name of this GameState.
string GameState::getName() {
  return name_;
}
// TODO 2021-02-06
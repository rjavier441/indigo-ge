// PROJECT:         Indigo
// Author:          R. Javier
// File:            main.cpp
// Created:         March 23, 2019
// Last Modified:   March 23, 2019
// Details:
//                  This file contains the game engine's main routine, which
//                  runs the game, loads characters and maps, manages game
//                  state, and is the main point of interface between the user
//                  controls and the game.
// Dependencies:
//                  C++11 and above
//                  SMFL v2.5.1 and above

// Includes
#include <SFML/Graphics.hpp>
#include "../lib/class/Error/Error.hpp"
#include "../lib/class/GameState/GameState.hpp"
#include "../lib/module/WindowManager/WindowManager.hpp"
using namespace std;

// @function        main()
// @description     This function is the main routine of the game engine
// @parameters      (int) argc      The number of arguments in the arg. vector
//                  (char*[]) argv  An array of strings commprising the args.
//                                  passed to this function
int main( int argc, char* argv[] ) {

    // Load Essentials
    WindowManager* wm = WindowManager::getInstance();

    return ErrorCode::NoError;
}

// EOF main.cpp
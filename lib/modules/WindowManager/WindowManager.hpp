// PROJECT:         Indigo
// Author:          R. Javier
// File:            WindowManager.hpp
// Created:         March 23, 2019
// Last Modified:   March 23, 2019
// Details:
//                  This file contains a class that manages the window of the
//                  game
// Dependencies:
//                  C++11 and above
//                  SFML v2.5.1 and above
#pragma once

// Includes
#include "../../interface/Testable.hpp"

// @class           WindowManager
// @description     This singleton class is used by the game engine's main
//                  routine to manage the window throughout the game's duration
class WindowManager : public Testable {
public:
    ~WindowManager();
    static WindowManager* getInstance();
    int test();
private:
    WindowManager();
    static WindowManager* wm;
};

// EOF WindowManager.hpp
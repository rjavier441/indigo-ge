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

// @includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
using namespace std;

// @class           WindowManager
// @description     This singleton class is used by the game engine's main
//                  routine to manage the window throughout the game's duration
class WindowManager {
public:
    static WindowManager& getInstance();
    sf::Window* openWindow(string t = "Indigo Game", int w = 800, int h = 600);
    sf::Window* getWindow();
    void setFullscreen(bool);
private:
    WindowManager(string t = "Indigo Game");
    ~WindowManager();
    static bool windowExists;
    sf::Window window;
    bool isFullscreen;
};

// EOF WindowManager.hpp
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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
using namespace std;

// @class           WindowManager
// @description     This singleton class is used by the game engine's main
//                  routine to manage the window throughout the game's duration
class WindowManager {
public:
    static WindowManager* getInstance();
    sf::Window* openWindow(string t = "Indigo Game", int w = 800, int h = 600);
    sf::Window* getWindow();
private:
    static WindowManager* wm;
    static bool windowExists;
    ~WindowManager();
    WindowManager(string t = "Indigo Game");
    sf::Window window;
    string title;
    int width;
    int height;
};

// EOF WindowManager.hpp
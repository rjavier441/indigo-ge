// PROJECT:         Indigo
// Author:          R. Javier
// File:            WindowManager.cpp
// Created:         March 23, 2019
// Last Modified:   March 23, 2019
// Details:
//                  This file contains a the implementation of the WindowManager
//                  class
// Dependencies:
//                  C++11 and above
//                  SFML v2.5.1 and above

// Includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <string>
#include "WindowManager.hpp"
using namespace std;

// @ctor
WindowManager::WindowManager(string t) {
    title = t;
}

// @dtor
WindowManager::~WindowManager() {

    // Delete instance, if it isn't already null
    if( wm != nullptr ) {
        delete wm;
    }
}

// @function        getInstance()
// @description     This function acquires an instance of the WindowManager
//                  singleton. It will create one if one doesn't exist yet.
// @parameters      n/a
// @returns         n/a
WindowManager* WindowManager::getInstance() {

    try {

        // Check if an instance already exists
        if( wm == nullptr ) {

            // If not, create an instance defaulting to full-screen mode
            wm = new WindowManager();
        }

        // Return instance reference
        return wm;
    } catch(...) {
        printf("Error creating WindowManager instance\n");
    }

    return nullptr;
}

// @function        openWindow()
// @description     Creates and opens this instance's window.
// @parameters      n/a
// @returns         (sf::Window*) window
//                                      The sf::Window for this instance.
sf::Window* WindowManager::openWindow() {

    try {
        window.create(
            sf::VideoMode(
                sf::VideoMode::getDesktopMode().width,
                sf::VideoMode::getDesktopMode().height
            ),
            title,
            sf::Style::Default
        );

        return &window;
    } catch(...) {
        printf("Error creating window\n");
    }

    return nullptr;
}

// @function        getWindow()
// @description     Gives the user a pointer to the instance's window.
// @parameters      n/a
// @returns         (sf::Window*) window
//                                      The sf::Window for this instance.
sf::Window* WindowManager::getWindow() {
    return &window;
}

// EOF WindowManager.cpp
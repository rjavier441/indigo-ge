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

// @includes
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdio>
#include <string>
#include "WindowManager.hpp"
using namespace std;

// @statics
bool WindowManager::windowExists = false;

// @ctor
WindowManager::WindowManager(string t) {
    isFullscreen = false;
}

// @dtor
WindowManager::~WindowManager() {
    // Do nothing
}

// @function        getInstance()
// @description     This function acquires an instance of the WindowManager
//                  singleton. It will create one if one doesn't exist yet.
// @parameters      n/a
// @returns         (WindowManager&) ref
//                                      Reference to a static function
//                                      variable acting as a singleton
//                                      instance for this class.
WindowManager& WindowManager::getInstance() {

    // Initialize a single instance
    static WindowManager instance;
    return instance;
}

// @function        openWindow()
// @description     Creates and opens this instance's window.
// @parameters      (~string) t         The window's title.
//                  (~int) w            The window's width in pixels.
//                  (~int) h            The window's height in pixels.
// @returns         (sf::Window*) window
//                                      The sf::Window for this instance.
sf::Window* WindowManager::openWindow(string t, int w, int h) {

    try {
        if( !windowExists ) {
            windowExists = true;
            window.create( sf::VideoMode( w, h ), t, sf::Style::Default );
        } else {
            printf("Window already exists!\n");
        }
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

// @function        setFullscreen()
// @description     Controls whether the window is in full-screen mode.
// @parameters      (bool) active       If true, sets the window dimentions
//                                      to full-screen mode for the window's
//                                      currently encapsulating screen.
// @returns         n/a
void WindowManager::setFullscreen(bool active) {
    
    if( active != isFullscreen ) {} else {
        printf("");
    }
}

// EOF WindowManager.cpp
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
#include <cstdio>
#include "WindowManager.hpp"
using namespace std;

// @statics
WindowManager* WindowManager::wm;

// @ctor
WindowManager::WindowManager() {

    // Initialize singleton pointer to null
    wm = NULL;
}

// @dtor
WindowManager::~WindowManager() {

    // Do nothing
}

// @function        getInstance()
// @description     This function acquires an instance of the WindowManager
//                  singleton. It will create one if one doesn't exist yet.
// @parameters      n/a
// @returns         n/a
WindowManager* WindowManager::getInstance() {

    // Check if an instance already exists
    if( wm == NULL ) {

        // If not, create an instance
        wm = new WindowManager();
    }

    // Return instance reference
    return wm;
}

// @function        Testable::test()
// @description     This function is a test method inherited from the Testable
//                  abstract class
// @parameters      n/a
// @returns         (int) zero          Always returns zero.
int WindowManager::test() {

    // Test
    printf( "Hello %s!", "World" );
    return 0;
}

// EOF WindowManager.cpp
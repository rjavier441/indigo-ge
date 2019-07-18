// PROJECT:         Indigo
// Author:          R. Javier
// File:            Testable.hpp
// Created:         March 23, 2019
// Last Modified:   March 23, 2019
// Details:
//                  This file contains an abstract class for a testable object
//                  (appends a test method to each child class)
// Dependencies:
//                  C++11 and above
//                  SFML v2.5.1 and above
#pragma once

// @abstract        Testable
// @description     This abstract class enforces all child classes to have a
//                  test function
class Testable{
public:
    // @dtor
    virtual ~Testable() {}

    // @functions
    virtual void test() = 0;
};

// EOF Testable.hpp
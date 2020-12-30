// PROJECT:         indigo
// Author:          R. Javier
// File:            test_WindowManager.cpp
// Created:         2020-11-22
// Last Modified:   2020-11-22
// Details:
//                  A unit test for the Window Manager class.
// Dependencies:
//                  Catch2 v2.13.3+

// @includes
#include "lib/catch2/catch.hpp"
#include "../lib/modules/WindowManager/WindowManager.hpp"
using namespace std;

// @tests
TEST_CASE( "WindowManager initializes without opening a window", "[WindowManager]" ) {
  REQUIRE( WindowManager::getInstance().getWindow()->isOpen() == false );
}
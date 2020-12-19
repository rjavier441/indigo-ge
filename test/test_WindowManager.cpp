// PROJECT:         indigo
// Author:          R. Javier
// File:            test_WindowManager.cpp
// Created:         2020-11-22
// Last Modified:   2020-11-22
// Details:
//                  A unit test for the Window Manager class.
// Dependencies:
//                  Catch2 v2.13.3+
#define CATCH_CONFIG_MAIN
#include "lib/catch2/catch.hpp"
#include "../lib/modules/WindowManager/WindowManager.hpp"
using namespace std;

TEST_CASE( "WindowManager initializes and returns an instance", "[WindowManager]" ) {
  WindowManager* temp = WindowManager::getInstance();
  // REQUIRE( WindowManager::getInstance() != NULL );
  REQUIRE( temp->test() == 0 );
}
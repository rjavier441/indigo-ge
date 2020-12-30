// PROJECT:         Indigo
// Author:          R. Javier
// File:            test_initializer.cpp
// Created:         2020-12-29
// Last Modified:   2020-12-29
// Details:
//                  Initializes test environment for Catch2.
// Dependencies:
//                  Catch2 v2.13.3+
#define CATCH_CONFIG_MAIN
#include "lib/catch2/catch.hpp"
using namespace std;

// @tests
TEST_CASE( "Catch2 was initialized", "[Test Initializer]" ) {
  REQUIRE( true == true );
}
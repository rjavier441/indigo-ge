// PROJECT:         Indigo
// Author:          R. Javier
// File:            test_ConsoleLogger.cpp
// Created:         2020-12-29
// Last Modified:   2020-12-29
// Details:
//                  A unit test for the ConsoleLogger class.
// Dependencies:
//                  Catch2 v2.13.3+

// @includes
#include "lib/catch2/catch.hpp"
#include "../lib/modules/ConsoleLogger/ConsoleLogger.hpp"
using namespace std;

// @statics
Indigo::ConsoleLogger* Indigo::ConsoleLogger::Console = nullptr;

// @tests
TEST_CASE( "ConsoleLogger initializes and returns an instance", "[ConsoleLogger]" ) {
  REQUIRE( Indigo::ConsoleLogger::getInstance() != nullptr );
}
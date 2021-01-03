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
#include <cstdio>
#include <cstdarg>
#include <string>
#include <string.h>
#include <fakeit.hpp> // See https://github.com/eranpeer/FakeIt/issues/197 for a description of how I got fakeit.hpp to compile.
#include "lib/catch2/catch.hpp"
#include "../lib/modules/ConsoleLogger/ConsoleLogger.hpp"
using namespace std;

// @tests
TEST_CASE( "ConsoleLogger initializes and uses only a single instance", "[ConsoleLogger]" ) {

  // SUT
  Indigo::ConsoleLogger* a = &Indigo::ConsoleLogger::getInstance();
  Indigo::ConsoleLogger* b = &Indigo::ConsoleLogger::getInstance();
  Indigo::ConsoleLogger* c = &Indigo::ConsoleLogger::getInstance();

  // Test that successive calls to getInstance() return the same address
  REQUIRE( a == &Indigo::ConsoleLogger::getInstance() );
  REQUIRE( b == &Indigo::ConsoleLogger::getInstance() );
  REQUIRE( c == &Indigo::ConsoleLogger::getInstance() );
}

TEST_CASE( "ConsoleLogger::log() returns the correct message length", "[ConsoleLogger]" ) {

  // SUT
  Indigo::ConsoleLogger& a = Indigo::ConsoleLogger::getInstance();
  string testPrefix[3] = {"[Prefix]","","Only Prefix"};
  string testMessage[3] = {"Test Message","Only Message",""};
  char temp[50];
  unsigned int expected[3] = {
    sprintf(temp, "%s%s\n", testPrefix[0].c_str(), testMessage[0].c_str()),
    sprintf(temp, "%s%s\n", testPrefix[1].c_str(), testMessage[1].c_str()),
    sprintf(temp, "%s%s\n", testPrefix[2].c_str(), testMessage[2].c_str())
  };

  REQUIRE( a.log(testMessage[0], testPrefix[0]) == expected[0] );
  REQUIRE( a.log(testMessage[1], testPrefix[1]) == expected[1] );
  REQUIRE( a.log(testMessage[2], testPrefix[2]) == expected[2] );
}
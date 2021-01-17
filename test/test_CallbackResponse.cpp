// PROJECT:         Indigo
// Author:          R. Javier
// File:            test_CallbackResponse.cpp
// Created:         2021-01-16
// Last Modified:   2021-01-16
// Details:
//                  A unit test for class CallbackResponse and its
//                  derivatives.
// Dependencies:
//                  Catch2 v2.13.3+

// @includes
#include <cstdio>
#include <cstring>
#include "../lib/class/CallbackResponse/CallbackResponse.hpp"
#include "lib/catch2/catch.hpp"
using namespace std;

// @test            CallbackResponseSuccess uses correct name and
//                  message.
TEST_CASE( "CallbackResponseSuccess uses correct name and message", "[CallbackResponseSuccess][CallbackResponse]" ) {

  // SUT
  Indigo::CallbackResponse sut1( "cbr", "This is a callback response" );
  Indigo::CallbackResponseSuccess sut2(
    "This is a success callback response"
  );

  REQUIRE( sut1.getName() != sut2.getName() );
  REQUIRE( strncmp(
    sut2.getName().c_str(), Indigo::CallbackResponseType::kSuccess, 30
  ) == 0 );
}
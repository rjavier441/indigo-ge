// PROJECT:         Indigo
// Author:          R. Javier
// File:            test_Callback.cpp
// Created:         2021-01-16
// Last Modified:   2021-01-16
// Details:
//                  A unit test for class Callback.
// Dependencies:
//                  Catch2 v2.13.3+

// @includes
#include <cstdio>
#include <cstring>
#include <string>
#include <stdexcept>
#include "lib/catch2/catch.hpp"
#include "../lib/class/Callback/Callback.hpp"
#include "../lib/class/GameState/GameState.hpp"
#include "../lib/class/CallbackResponse/CallbackResponse.hpp"
using namespace std;

// @begin test utilities
namespace TestCallbackMethods {
  static int count = 0;
  const string kFailureMsg = "Failed on purpose";

  // Function that returns a custom response
  Indigo::CallbackResponse returnFailureResponse(
    sf::Event::EventType et, Indigo::GameState* state, sf::Event* e
  ) {
    // Return a failure response
    Indigo::CallbackResponse response("Failure", kFailureMsg);
    return response;
  }

  // Function to throw a runtime error
  Indigo::CallbackResponse throwRuntimeError(
    sf::Event::EventType et, Indigo::GameState* state, sf::Event* e
  ) {
    
    // Throw an uncaught exception
    throw runtime_error("Error on purpose");
  }

  // Function that increments an external integer
  Indigo::CallbackResponse incrementCount(
    sf::Event::EventType et, Indigo::GameState* state, sf::Event* e
  ) {
    ++TestCallbackMethods::count;
    Indigo::CallbackResponseSuccess response;
    return response;
  }
  
  // Function that decrements an external integer
  Indigo::CallbackResponse decrementCount(
    sf::Event::EventType et, Indigo::GameState* state, sf::Event* e
  ) {
    --TestCallbackMethods::count;
    Indigo::CallbackResponseSuccess response;
    return response;
  }

  // Function that doubles an external integer
  Indigo::CallbackResponse doubleCount(
    sf::Event::EventType et, Indigo::GameState* state, sf::Event* e
  ) {
    TestCallbackMethods::count *= 2;
    Indigo::CallbackResponseSuccess response;
    return response;
  }
}
// @end test utilities

// @test            Callback runs the correct function
TEST_CASE( "Callback runs the correct function", "[Callback]" ) {

  // SUT
  Indigo::GameState s;
  Indigo::CallbackFunctionPointer myFuncPtr {
    &TestCallbackMethods::returnFailureResponse
  };
  Indigo::Callback cb( "myCallback", &s, myFuncPtr );
  
  REQUIRE( strncmp(
    cb.run( sf::Event::Closed ).getMessage().c_str(),
    TestCallbackMethods::kFailureMsg.c_str(),
    100
  ) == 0 );
}

// @test            Callback returns CallbackResponseUncaughtExecption
//                  response on uncaught exception during callback run.
TEST_CASE(
  "Callback returns CallbackResponseUncaughtExecption response on uncaught exception during callback run", "[Callback]"
) {

  // SUT
  Indigo::GameState s;
  Indigo::CallbackFunctionPointer myFuncPtr {
    &TestCallbackMethods::throwRuntimeError
  };
  Indigo::Callback cb( "badCallback", &s, myFuncPtr );

  // Make sure cb.run() doesn't throw an error when the callback throws
  // an uncaught exception, instead returning the special
  //  "CallbackResponseUncaughtExecption" response.
  REQUIRE_NOTHROW( cb.run( sf::Event::Closed ) );
  REQUIRE( strncmp(
    cb.run(sf::Event::Closed ).getName().c_str(),
    Indigo::CallbackResponseType::kUncaughtException,
    100
  ) == 0 );
}

// @test            Callback can influence the state of any externally
//                  accessible data.
TEST_CASE(
  "Callback can influence the state of any externally accessible data",
  "[Callback]"
) {

  // SUTs
  Indigo::GameState s;
  Indigo::CallbackFunctionPointer incPtr {
    &TestCallbackMethods::incrementCount
  };
  Indigo::CallbackFunctionPointer decPtr {
    &TestCallbackMethods::decrementCount
  };
  Indigo::CallbackFunctionPointer dblPtr {
    &TestCallbackMethods::doubleCount
  };
  Indigo::Callback sutIncrement( "sutIncrement", &s, incPtr );
  Indigo::Callback sutDecrement( "sutDecrement", &s, decPtr );
  Indigo::Callback sutDouble( "sutDouble", &s, dblPtr );

  // Execute test starting from a known state
  TestCallbackMethods::count = 0;

  INFO( "Incrementing once" );
  sutIncrement.run( sf::Event::Closed );
  REQUIRE( TestCallbackMethods::count == 1 );
  
  INFO( "Decrementing twice" );
  sutDecrement.run( sf::Event::Closed );
  sutDecrement.run( sf::Event::Closed );
  REQUIRE( TestCallbackMethods::count == -1 );
  
  INFO( "Decrementing once more and doubling" );
  sutDecrement.run( sf::Event::Closed );
  sutDouble.run( sf::Event::Closed );
  REQUIRE( TestCallbackMethods::count == -4 );
}
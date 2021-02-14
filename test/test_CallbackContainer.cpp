// PROJECT:         Indigo
// Author:          R. Javier
// File:            test_CallbackContainer.cpp
// Created:         2021-02-06
// Last Modified:   2021-02-06
// Details:
//                  A unit test for class CallbackContainer.
// Dependencies:
//                  Catch v2.13.3+

// @includes
#include <cstring>
#include <string>
#include "lib/catch2/catch.hpp"
#include "../lib/class/GameState/GameState.hpp"
#include "../lib/class/CallbackContainer/CallbackContainer.hpp"
#include "../lib/class/CallbackResponse/CallbackResponse.hpp"
using namespace std;
using namespace Indigo;

// @begin test utlities
namespace testCallbackContainerMethods {
  // @gameStates
  GameState s;

  // @callbackSources
  CallbackResponse getA(
    sf::Event::EventType et, GameState* state, sf::Event* e
  ) {
    CallbackResponse response("A");
    return response;
  }
  CallbackResponse getB(
    sf::Event::EventType et, GameState* state, sf::Event* e
  ) {
    CallbackResponse response("B");
    return response;
  }
  CallbackResponse getC(
    sf::Event::EventType et, GameState* state, sf::Event* e
  ) {
    CallbackResponse response("C");
    return response;
  }

  // @funcPtrs
  CallbackFunctionPointer fptrA {
    &getA
  };
  CallbackFunctionPointer fptrB {
    &getB
  };
  CallbackFunctionPointer fptrC {
    &getC
  };

  // @callbacks
  Callback cbA( "Callback A", &s, fptrA );
  Callback cbB( "Callback B", &s, fptrB );
  Callback cbC( "Callback C", &s, fptrC );
}
// @end test utlities

// @test            CallbackContainer can insert to new and existing
//                  EventType keys.
TEST_CASE(
  "CallbackContainer can insert to new and existing EventType keys",
  "[CallbackContainer]"
) {
  // SUT
  CallbackContainer SUT;

  REQUIRE( SUT.on(
    sf::Event::EventType::Closed,
    testCallbackContainerMethods::cbA
  ) == true );
  REQUIRE( SUT.on(
    sf::Event::EventType::Closed,
    testCallbackContainerMethods::cbB
  ) == true );
}

// @test            CallbackContainer is able to add/remove callbacks
//                  (i.e. on/off/purgeEventCallbacks/purgeAllCallbacks)
TEST_CASE(
  "CallbackContainer can freely add/remove callbacks",
  "[CallbackContainer]"
) {

  // SUT
  string s = "a";
  CallbackContainer SUT;
  sf::Event::EventType et1 = sf::Event::EventType::KeyPressed;
  sf::Event::EventType et2 = sf::Event::EventType::Closed;
  sf::Event::EventType et3 = sf::Event::EventType::MouseButtonPressed;
  
  // Calculate 1st state expected results (tests "on()")
  CallbackResponse expected1a[] = {  // State 1: inserted et1 callbacks
    testCallbackContainerMethods::getA( // Callback A
      et1,
      &testCallbackContainerMethods::s,
      nullptr
    ),
    testCallbackContainerMethods::getC( // Callback C
      et1,
      &testCallbackContainerMethods::s,
      nullptr
    ),
    testCallbackContainerMethods::getB( // Callback B
      et1,
      &testCallbackContainerMethods::s,
      nullptr
    )
  };
  CallbackResponse expected1b[] = { // State 1: inserted et2 callbacks
    expected1a[0],  // Callback A
    expected1a[2],  // Callback B
    expected1a[1]   // Callback C
  };
  CallbackResponse expected1c[] = { // State 1: inserted et3 callback
    expected1a[1]   // Callback C
  };

  // Calculate 2nd state expected results (tests "off()")
  CallbackResponse expected2a[] = { // State 2: removed et1 Callback C
    expected1a[0],  // Callback A
    expected1a[2]   // Callback B
  };
  CallbackResponse expected2b[] = { // State 2: removed et2 Callback A
    expected1a[2],  // Callback B
    expected1a[1]   // Callback C
  };

  // Begin state 1 test
  // Initialize SUT with all et1 callbacks
  REQUIRE( SUT.on( et1, testCallbackContainerMethods::cbA ) == true );
  REQUIRE( SUT.on( et1, testCallbackContainerMethods::cbC ) == true );
  REQUIRE( SUT.on( et1, testCallbackContainerMethods::cbB ) == true );

  // Then et2 callbacks
  REQUIRE( SUT.on( et2, testCallbackContainerMethods::cbA ) == true );
  REQUIRE( SUT.on( et2, testCallbackContainerMethods::cbB ) == true );
  REQUIRE( SUT.on( et2, testCallbackContainerMethods::cbC ) == true );
  
  // Then et3 callbacks
  REQUIRE( SUT.on( et3, testCallbackContainerMethods::cbC ) == true );

  // Verify et1's callbacks were added
  vector<CallbackResponse> actual1a = SUT.fireEvent(et1);
  int i = 0;
  REQUIRE( actual1a.size() == 3 );
  for( auto item : actual1a ) {
    REQUIRE( strncmp(
      item.getName().c_str(),
      expected1a[i].getName().c_str(),
      100
    ) == 0 );
    i++;
  }

  // Verify et2's callbacks were added
  vector<CallbackResponse> actual1b = SUT.fireEvent(et2);
  i = 0;
  REQUIRE( actual1b.size() == 3 );
  for( auto item : actual1b ) {
    REQUIRE(
      strncmp( item.getName().c_str(), expected1b[i].getName().c_str(), 100 ) == 0
    );
    i++;
  }

  // Verify et3's callback was added
  vector<CallbackResponse> actual1c = SUT.fireEvent(et3);
  REQUIRE( actual1c.size() == 1 );
  REQUIRE( strncmp( actual1c[0].getName().c_str(), expected1c[0].getName().c_str(), 100 ) == 0 );

  // Begin state 2 test
  // Perform state 2 modifications (remove et1 and et2 callbacks)
  REQUIRE( SUT.off( et1, "Callback C" ) == true );
  REQUIRE( SUT.off( et2, "Callback A" ) == true );

  // Verify et1's Callback C was removed
  vector<CallbackResponse> actual2a = SUT.fireEvent(et1);
  i = 0;
  REQUIRE( actual2a.size() == 2 );
  for( auto item : actual2a ) {
    REQUIRE(
      strncmp( item.getName().c_str(), expected2a[i].getName().c_str(), 100 ) == 0
    );
    i++;
  }

  // Verify et2's Callback A was removed
  vector<CallbackResponse> actual2b = SUT.fireEvent(et2);
  i = 0;
  REQUIRE( actual2b.size() == 2 );
  for( auto item : actual2b ) {
    REQUIRE(
      strncmp( item.getName().c_str(), expected2b[i].getName().c_str(), 100 ) == 0
    );
    i++;
  }

  // Verify et3's callback chain was unchanged
  vector<CallbackResponse> actual2c = SUT.fireEvent(et3);
  REQUIRE( actual2c.size() == 1 );
  REQUIRE( strncmp( actual2c[0].getName().c_str(), expected1c[0].getName().c_str(), 100 ) == 0 );

  // Begin state 3 test
  // Perform state 3 modifications (remove et1 callbacks only)
  REQUIRE( SUT.purgeEventCallbacks(et1) == true );


  // Verify only et1's callbacks are removed
  REQUIRE( SUT.fireEvent(et1).size() == 0 );
  REQUIRE( SUT.fireEvent(et2).size() == 2 );
  REQUIRE( SUT.fireEvent(et3).size() == 1 );

  // Begin state 4 test
  // Perform state 4 modifications (remove ALL callbacks)
  REQUIRE( SUT.purgeAllCallbacks() == true );

  // Verify all event callbacks have been removed
  REQUIRE( SUT.fireEvent(et1).size() == 0 );
  REQUIRE( SUT.fireEvent(et2).size() == 0 );
  REQUIRE( SUT.fireEvent(et3).size() == 0 );
}

// @test            CallbackContainer orders callbacks in insertion
//                  order.
TEST_CASE(
  "CallbackContainer orders callbacks in insertion order",
  "[CallbackContainer]"
) {

  // SUT
  sf::Event::EventType et = sf::Event::EventType::KeyPressed;
  CallbackContainer SUT;

  // Load events
  SUT.on( et, testCallbackContainerMethods::cbA );
  SUT.on( et, testCallbackContainerMethods::cbC );
  SUT.on( et, testCallbackContainerMethods::cbB );

  // Prepare expected results
  const int expectedSize = 3;
  CallbackResponse expected[expectedSize] = {
    testCallbackContainerMethods::getA(
      et,
      &testCallbackContainerMethods::s,
      nullptr
    ),
    testCallbackContainerMethods::getC(
      et,
      &testCallbackContainerMethods::s,
      nullptr
    ),
    testCallbackContainerMethods::getB(
      et,
      &testCallbackContainerMethods::s,
      nullptr
    )
  };

  // Run tests
  vector<CallbackResponse> actual = SUT.fireEvent(et);
  REQUIRE( actual.size() == expectedSize );

  int i = 0;
  for(auto item : actual) {
    REQUIRE( strncmp(
      item.getName().c_str(),
      expected[i].getName().c_str(),
      100
    ) == 0 );
    i++;
  }
}

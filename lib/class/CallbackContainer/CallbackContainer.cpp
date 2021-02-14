// PROJECT:         Indigo
// Author:          R. Javier
// File:            CallbackContainer.cpp
// Created:         2021-02-06
// Last Modified:   2021-02-06
// Details:
//                  Defines implementation of class CallbackContainer.
// Dependencies:
//                  n/a

// @includes
// #include <map>
// #include <vector>
#include <cstring>
#include <exception>
#include "CallbackContainer.hpp"
using namespace std;
using namespace Indigo;

// @ctor
CallbackContainer::CallbackContainer() {
  // Do nothing
}

// @function        getEventCallbacks()
// @description     Acquires the given EventType's Callback vector.
// @parameters      (sf::Event::EventType) et
//                                      The event type to get callbacks
//                                      from.
// @returns         (vector<Callback>*) cbs
//                                      The callback vector.
vector<Callback>* CallbackContainer::getEventCallbacks(
  sf::Event::EventType et
) {
  vector<Callback>* cbs = nullptr;
  map<sf::Event::EventType, vector<Callback>>::iterator cbIterator =
    cb_map_.find(et);
  if( cbIterator != cb_map_.end() ) {
    cbs = &cbIterator->second;
  }
  return cbs;
}

// @function        on()
// @description     Assigns the given Callback to the given EventType.
//                  Successive calls for the same EventType append new
//                  Callbacks to the end of the callback chain.
// @parameters      (sf::Event::EventType) et
//                                      The EventType to assign the
//                                      given Callback to.
//                  (Callback) cb       The Callback to assign.
// @returns         (bool) success      Returns true on success, false
//                                      otherwise.
bool CallbackContainer::on(
  sf::Event::EventType et,
  Callback cb
) {

  bool success = true;
  try {
    map<sf::Event::EventType, vector<Callback>>::iterator it =
      cb_map_.find(et);
    if( it == cb_map_.end() ) {
      vector<Callback> cbList;
      auto [it_item, success] = cb_map_.insert( {et, cbList} );
      it = it_item;
    }
    it->second.push_back(cb);
  } catch( const exception& err ) {
    printf("[ERR] %s\n", err.what());
    success = false;
  }

  return success;
}

// @function        off()
// @description     Unassigns the first Callback in the given EventType
//                  matching the given name.
// @parameters      (sf::Event::EventType) et
//                                      The EventType to unassign from.
//                  (string) cbName     The name of the callback to
//                                      unassign.
// @returns         (bool) success      Returns true on success, false
//                                      otherwise.
bool CallbackContainer::off(
  sf::Event::EventType et,
  string cbName
) {
  bool success = true;
  try{

    // Check if we have the given EventType
    map<sf::Event::EventType, vector<Callback>>::iterator it = cb_map_.find(et);
    if( it != cb_map_.end() ) {

      // Search for a Callback with a given name (linear complexity)
      vector<Callback>::iterator vectIt = it->second.begin();
      for(vectIt; vectIt != it->second.end(); ) {
        if(
          strncmp( vectIt->getName().c_str(), cbName.c_str(), 100 ) == 0
        ) {

          // If found, remove only this Callback and end
          vectIt = it->second.erase(vectIt);
          break;
        } else {
          ++vectIt;
        }
      }
    }
  } catch( const exception& err ) {
    printf("[ERR] %s\n", err.what());
    success = false;
  }

  return success;
}

// @function        fireEvent()
// @description     Executes the callbacks under the given EventType in
//                  insertion order.
// @parameters      (sf::Event::EventType) et
//                                      The EventType whose Callbacks
//                                      will be executed.
//                  (~sf::Event*) e     The Event object to pass to the
//                                      Callbacks (if any). Defaults to
//                                      nullptr. 
// @returns         (vector<CallbackResponse>) responses
//                                      A list of responses from each
//                                      executed Callback. If there were
//                                      no callbacks executed or the
//                                      given event has no registered
//                                      callbacks, this list is empty.
//                                      If an internal error occurred
//                                      (i.e. an issue in fireEvent(),
//                                      not an executed Callback), this
//                                      list's only item is an instance
//                                      of CallbackResponseFireFailed.
vector<CallbackResponse> CallbackContainer::fireEvent(
  sf::Event::EventType et,
  sf::Event* e
) {
  vector<CallbackResponse> responses;
  try {

    // Check if any Callbacks are registered for this EventType
    map<sf::Event::EventType, vector<Callback>>::iterator it = cb_map_.find(et);
    if( it != cb_map_.end() ) {
      
      // Run callbacks in order
      for(auto callback : it->second) {
        responses.push_back( callback.run( et, e ) );
      }
    }
  } catch( const exception& err ) {

    // On error, force response list to contain only a single item,
    // (an instance of CallbackResponseFireFailed)
    CallbackResponseFireFailed errResponse( err.what() );
    printf("[ERR] %s\n", err.what());
    responses.clear();
    responses.push_back( static_cast<CallbackResponse>(errResponse) );
  }

  return responses;
}

// @function        purgeEventCallbacks()
// @description     Clears all callbacks for the given EventType.
// @parameters      (sf::Event::EventType) et
//                                      The EventType to clear.
// @returns         (bool) success      Returns true on success, false
//                                      otherwise.
bool CallbackContainer::purgeEventCallbacks( sf::Event::EventType et ) {
  bool success = true;
  try {
    
    // Check if any Callbacks are registered for this EventType
    map<sf::Event::EventType, vector<Callback>>::iterator it = cb_map_.find(et);
    if( it != cb_map_.end() ) {

      // Clear the callbacks for the associated event, then remove the
      // event
      it->second.clear();
      cb_map_.erase(et);
    }
  } catch( const exception& err ) {
    printf("[ERR] %s\n", err.what() );
    success = false;
  }

  return success;
}

// @function        purgeAllCallbacks()
// @description     Clears all callbacks in this CallbackContainer.
// @parameters      n/a
// @returns         (bool) success      Returns true on success, false
//                                      otherwise.
bool CallbackContainer::purgeAllCallbacks() {
  bool success = true;
  try {
    cb_map_.clear();
  } catch( const exception& err ) {
    printf( "[ERR] %s\n", err.what() );
    success = false;
  }

  return success;
}

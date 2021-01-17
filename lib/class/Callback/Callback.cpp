// PROJECT:         Indigo
// Author:          R. Javier
// File:            Callback.cpp
// Created:         2021-01-23
// Last Modified:   2021-01-23
// Details:
//                  Defines implementation of class Callback.
// Dependencies:
//                  n/a

// @includes
#include <string>
#include <exception>
#include "Callback.hpp"
using namespace std;

// @ctor
Indigo::Callback::Callback(
  string name,
  Indigo::GameState* caller,
  Indigo::CallbackFunctionPointer funcPtr
) {
  name_ = name;
  caller_ = caller;
  funcPtr_ = funcPtr;
}

// @function        getName()
// @description     Name accessor.
// @parameters      n/a
// @returns         (string) name       Name given to this Callback
//                                      instance.
string Indigo::Callback::getName() {
  return name_;
}

// @function        getFunction()
// @description     Function pointer accessor.
// @parameters      n/a
// @returns         (CallbackFunctionPointer) funcPtr
//                                      A pointer to the associated
//                                      callback function.
Indigo::CallbackFunctionPointer Indigo::Callback::getFunction() {
  return funcPtr_;
}

// @function        createResponse()
// @description     Convenience method to create a CallbackResponse
//                  instance with name automatically set to this
//                  Callback instance's name.
// @parameters      (string) msg        Message to include in the
//                                      response.
// @returns         (CallbackResponse) response
//                                      CallbackResponse instance
//                                      with the given message and
//                                      name from this Callback
//                                      instance.
Indigo::CallbackResponse Indigo::Callback::createResponse( string msg ) {
  CallbackResponse response( name_, msg );
  return response;
}

// @function        run()
// @description     Executes the callback function pointed to by
//                  this Callback instance's funcPtr.
// @parameters      (sf::Event::EventType) et
//                                      Detected SFML EventType.
//                  (T*) caller         Pointer to the GameState (or
//                                      whatever owns this Callback's
//                                      enclosing CallbackContainer)
//                                      instance housing this Callback
//                                      instance.
//                  (~sf::Event*) e     A pointer to an event object
//                                      associated with the given type.
//                                      Only necessary if sf::Event
//                                      data needs to be used within
//                                      the callback. If omitted,
//                                      defaults to nullptr.
// @returns         (CallbackResponse) response
//                                      The response returned from the
//                                      callback function pointed to by
//                                      this Callback instance's
//                                      funcPtr.
Indigo::CallbackResponse Indigo::Callback::run(
  sf::Event::EventType et,
  sf::Event* e
) {
  try {
    return (*funcPtr_)( et, caller_, e );
  } catch( const exception& err ) {

    // If callback fails to catch exception, catch it here and
    // return its internal message to notify the Callback::run()
    // caller about what happened.
    Indigo::CallbackResponseUncaughtException response( err.what() );
    return response;
  }
}
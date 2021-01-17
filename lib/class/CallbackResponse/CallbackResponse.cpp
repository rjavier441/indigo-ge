// PROJECT:         Indigo
// Author:          R. Javier
// File:            CallbackResponse.cpp
// Created:         2021-01-16
// Last Modified:   2021-01-16
// Details:
//                  Defines implementation of class CallbackResponse and
//                  its derivatives.
// Dependencies:
//                  n/a

// @includes
#include <cstring>
#include "CallbackResponse.hpp"
using namespace std;


// @begin class CallbackResponse
// @ctor
Indigo::CallbackResponse::CallbackResponse( string n, string m ) {
  name = n;
  message = m;
}

// @function        getName()
// @description     Name accessor.
// @parameters      n/a
// @returns         (string) name       The name of this instance of
//                                      CallbackResponse.
string Indigo::CallbackResponse::getName() {
  return name;
}

// @function        getMessage()
// @description     Message accessor.
// @parameters      n/a
// @returns         (string) message    The message of this instance of
//                                      CallbackResponse.
string Indigo::CallbackResponse::getMessage() {
  return message;
}
// @end class CallbackResponse
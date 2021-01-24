// PROJECT:         Indigo
// Author:          R. Javier
// File:            Callback.hpp
// Created:         2021-01-23
// Last Modified:   2021-01-23
// Details:
//                  Public interface to class Callback.
// Dependencies:
//                  n/a
#pragma once

// @includes
#include <string>
#include <SFML/Window/Event.hpp>
#include "../../interface/NamedEntity/NamedEntity.hpp"
#include "../CallbackResponse/CallbackResponse.hpp"
#include "../GameState/GameState.hpp"
using namespace std;

namespace Indigo {

  // @forwardDecl     GameState
  // @description     Allows use of GameState pointers in Callback.
  class GameState;

  // @typedef         CallbackFunctionPointer
  // @description     Alias for callback function pointers associated
  //                  with instances of class Callback.
  typedef CallbackResponse (*CallbackFunctionPointer)(
    sf::Event::EventType, GameState*, sf::Event*
  );

  // @class           Callback
  // @description     A callback function pointer and associated data
  //                  container.
  class Callback : public NamedEntity {
    private:
      string name_;
      CallbackFunctionPointer funcPtr_;
      GameState* caller_;
    public:
      Callback(
        string name,
        GameState* caller,
        CallbackFunctionPointer funcPtr
      );

      string getName();
      
      CallbackFunctionPointer getFunction();
      CallbackResponse createResponse( string msg );
      CallbackResponse run(
        sf::Event::EventType et,
        sf::Event* e = nullptr
      );
  };
}
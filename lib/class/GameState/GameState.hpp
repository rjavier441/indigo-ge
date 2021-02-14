// PROJECT:         Indigo
// Author:          R. Javier
// File:            GameState.hpp
// Created:         2021-01-16
// Last Modified:   2021-01-16
// Details:
//                  Public interface of class GameState.
// Dependencies:
//                  DirectedNode
#pragma once

// @includes
#include<unordered_set>
#include<map>
#include "../../interface/DirectedNode/DirectedNode.hpp"
#include "../../interface/NamedEntity/NamedEntity.hpp"
// #include "../../class/CallbackContainer/CallbackContainer.hpp"
using namespace std;

namespace Indigo{

  // @class           GameState
  // @description     A game state that has knowledge of possible next
  //                  and previous states.
  class GameState : public NamedEntity {
    protected:
      static unsigned int total_distinct_states_;
      static map<string, GameState*> state_roster_;
    private:
      string name_;
      unsigned int id_;
      
      // TODO 2021-01-16: add callback container
      // CallbackContainer callbacks_;
    public:
      string getName();

      // TODO 2021-01-16: Add public methods
  };
}

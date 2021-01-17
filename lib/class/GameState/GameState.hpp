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
#include "../../interface/DirectedNode/DirectedNode.hpp"
using namespace std;

namespace Indigo{

    // @class           GameState
    // @description     A game state that has knowledge of possible next
    //                  and previous states.
    class GameState {
        private:
            static unsigned int totalDistinctStates;
            string name;
            unsigned int id;
            unordered_set<DirectedNode*> ancestors;
            unordered_set<DirectedNode*> descendants;
            
            // TODO 2021-01-16: add callbacks
    };
}

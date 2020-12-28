// PROJECT:         Indigo
// Author:          R. Javier
// File:            GameState.hpp
// Created:         March 23, 2019
// Last Modified:   March 23, 2019
// Details:
//                  This file contains definitions for various states that the
//                  game can be in
// Dependencies:
//                  n/a
#pragma once

// @enum            GameState
// @description     This enumerator defines various different
//                  states that the game can be in
enum class GameState {
    Error,
    Loading,
    Saving,
    Paused,
    Uninitialized
};

// EOF GameState.hpp
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

// @enum            GameState
// @description     This enumerator defines various different
// states that the game can be in
enum GameState {
    Error,
    Loading,
    Saving,
    Paused,
    Uninitialized
};
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "World.h"			// World
#include "Scaling.h"		// FloatScaler
#include "Menu2.h"			// Menu
#include "Overlay.h"		// OverlayMenu
#include "Utilities.h"		// Context
#include "Interactions.h"	// ActionType, Interaction
#include <vector>
using namespace std;

enum GameState {
	Error,
	Quitting,
	Saving,
	Loading,
	Paused,
	CheckingInventory,
	Interacting,
	NewGameSetup,
	ChangingMap,
	Uninitialized,
	Freeroaming,
	Fighting,
	Shopping,
	Cutscene
};
enum Difficulty { Easy, Normal, Hard };

class Game{
public:
	Game();
	Game(string title);

	void Start();	//run the game
	void changeState(GameState);	//change the game state

	sf::SoundBuffer buffer;
	sf::Sound soundEffect;
	sf::Music music;

private:
	bool getLastFrame(vector<sf::Sprite>* spritePtr, vector<sf::Texture>* texturePtr);	// draws the last frame shown from the Freeroaming state. Upon successful execution, "spritePtr" will contain all sprites that must be drawn to the WINDOW externally (i.e. from the Game's main loop), and "texturePtr" will contain all corresponding textures.
	bool execute(Interaction* ptr);	// perform the action defined by the interaction given by the "Interacting" GameState; returns true on success

	static GameState STATE;
	static GameState PREVSTATE;
	static sf::RenderWindow WINDOW;
	int windowX;
	int windowY;
	World WORLD;
	string gameTitle;
	vector<sf::VideoMode> videoModes;
	int currentVideoMode;
	FloatScaler splashScaler;	// scales the splash screen's background image
	FloatScaler menuScaler;	// scales a menu's button sprites/clickable regions
	FloatScaler menuBkgdScaler;	// scales a menu's backing
};
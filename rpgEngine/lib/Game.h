#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "World.h"
#include "Scaling.h"
#include <vector>
// #include "Player.h"
// #include "Character.h"
using namespace std;

enum GameState {
	Error,
	Quitting,
	Saving,
	Loading,
	Paused,
	CheckingInventory,
	NewGameSetup,
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

	// GameState StartScreen(sf::RenderWindow&);
private:
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
	// sf::Music MUSIC;
	// sf::Texture BACK;
	// sf::Font FONT;
};

// void initializeMenuScaling (sf::Sprite* menu, sf::Sprite* menubtn) {
	
// 	return;	
// }
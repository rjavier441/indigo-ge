#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
// #include <fstream>	//open()
#include <string>	//string
// #include <vector>
#include "Utilities.h"	//Direction, Position, TileCoord
#include "Items.h"	//Inventory, Items
using namespace std;

/*
Character.h: A Class for the general character and character variants (includes npcs, enemies, animals, and even you!).
*/

class Character{
public:
	Character();
	Character(string name);

	virtual Character& setName(string);
	// Character& setImages(vector<string> image_file_paths);
	virtual Character& setImage(string);	// Sets the Character's image file name (image must be stored in img/characters)
	bool setLocation(MapData* d, int xTile, int yTile);	// Sets the Character's tile position; returns true on success
	bool setPosition(int xPixel, int yPixel);	// Sets the Character's pixel position; returns true on success
	void setMoveDone(bool);
	void setPhase(int);
	void move(MapData* d, Move m);	// Moves the Character

	string getName();
	string getImage();
	Position getPosition();	// Returns the Character's pixel position
	TileCoord getLocation();
	Direction getDirection();
	Position* getPositionPtr();
	TileCoord* getLocationPtr();
	bool finishedMove();
	int getPhase();	// Gets the animation phase
private:
	string Name;
	string Image;	// A path to the file containing the 12 character images used to animate the Character
	Position Pos;	// A character's position in pixel coordinates
	TileCoord Loc;	// A character's location in tile coordinates

	// Animation variables
	Direction Dir;	// The direction the character is facing
	bool completedMove;	// A bool signifying if the character's animation is complete
	int animationPhase;	// The phase of a character animation. 0 = unmoved, 1 = start, 2 = middle, 3 = final
};

class Player : public Character {
public:
	Player();
	Player(string name, int level, int xp, int max_health, int hp, int armor, int magic, int attack_damage);

	Player& setName(string);
	Player& setImage(string);
	Player& setLevel(int);
	Player& setExperience(int);
	Player& setMaxHealth(int);
	Player& setHP(int);
	Player& setArmor(int);
	Player& setMagic(int);
	Player& setAttack(int);
	Player& pickup();	//adds an object to the Player's inventory

	int getLevel();
	int getExperience();
	int getMaxHealth();
	int getHP();
	int getArmor();
	int getMagic();
	int getAttack();
	Inventory* getInventoryPtr();
private:
	int Level;
	int Experience;
	int MaxHealth;
	int Health;
	int Armor;
	int Magic;
	int Attack;
	Inventory Bag;
};
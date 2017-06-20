#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>	//open(), eof()
#include <string>	//getline()
#include <vector>
#include <cstdlib>	//atoi()
#include "Character.h"
#include "Utilities.h"	//Position, TileCoord, SpawnPoint, Move, Direction
using namespace std;

/*
	World.h: Software to rule the world! (Loads worlds, handles tile/object collision, handles character movement)
	I plan to make worlds run like so: A single square image file will be displayed, and the player's view can be moved around the world image using sf::View. As for tile collisions and events, a world data file (.txt) will house all information about the tiles/objects within their respective coordinates world coordinates that way, when a character wants to move some direction, the software need only refer to the coordinates of the tile in the direction of the movement; I shall define the largest world size as 100x100 tiles (3200x3200 px)
	
	Tiles: Tiles are defined as 32px by 32px images that make up a world image.

	Coord File: Holds data about each tile coord of the world, as well as the world width/height in number of tiles, which are assumed to be 32px by 32px each (should be stored in maps/data).

	Image File: Holds the image of the world. Note that the world is intended to be a square with width/height of some multiple of 32px (images should be stored in maps/img). Note that the upper left tile is considered the origin tile (0,0), with +x axis heading right, and +y axis heading down.
*/

class World {
	/*
		After a world is instantiated, you must make sure to peform the following in order before being allowed to show/move in the world:
		1.> Set the window (unless done so with a constructor)
		2.> Load the map image and data with loadMap() and loadData()
		3.> Set the main character's animation image with setMainCharImage()
		4.> Set a location for spawn with setLocation()
	*/
public:
	World();
	World(sf::RenderWindow*);	// World object taking a pointer to the main window

	void setWorldName(string);	// Set the name of the world (not the map name)
	void setWindow(sf::RenderWindow*);	// Set the window pointer
	bool setLocation(int xtile = -1, int ytile = -1);	// Set's the player's map location in tiles; defaults to the first spawn point of a map
	bool loadMap(string);	// Load a map image; takes the name of the file (should be stored in maps/img); returns true on successful load
	bool loadData(string);	// Load a map coord data file; takes the name of the file (should be stored in maps/data); returns true on successful load
	
	string Show();	// Show the current world view on screen; returns a string of the requested state
	string getName();	// Get the world's name
	Player* getMainCharPtr();	// Returns a pointer to the main character

private:
	void animateChar(sf::Sprite* charToAnimate, Player* yourCharacter);	// Animates character movement
	bool parseData(string);	// Returns true on successful parsing and writing of data

	sf::RenderWindow* WINDOW;
	sf::RenderTexture MAPRENDER;
	sf::Texture MAP;
	sf::View VIEW;
	string WORLDNAME;
	vector <SpawnPoint> SPAWNPOINT;	// A vector of player entry points in a map
	MapData DATA;
	// sf::Clock clk;

	// Characters
	Player MainChar;
	
};
#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>	// open(), eof()
#include <string>	// getline()
#include <vector>	// vector
#include <cstdlib>	// atoi()
#include "Character.h"	// Player
#include "Utilities.h"	// Position, TileCoord, SpawnPoint, Move, Direction, Context
#include "Interactions.h"	// Interaction
#include "Tiles.h"	// TileIndex
using namespace std;

#define TILEDIR "maps/tiles/"

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
	/*
		After every map change, the following private variables are changed (in no particular order):
		1.> MAPRENDER
		2.> MAP
		3.> VIEW (?)
		4.> DATA
		5.> WORLDNAME (?)
		6.> DESTINATION
		7.> DESTINATIONSPAWN
		8.> musicFile
		9.> SPAWNPOINT
		10.> DOORWAY
	*/
public:
	World();
	World(sf::RenderWindow*);	// World object taking a pointer to the main window
	~World();	// destructor

	void setWorldName(string);	// Set the name of the world (not the map name)
	void setWindow(sf::RenderWindow*);	// Set the window pointer
	bool setLocation(int xtile = -1, int ytile = -1);	// Sets the player's map location in tiles; defaults to the first spawn point of a map
	bool setSpawn(string SpawnPointName);	// Sets the player's map location using the spawn name instead of coordinates
	void setDest(string dst);	// Sets "DESTINATION"
	void setDestSpawn(string dstspn);	// Sets "DESTINATIONSPAWN"
	bool loadMap(string);	// Load a map image; takes the name of the file (should be stored in maps/img); returns true on successful load
	bool loadData(string);	// Load a map coord data file; takes the name of the file (should be stored in maps/data); returns true on successful load
	bool loadTiles(string);	// Load the Tile Index file specified by the string path; returns true on successful load
	void animateChar(sf::Sprite* charToAnimate, Player* yourCharacter);	// Animates character movement
	
	string Show();		// Show the current world view on screen; returns a string of the requested state
	string getName();	// Get the world's name
	string getMusic();	// Get the world's music filename (must be stored in audio)
	string getDest();	// Returns "DESTINATION"
	string getDestSpawn();	// Returns "DESTINATIONSPAWN"
	Player* getMainCharPtr();	// Returns a pointer to the main character
	sf::View* getView();	// Returns ptr to the world's current view "VIEW"
	sf::Texture* getMap();	// Returns ptr to the map texture "MAP"
	sf::RenderTexture* getMapRender();	// returns ptr to the map render texture "MAPRENDER"
	Context* getContextPtr();	// returns a pointer to "MainCharContext"
	vector<Doorway>* getDoorwayPtr();	// returns a pointer to "DOORWAY"
	Interaction interact(int contextID);	// returns the interaction associated with the context action data in "contextID"; if either the contextID exceeds the bounds of Context's data vectors or the player is not able to perform the action, returns an "Nulled Interaction" (see Interactions.h)

private:
	void setContext();		// compiles data on all interactable objects within interaction range of the Main Character
	bool parseData(string);	// Returns true on successful parsing and writing of data
	bool adjacent(TileCoord a, TileCoord b);	// Returns true if the two tile coordinates are adjacent (i.e. next to each other vertically/horizontally, NOT diagonally)

	// SFML data
	sf::RenderWindow* WINDOW;
	sf::RenderTexture MAPRENDER;
	sf::Texture MAP;
	sf::View VIEW;
	
	// Map Data
	MapData DATA;
	string WORLDNAME;
	string DESTINATION;	// controls which map to spawn to during a map change (i.e. in GameState "ChangingMap")
	string DESTINATIONSPAWN;	// controls which spawn point to spawn in during a map change
	TileIndex* tileindex;
	string musicFile;
	// sf::Clock clk;

	// Spawnables
	vector <SpawnPoint> SPAWNPOINT;	// A vector of player entry points in a map
	vector <Doorway> DOORWAY;	// A vector of all doorways within the map

	// Characters
	Player MainChar;
	
	// Characters' Interaction Context
	Context MainCharContext;	// a struct to keep track of all objects around the player in interaction range
};
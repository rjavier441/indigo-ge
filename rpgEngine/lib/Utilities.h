#pragma once
#include <iostream>
#include <string>	//string
#include <vector>	//vector
using namespace std;

/*
	Utilities.h: A bunch of utilities for running the world! Contains all the necessary types of objects that World.h uses
*/

struct Position {	// Position of an object in the map in pixels 
	int x;
	int y;
};
struct TileCoord {	// Coordinate pair of an object in terms of map tiles
	TileCoord();	//default
	TileCoord(int, int);

	int x;
	int y;
};
struct SpawnPoint : TileCoord {
	SpawnPoint();	// default
	SpawnPoint(string,int,int);

	string spawnName;
};
enum Move { Up, Down, Left, Right };
enum Direction { U, D, L, R };
enum StatusEffect {		// i.e. Poisoning/blindness/etc.
	Poisoned,
	Blinded,
	Stunned,
	Slowed,
	Frightened
};
enum Buff {
	Strengthened,
	Clairvoyant,	// counter to blinded
	Recovered,
	Hastened,
	Courage
};


class MapData {
public:
	MapData();

	void setName(string);	// Sets the name of the map
	void setSize(int xpixels, int ypixels);
	bool setPassable(unsigned int xtile, unsigned int ytile, bool val);	// Set tile w/ coords ("xtile","ytile") as "val"; returns true on success

	string getName();	// Returns the map's name
	int pixelX();	// Returns x dimension of map in pixels
	int pixelY();	// Returns y dimension of map in pixels
	int getWidth();	// Returns x dimension of map in tiles
	int getHeight();	// Returns y dimension of map in tiles
	bool isPassable(int xtile, int ytile);	// Returns passability of a tile; takes the x,y coords of a 32 px^2 tile in the map
private:
	string Name;	// The name of the current map (mainly for guiding/reference purposes)

	// Map image dimensions in pixels
	int sizeX;
	int sizeY;
	
	// Map image dimensions in number of tiles (1 tile = 32 px^2)
	int Width;
	int Height;

	vector < vector <bool> > Passable;	// 2d vector (i.e. 2d array) containing the passability bools of each tile in the MAP
};
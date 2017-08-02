#pragma once
#include <iostream>
#include <cstdlib>		// itoa()
#include <cmath>	// sqrt(), pow(), floor()
#include <string>		// string
#include <vector>		// vector
#include "Interactions.h"	// MapObject, ActionType, Lockable, Exploitable
using namespace std;

/*
	Utilities.h: A bunch of utilities for running the world! Contains all the necessary types of objects that World.h uses, as well as several other helper constructs
*/

// Positionals
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
double getDistance(TileCoord a, TileCoord b);	// returns the distance between two tiles in the map 




// Spawnables
struct SpawnPoint : TileCoord {
	SpawnPoint();	// default
	SpawnPoint(string,int,int);

	string spawnName;
};
struct Doorway : TileCoord, Lockable, Exploitable {
	Doorway(int doorX, int doorY, int destX, int destY);	// default
	Doorway(string doorname, string destmap, int doorX, int doorY, string spawnTarget, string file);
	Doorway(string doorname, string destmap, int doorX, int doorY, int destX, int destY, string file);

	TileCoord getLocation();	// returns the location of the doorway within the map, in tile coordinates
	bool inRange(TileCoord t);		// returns true if t's distance away is <= this door's "Exploitable::minRange"

	string doorName;		// doorway name
	string filename;		// the filename for the door tile image
	string destMap;			// the map to transfer the player to
	string destSpawnName;	// the name of the spawn point to spawn the player at
	TileCoord destSpawn;	// the coordinates to spawn the player at (only used if destSpawnName is empty)
};




// Character Interactions/Contextuals
struct Context {	// info about objects in the map that a player can interact with
	void add(ActionType a, MapObject o, TileCoord t, int elementID, string d = "");	// adds a context action and associates it with a type of map object, allows an optional description
	int size();								// returns the number of 
	vector<string>* getDescriptionPtr();	// returns pointer to "actionDescription"
	vector<string>* getActionStringPtr();	// returns pointer to "actionStr"
	vector<MapObject>* getActionObjectPtr();	// returns pointer to "actionObject"
	vector<TileCoord>* getObjectLocationPtr();	// returns pointer to "objectLocation"
	vector<int>* getElemIdPtr();			// returns pointer to "elemId"
	vector<ActionType>* getActionPtr();			// returns pointer to "action"

	void clear();	// clears all context data
private:
	/*
		Note: Each time add is called, a single piece of information is added to each of the following vectors. Thus, all items are arranged by index (i.e. action[0] has its string name and description at index 0 of the corresponding vectors, and so on for action[1], action[2], ...
	*/
	vector<string> actionDescription;	// an optional description of each action
	vector<string> actionStr;			// the string representations of actions in "action" corresponding to their respective ActionTypes
	vector<MapObject> actionObject;		// the object types in the world associated with each action in "action"
	vector<TileCoord> objectLocation;	// the coordinate location of the object(s) in "actionObject" within the map (in tiles)
	vector<int> elemId;				// an ID number used to locate the data of the object in question within the world object's memory (e.g. the index referencing a doorway in World::DOORWAY)
	vector<ActionType> action;			// the action enumerations associated with the objects in "actionObject"
	int currentSize;					// the current amount of elements in the context set (consequently equals the size of each of the above vectors)
};





// Movement
enum Move { Up, Down, Left, Right };
enum Direction { U, D, L, R };




// Effects
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




// Map Data
class MapData {
public:
	MapData();

	void setName(string);	// Sets the name of the map
	void setSize(int xpixels, int ypixels);
	bool setPassable(unsigned int xtile, unsigned int ytile, bool val);	// Set tile w/ coords ("xtile","ytile") as "val"; returns true on success
	void clear();	// clear all data

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

	vector < vector <bool> > Passable;	// 2d vector (i.e. 2d array) containing the passability bools of each FLOOR tile in the MAP
};
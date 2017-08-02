#include "Utilities.h"
using namespace std;

/*Struct TileCoord*/
TileCoord::TileCoord () {
	x = 0;
	y = 0;
}
TileCoord::TileCoord (int a, int b) {
	x = a;
	y = b;
}



/*Distance Formula (using TileCoords)*/
double getDistance (TileCoord a, TileCoord b) {
	// Apply the distance formula
	double x_a = static_cast<double>(a.x);
	double x_b = static_cast<double>(b.x);
	double y_a = static_cast<double>(a.y);
	double y_b = static_cast<double>(b.y);
	double distance = sqrt( pow(x_b - x_a, 2) + pow(y_b - y_a, 2) );

	return distance;
}



/*Struct SpawnPoint*/
SpawnPoint::SpawnPoint () : TileCoord (0,0) {
	spawnName = "";
}
SpawnPoint::SpawnPoint (string s, int xInt, int yInt) : TileCoord (xInt,yInt) {
	spawnName = s;
}



/*Struct Doorway*/
Doorway::Doorway (int x, int y, int destX, int destY) : TileCoord (x, y), Lockable (), Exploitable (1) {
	doorName = "Door " + static_cast<char>(x) + ',' + static_cast<char>(y);
	destMap = "";
	destSpawnName = "";
	filename = "";
	destSpawn.x = destX;
	destSpawn.y = destY;
	action = AT_ENTER;
}
Doorway::Doorway (string n, string d, int x, int y, string spawnTarget, string f) : TileCoord (x, y), Lockable (), Exploitable (1) {
	doorName = n;
	destMap = d;
	destSpawnName = spawnTarget;
	filename = f;
	destSpawn.x = -1;
	destSpawn.y = -1;
	action = AT_ENTER;
}
Doorway::Doorway (string n, string d, int x, int y, int destX, int destY, string f) : TileCoord (x, y), Lockable (), Exploitable (1) {
	doorName = n;
	destMap = d;
	destSpawnName = "";
	filename = f;
	destSpawn.x = destX;
	destSpawn.y = destY;
	action = AT_ENTER;
}

TileCoord Doorway::getLocation () {
	return TileCoord(x, y);
}

bool Doorway::inRange (TileCoord t) {
	TileCoord* doorLocation = this;
	if (getDistance(*doorLocation, t) <= static_cast<double>(minRange)) {
		return true;
	}
	return false;
}





/*struct Context*/
void Context::add (ActionType a, MapObject o, TileCoord t, int id, string d) {
	string temp;

	actionObject.push_back(o);
	actionDescription.push_back(d);
	objectLocation.push_back(t);
	elemId.push_back(id);
	action.push_back(a);
	switch (a) {
		case AT_UNDEFINED:
			temp = "Undefined";
			break;
		case AT_ENTER:
			temp = "Enter";
			break;
		case AT_EXAMINE:
			temp = "Examine";
			break;
		case AT_PICKUP:
			temp = "PickUp";
			break;
		default:
			temp = "_err_";
			break;
	}
	actionStr.push_back(temp);
	currentSize++;

	return;
}
int Context::size () {
	return currentSize;
}
vector<string>* Context::getDescriptionPtr () {
	return &actionDescription;
}
vector<string>* Context::getActionStringPtr () {
	return &actionStr;
}
vector<MapObject>* Context::getActionObjectPtr () {
	return &actionObject;
}
vector<TileCoord>* Context::getObjectLocationPtr () {
	return &objectLocation;
}
vector<int>* Context::getElemIdPtr () {
	return &elemId;
}
vector<ActionType>* Context::getActionPtr () {
	return &action;
}

void Context::clear () {
	actionObject.clear();
	objectLocation.clear();
	elemId.clear();
	actionDescription.clear();
	actionStr.clear();
	action.clear();
	currentSize = 0;
	return;
}





/*Class MapData*/
MapData::MapData() {
	Name = "";
	sizeX = 0;
	sizeY = 0;
	Width = 0;
	Height = 0;
}
void MapData::setName (string n) {
	Name = n;
}
void MapData::setSize (int x, int y) {
	// Set variables
	sizeX = x;
	sizeY = y;
	Width = x/32;
	Height = y/32;

	// Reallocate space in the 2d vector array
	Passable.resize(Width);
	for (int i = 0; i < Width; i++) {
		Passable[i].resize(Height);
	}
}
bool MapData::setPassable (unsigned int x, unsigned int y, bool val) {
	if (x < Width && y < Height) {
		Passable[x][y] = val;
		return true;
	} else {
		cout << endl << "[World] Error: Requested passability coordinate out of bounds" << endl;
		return false;
	}
}
void MapData::clear () {
	if (!Passable.empty()) Passable.clear();
	Name = "";
	sizeX = 0;
	sizeY = 0;
	Width = 0;
	Height = 0;
	return;
}
string MapData::getName () {
	return Name;
}
int MapData::pixelX () {
	return sizeX;
}
int MapData::pixelY () {
	return sizeY;
}
int MapData::getWidth () {
	return Width;
}
int MapData::getHeight () {
	return Height;
}
bool MapData::isPassable (int x, int y) {
	return Passable[x][y];
}
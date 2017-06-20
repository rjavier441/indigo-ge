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



/*Struct SpawnPoint*/
SpawnPoint::SpawnPoint () : TileCoord (0,0) {
	spawnName = "";
}
SpawnPoint::SpawnPoint (string s, int xInt, int yInt) : TileCoord (xInt,yInt) {
	spawnName = s;
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
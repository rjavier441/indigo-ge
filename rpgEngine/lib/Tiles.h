#ifndef TILES_H
#define TILES_H

#include <iostream>	// cout, endl
#include <cstdio>	// printf()
#include <cstdlib>	// atoi()
#include <cstring>	// strtok()
#include <fstream>	// open(), eof()
#include <vector>	// type vector<>
#include <string>	// type string
using namespace std;

enum TileType {
	Floor,		// 0
	Door,		// 1
	Overhang,	// 2
	Wall		// 3
};

struct Tile {	// a tile's data structure
	char key;
	short id;
	string filename;
	int type;
	// char* name;	// c-string
	string name;
	bool passable;
	short height;
	// misc: TBD
};
typedef struct Tile Tile;

class TileIndex {	// a complete list of all tiles in the game
public:
	TileIndex();

	bool read(string path);	// reads a tile index file; returns true on a successful read
	Tile tile(char key);	// returns a tile object corresponding to the tile "key"
private:
	bool parseData(string data);	// parses a line of "row" data

	vector<Tile> tiles;
	int size;
};

#endif
/* TILES_H */
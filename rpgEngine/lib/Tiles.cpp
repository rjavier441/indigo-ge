#include "Tiles.h"

/*
	Class TileIndex
*/
TileIndex::TileIndex () {
	size = 0;
}

bool TileIndex::read (string p) {
	ifstream file;

	// Open a stream to the Tile Index file
	file.open(p.c_str());
	if (file.fail()) {
		cout << "[Tile] Tile index file " << p << " failed to load" << endl;
		file.close();
		return false;
	}
	// cout << "[Tile] Reading Tile Index file " << p << endl;	// debug

	// Load all tile data
	int lineNum = 0;
	while (!file.eof()) {
		string temp;

		getline(file, temp);
		if (!parseData(temp)) {
			cout << "[Tile] Failed to load data at line " << lineNum << endl;
			file.close();
			return false;
		}
		lineNum++;
	}

	// Close file stream when done reading
	file.close();

	return true;
}

Tile TileIndex::tile (char key) {
	// Search for the indicated tile's info w/ the key
	int index = static_cast<int>(key) - 33;	// offset of 33 since '!' (the first of the available keys) is ascii code 33
	return tiles[index];
}

bool TileIndex::parseData (string s) {
	Tile temptile;

	// Separate the data string into its segments and set the corresponding temptile members
	// cout << "[Tile] Parsing Data " << s << endl;	// debug
	char* pch = strtok((char*) s.c_str(), " ");
	int i = 0;
	while (pch != NULL) {
		// printf("%s\n", pch);	// debug: print the token in front
		switch (i) {
			case 0: {	// character key & key id
				temptile.key = pch[0];
				// printf("Key:%c\n", temptile.key);	// debug
				temptile.id = static_cast<int>(pch[0]);
				// printf("ID:%d\n", temptile.id);	// debug
				break;
			}
			case 1: {	// tile name
				temptile.name = static_cast<string>(pch);
				// printf("Name:%s\n", temptile.name.c_str());	// debug
				break;
			}
			case 2: {	// passability
				temptile.passable = static_cast<bool>(atoi(pch));
				// printf("Passable:%d\n", temptile.passable);	// debug
				break;
			}
			case 3: {	// world height
				temptile.height = atoi(pch);
				// printf("Height:%d\n", temptile.height);	// debug
				break;
			}
			case 4: {	// image name (tile images must be stored in "pathToGame/maps/tiles")
				temptile.filename = static_cast<string>(pch);
				break;
			}
			case 5: {	// tile type
				temptile.type = atoi(pch);
				break;
			}
			default: {
				cout << "[Tile] Extra Data: " << pch << endl;
				break;
			}
		}
		i++;
		pch = strtok(NULL," ");	// move onto the next token (?)
	}

	// Update the tileindex with this type of tile
	tiles.push_back(temptile);

	return true;
}
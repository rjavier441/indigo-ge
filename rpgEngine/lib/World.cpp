#include "World.h"
using namespace std;

/*Class World*/
World::World () {
	DATA.setName("???");
	MAPRENDER.create(3200,3200);	// Default rendertexture size to max map size in pixels
	MainChar.setName("Antonius").setLevel(0).setExperience(0).setMaxHealth(100).setHP(100).setArmor(
		100).setMagic(1).setAttack(10);
	MainChar.printInventory();	// debug
	MainChar.setImage("hero_test.png");
	DESTINATION = "";
	DESTINATIONSPAWN = "";
	tileindex = NULL;
}
World::World (sf::RenderWindow* w) {
	WINDOW = w;
	DATA.setName("???");
	MAPRENDER.create(3200,3200);	// Default rendertexture size to max map size in pixels
	MainChar.setName("Antonius").setLevel(0).setExperience(0).setMaxHealth(100).setHP(100).setArmor(100).setMagic(1).setAttack(10);
	MainChar.setImage("hero_test.png");
	DESTINATION = "";
	DESTINATIONSPAWN = "";
	tileindex = NULL;
}
World::~World () {
	delete tileindex;
}

void World::setWorldName (string n) {
	WORLDNAME = n;
}
void World::setWindow (sf::RenderWindow* w) {
	WINDOW = w;
}
bool World::setLocation (int x, int y) {
	if (x == -1 && y == -1) {
		if (SPAWNPOINT.empty()) {
			cout << endl << "[World] Error: No spawn points found" << endl;
			return false;
		} else {
			// cout << endl << "[World] Spawning to default spawn point" << endl;
			return MainChar.setLocation(&DATA, SPAWNPOINT[0].x, SPAWNPOINT[0].y);
		}
	} else {
		if (x > DATA.getWidth() || y > DATA.getHeight() || x < 0 || y < 0) {
			cout << endl << "[World] Error: Location out of bounds" << endl;
			return false;
		} else {
			return MainChar.setLocation(&DATA, x, y);
		}
	}
}
bool World::setSpawn (string spawnPointName) {
	if (SPAWNPOINT.empty()) {
		printf("[World] Error: No spawn points found\n");	// debug
		return false;
	}

	// Compare given name with all spawn point names
	for (int i = 0; i < SPAWNPOINT.size(); i++) {
		if (spawnPointName == SPAWNPOINT[i].spawnName) {
			MainChar.setLocation(&DATA, SPAWNPOINT[i].x, SPAWNPOINT[i].y);
			return true;
		}
	}

	printf("[World] Error: No matching spawn \"%s\"", spawnPointName.c_str());	// debug
	return false;
}
void World::setDest (string dst) {
	DESTINATION = dst;
	return;
}
void World::setDestSpawn (string dstspn) {
	DESTINATIONSPAWN = dstspn;
	return;
}
bool World::loadMap (string img) {
	string tempfilename = "maps/img/" + img;

	if(!MAP.loadFromFile(tempfilename)){
		cout << endl << "[World] Error: " << img << " failed to load" << endl;
		return false;
	}

	return true;
}
bool World::loadData (string datafile) {
	ifstream file;
	string tempfilename = "maps/data/" + datafile;

	// Clear data from the previous map, if any
	if (!SPAWNPOINT.empty()) SPAWNPOINT.clear();
	if (!DOORWAY.empty()) DOORWAY.clear();
	DATA.clear();

	// Open file
	file.open(tempfilename.c_str());
	if(file.fail()){
		cout << endl << "[World] Error: " << datafile << " failed to load" << endl;
		file.close();
		return false;
	}

	// Load map data
	// short state = 0;	// 0 = naming, 1 = sizing, 2 = coords
	int lineNum = 0;
	printf("[World] #### Loading Map Data ####\n");	// debug
	while (!file.eof()) {
		string temp;

		getline(file, temp);
		lineNum++;
		if (!parseData(temp)) {
			cout << endl << "[World] Error: Failed to load data file line " << lineNum << ": \"" << temp << "\"" << endl;
			file.close();
			return false;
		}
	}
	printf("[World] #### Done ####\n");	// debug

	file.close();
	return true;
}
bool World::loadTiles (string path) {
	if (tileindex != NULL) delete tileindex;	// clear tileindex 
	tileindex = new TileIndex;

	if (!tileindex->read(path)) {
		cout << endl << "[World] Failed to load tile index file" << endl;
		return false;
	}

	return true;
}
void World::animateChar (sf::Sprite* sprite, Player* thePlayer) {
	/*
		This function animates character movement by directly manipulating the texture rectangle of the sprite pointer passed in.
		It also moves a character by 2 pixels at a time, animating each image in 4 phases as moveImg->stillImg->otherMoveImg->stillImg.
	*/
	// sf::Time timeElapsed = clk.getElapsedTime();

	TileCoord loc = thePlayer->getLocation();
	Position pos = thePlayer->getPosition();
	Direction myDir = thePlayer->getDirection();

	int goalPixelX = loc.x * 32;
	int goalPixelY = loc.y * 32;

	// If animation is already complete (i.e. char is staying still), keep char facing its current direction
	if (thePlayer->finishedMove()) {
		switch (myDir) {
			case D: {
				sprite->setTextureRect(sf::IntRect(32,0,32,32));
				break;
			}
			case L: {
				sprite->setTextureRect(sf::IntRect(32,32,32,32));
				break;
			}
			case R: {
				sprite->setTextureRect(sf::IntRect(32,64,32,32));
				break;
			}
			case U: {
				sprite->setTextureRect(sf::IntRect(32,96,32,32));
				break;
			}
			default:
				break;
		}
		return;
	}

	// If position is already at goal location, do nothing
	else if (pos.x == goalPixelX && pos.y == goalPixelY) {
		return;
	} else {
		thePlayer->setMoveDone(false);
	}

	// Determine the desired direction of movement
	Move goalMove;
	if (goalPixelX < pos.x) {
		goalMove = Left;
	} else if (goalPixelX > pos.x) {
		goalMove = Right;
	} else if (goalPixelY < pos.y) {
		goalMove = Up;
	} else if (goalPixelY > pos.y) {
		goalMove = Down;
	} else {
		return;	// In case of an invalid movement trigger
	}

	// Determine which part of the character texture to use based on the phase of movement the character is in
	int imgX = 0, imgY = 0, imgSizeX = 32, imgSizeY = 32;
	switch (goalMove) {
		case Down: {
			imgY = 0;	// top row of character tiles is Down direction
			if (thePlayer->getPhase() == 0 || thePlayer->getPhase() == 2) {
				imgX = 32;
				if ((goalPixelY - pos.y ) % 16 == 0) thePlayer->setPhase(thePlayer->getPhase() + 1);
			} else if (thePlayer->getPhase() == 1) {
				imgX = 0;
				if ((goalPixelY - pos.y ) % 16 == 0) thePlayer->setPhase(thePlayer->getPhase() + 1);
			} else if (thePlayer->getPhase() == 3) {
				imgX = 64;
				thePlayer->setPhase(0);
			}
			break;
		}
		case Left: {
			imgY = 32;	// 2nd row of character tiles is Left direction
			if (thePlayer->getPhase() == 0 || thePlayer->getPhase() == 2) {
				imgX = 32;
				if ((pos.x - goalPixelX) % 16 == 0) thePlayer->setPhase(thePlayer->getPhase() + 1);
			} else if (thePlayer->getPhase() == 1) {
				imgX = 0;
				if ((pos.x - goalPixelX) % 16 == 0) thePlayer->setPhase(thePlayer->getPhase() + 1);
			} else if (thePlayer->getPhase() == 3) {
				imgX = 64;
				thePlayer->setPhase(0);
			}
			break;
		}
		case Right: {
			imgY = 64;	// 3rd row of character tiles is Right direction
			if (thePlayer->getPhase() == 0 || thePlayer->getPhase() == 2) {
				imgX = 32;
				if ((goalPixelX - pos.x) % 16 == 0) thePlayer->setPhase(thePlayer->getPhase() + 1);
			} else if (thePlayer->getPhase() == 1) {
				imgX = 0;
				if ((goalPixelX - pos.x) % 16 == 0) thePlayer->setPhase(thePlayer->getPhase() + 1);
			} else if (thePlayer->getPhase() == 3) {
				imgX = 64;
				thePlayer->setPhase(0);
			}
			break;
		}
		case Up: {
			imgY = 96;	// 4th row of character tiles is Up direction
			if (thePlayer->getPhase() == 0 || thePlayer->getPhase() == 2) {
				imgX = 32;
				if ((pos.y - goalPixelY) % 16 == 0) thePlayer->setPhase(thePlayer->getPhase() + 1);
			} else if (thePlayer->getPhase() == 1) {
				imgX = 0;
				if ((pos.y - goalPixelY) % 16 == 0) thePlayer->setPhase(thePlayer->getPhase() + 1);
			} else if (thePlayer->getPhase() == 3) {
				imgX = 64;
				thePlayer->setPhase(0);
			}
			break;
		}
		default:
			break;
	}

	// Edit sprite texture rectangle
	sprite->setTextureRect(sf::IntRect(imgX, imgY, imgSizeX, imgSizeY));

	// Move sprite to the new position
	int movementSpeed = 2;	//movement speed in pixels (must be a multiple of 2)
	int newX = 0, newY = 0;
	if (goalMove == Left) {
		newX = pos.x - movementSpeed;
		newY = pos.y;
	} else if (goalMove == Right) {
		newX = pos.x + movementSpeed;
		newY = pos.y;
	} else if (goalMove == Up) {
		newX = pos.x;
		newY = pos.y - movementSpeed;
	} else if (goalMove == Down) {
		newX = pos.x;
		newY = pos.y + movementSpeed;
	} else {
		return;	// In case of an invalid movement trigger
	}
	thePlayer->setPosition(newX,newY);

	// If the new position is the goal position, signify that the move animation is complete
	if (thePlayer->getPosition().x == goalPixelX && thePlayer->getPosition().y == goalPixelY) {
		thePlayer->setMoveDone(true);
	}

	// cout << endl << "[World] thePlayer->setMoveDone(:" << thePlayer->setMoveDone( << " x:" << thePlayer->getPosition().x << " y:" << thePlayer->getPosition().y << " goalx:" << goalPixelX << " goaly:" << goalPixelY;
}

string World::Show () {
	// Format world view
	Position MainCharacterPos = MainChar.getPosition();
	VIEW.setCenter(MainCharacterPos.x, MainCharacterPos.y);
	VIEW.setSize(480, 480);	// lock the view to show a 15x15 tile area (480x480 px)
	// VIEW.setViewport(sf::FloatRect(0.2f, 0.2, 0.6f, 0.6f));
	MAPRENDER.clear(sf::Color::Black);

	// Setup and draw map base image (i.e. floors/walls)
	sf::Sprite mapImg(MAP);
	MAPRENDER.draw(mapImg);

	// TODO: Setup interactive image(s) (i.e. place animatable doors, or overhanging arches; things with world height > 0)
	// Setup and draw Doorways
	for (int i = 0; i < DOORWAY.size(); i++) {
		// Load door image and create sprite
		sf::Texture doorTexture;
		if (!doorTexture.loadFromFile(TILEDIR + DOORWAY[i].filename)) {
			printf("[World] Error: unable to load door texture \"%s\"\n", DOORWAY[i].filename.c_str());
			return "Error";
		}
		sf::Sprite doorImg(doorTexture);

		// Properly size and "phase" the door image and view (i.e. size the door tile's view as a 32x32px img, and select the correct door image for the state of the door)
		int doorImgYpx = 0;
		// printf("MC:%d,%d %s:%d,%d Adj:%d Locked:%d, Actn:%d, Dist:%f, inRange:%d\n",
		// 	MainChar.getLocation().x,
		// 	MainChar.getLocation().y,
		// 	DOORWAY[i].doorName.c_str(),
		// 	DOORWAY[i].getLocation().x,
		// 	DOORWAY[i].getLocation().y,
		// 	static_cast<int>(adjacent(MainChar.getLocation(), DOORWAY[i].getLocation())),
		// 	static_cast<int>(DOORWAY[i].isLocked()),
		// 	static_cast<int>(DOORWAY[i].action),
		// 	getDistance(MainChar.getLocation(), DOORWAY[i].getLocation()),
		// 	static_cast<int>(DOORWAY[i].inRange(MainChar.getLocation()))
		// );	// debug
		if (adjacent(MainChar.getLocation(), DOORWAY[i].getLocation())) {
			// printf("[World] Character is next to \"%s\"\n", DOORWAY[i].doorName.c_str());	// debug
			doorImgYpx = 32;	// selects the "half-open" door image
		} else {
			// printf("[World] Character is away from \"%s\"\n", DOORWAY[i].doorName.c_str());	// debug
		}
		doorImg.setTextureRect(sf::IntRect(0, doorImgYpx, 32, 32));

		// Properly position the door in the map
		doorImg.setPosition(sf::Vector2f(DOORWAY[i].x * 32, DOORWAY[i].y * 32));

		// Draw door to map
		MAPRENDER.draw(doorImg);

		// printf("[World] Doorway \"%s\", %s\n", DOORWAY[i].doorName.c_str(), DOORWAY[i].filename.c_str());	// debug
	}

	// TODO: Setup misc. images (i.e. obtainable items, or animatable blocks like lava/water)

	// Draw stuff in map render texture and "save it" (display it)
	MAPRENDER.display();

	// Create the main character's sprite
	sf::Texture HeroTexture;
	if (MainChar.getImage() == "") {
		cout << endl << "[World] Error: Main character image not set" << endl;
		return "Error";
	}
	if (!HeroTexture.loadFromFile("img/characters/" + MainChar.getImage())) {
		cout << endl << "[World] Error: " << MainChar.getImage() << " failed to load" << endl;
		return "Error";
	}
	sf::Sprite HeroSprite(HeroTexture);
	HeroSprite.setPosition( MainCharacterPos.x, MainCharacterPos.y );

	// TODO: Draw NPC sprite(s)

	// Animate the main char image to simulate movement
	animateChar(&HeroSprite, &MainChar);

	// TODO: Animate NPC sprite movement(s)

	// Clear window
	WINDOW->clear();

	// Draw map texture and hero to window
	sf::Sprite mapImgSprite(MAPRENDER.getTexture());
	WINDOW->draw(mapImgSprite);
	WINDOW->setView(VIEW);
	WINDOW->draw(HeroSprite);

	// TODO: Draw NPC sprite(s) to window

	// Draw HUD elements: World Name, Minimap, etc.
	// sf::Texture worldInfoTexture;
	// if (!worldInfoTexture.loadFromFile("img/")) {
	// 	printf("[World] Error: World info texture \"%s\" failed to load\n", "img/");
	// 	return "Error";
	// }


	// Event processing
	sf::Event event;
	while (WINDOW->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			return "Quitting";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return "Paused";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {	// Launch interaction menu
			return "Interact";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			MainChar.move(&DATA, Left);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			MainChar.move(&DATA, Right);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			MainChar.move(&DATA, Down);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			MainChar.move(&DATA, Up);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {	// Launch Inventory menu
			return "Inventory";
		}
	}

	// Set main character's context
	setContext();

	// Display
	WINDOW->display();
	return "";
}
string World::getName () {
	return DATA.getName();
}
string World::getMusic () {
	return musicFile;
}
string World::getDest () {
	return DESTINATION;
}
string World::getDestSpawn () {
	return DESTINATIONSPAWN;
}
Player* World::getMainCharPtr () {
	return &MainChar;
}
sf::View* World::getView () {
	return &VIEW;
}
sf::Texture* World::getMap () {
	return &MAP;
}
sf::RenderTexture* World::getMapRender () {
	return &MAPRENDER;
}
Context* World::getContextPtr () {
	return &MainCharContext;
}
vector<Doorway>* World::getDoorwayPtr () {
	return &DOORWAY;
}
Interaction World::interact (int cid) {
	Interaction temp;
	bool canPerformAction = false;
	int action = static_cast<int>(MainCharContext.getActionPtr()->at(cid));
	int target = static_cast<int>(MainCharContext.getActionObjectPtr()->at(cid));
	int eid = MainCharContext.getElemIdPtr()->at(cid);
	TileCoord targetLocation = MainCharContext.getObjectLocationPtr()->at(cid);

	// Check vector bounds
	if (cid < 0 || cid >= MainCharContext.size()) {
		printf("[World] Context access bounds exceeded (invalid index \"%d\")\n", cid);
		return temp;
	}

	printf("[World] cid %d, action %d to target %d @ eid %d\n", cid, action, target, eid);	// debug

	// Check action conditions (i.e. determine if the player has the ability to perform the requested action on the indicated object; if so, populate the interaction with the relevant data and return, otherwise, return a "nulled interaction")
	switch (action) {
		case AT_UNDEFINED:
			// Do nothing...
			break;
		case AT_ENTER:
			switch (target) {
				case MO_UNKNOWN:
					// Do nothing...
					break;
				case MO_DOORWAY: {
					// Determine which door the player is interacting with, using context data's location
					int target_x = targetLocation.x;
					int target_y = targetLocation.y;
					for (int k = 0; k < DOORWAY.size(); k++) {
						int x = DOORWAY[k].getLocation().x;
						int y = DOORWAY[k].getLocation().y;

						// If DOORWAY[k]'s location matches the targetLocation, then the character's context indicates that DOORWAY[k] is the desired door to perform the action upon
						if (target_x == x && target_y == y) {
							// Check if the doorway is locked; if not, allow the player to "enter" through the doorway
							if (!DOORWAY[k].isLocked()) canPerformAction = true;

							// If it is locked, check that the player has the correct key in inventory to unlock it
							else if (getMainCharPtr()->getInventoryPtr()->hasKey(DOORWAY[k].doorName)) canPerformAction = true;
							break;
						}
					}

					break;
				}
				case MO_TRAVELPOINT:
					/* TODO */
					break;
				default:
					printf("[World] Invalid MapObject associated with ActionType \"AT_ENTER\"\n");
					break;
			}
			break;
		case AT_EXAMINE:
			/* TODO */
			break;
		case AT_PICKUP:
			/* TODO */
			break;
		default:
			printf("[World] Unrecognized ActionType\n");
			break;
	}

	// If player is able to perform the "action" with the "target", populate temp with context data; else leave it as a "nulled interaction"
	if (canPerformAction) {
		temp.action = static_cast<ActionType>(action);
		temp.actionStr = MainCharContext.getActionStringPtr()->at(cid);
		temp.actionDesc = MainCharContext.getDescriptionPtr()->at(cid);
		temp.target = static_cast<MapObject>(target);
		temp.cid = cid;
		temp.eid = eid;
	}

	return temp;
}

void World::setContext () {	// keep track of all doorways, item drops, chests, etc. that the player can interact with (in the current frame)
	// Clear context from previous frame
	MainCharContext.clear();

	// Keep track of all doorways within range
	for (int i = 0; i < DOORWAY.size(); i++) {
		// if Door is not in range, skip
		if (!DOORWAY[i].inRange(MainChar.getLocation())) continue;
		
		// else add it to the main character's context
		// printf("[World] %s in range!\n", DOORWAY[i].doorName.c_str());	// debug
		MainCharContext.add(AT_ENTER, MO_DOORWAY, DOORWAY[i].getLocation(), i, DOORWAY[i].doorName);
	}

	/* TODO: */
	// Keep track of all other interactable objects, etc.

	return;
}
bool World::parseData (string str) {
	/*
		See Map data readme for data details
	*/
	string header = "";
	vector <string> data;

	// Grab the header
	// printf("[World] \tProcessing data \"%s\" (%d chars)", str.c_str(), static_cast<int>(str.length()));	// debug
	int i;
	bool colonDetected = false;
	for (i = 0; i < str.length(); i++) {
		if (str[i] == ':') {
			colonDetected = true;
			break;
		} else {
			header += str[i];
		}
	}
	if (!colonDetected) {
		cout << endl << "[World] \tError: Invalid data detected" << endl;
		return false;
	}
	// printf("\tHeader - %s\n", header.c_str());	// debug

	// Grab the data
	i++;
	string tempdata = "";
	for (i; i < str.length(); i++) {
		if (str[i] == ' ') {	// if a space is encountered
			data.push_back(tempdata);
			tempdata = "";
		} else if (i == str.length() - 1) {	// else if current char is the last in the string
			tempdata += str[i];	// add last char
			data.push_back(tempdata);
			// printf("[World] adding last \"%c\" (char %d) - tempdata:%d\n", str[i], i, static_cast<int>(tempdata.length()));	// debug
		} else {
			tempdata += str[i];
			// printf("[World] adding \"%c\" (char %d) - tempdata:%d\n", str[i], i, static_cast<int>(tempdata.length()));	// debug
		}
	}

	// Handle adding data
	if (header == "name") {		// Load map name
		string tempstring = "";
		if (data.size() > 1) {	// if name longer than 1 word, concat data to single string
			for (int k = 0; k < data.size(); k++) {
				if (k > 0) {
					tempstring += " ";
				}
				tempstring += data[k];
			}
		} else if (data.size() == 1) {
			tempstring = data[0];
		} else {
			cout << endl << "[World] \tError: Data file missing name parameter" << endl;
			return false;
		}

		printf("[World] \tLoading Map \"%s\"\n", tempstring.c_str());
		DATA.setName(tempstring);
	} else if (header == "size") {		// Load map pixel dimensions
		string temp = data[0];
		int divider = 0;
		bool dividerDetected = false;
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == 'x') {
				divider = i;
				dividerDetected = true;
				break;
			}
		}

		if (!dividerDetected) {
			cout << endl << "[World] \tError: Invalid size parameter format" << endl;
			return false;
		} else if (divider == 0 || divider == temp.length() - 1) {
			cout << endl << "[World] \tError: Invalid size parameter" << endl;
			return false;
		}

		string xstr = temp.substr(0, divider);
		string ystr = temp.substr(divider + 1);
		printf("[World] \tSizing map to \"%sx%s\"\n", xstr.c_str(), ystr.c_str());	// debug
		DATA.setSize( atoi(xstr.c_str()), atoi(ystr.c_str()) );
	} else if (header == "spawn") {		// Load map spawn point(s)
		if (data.size() != 3) {
			cout << endl << "[World] \tError: Invalid spawn point data" << endl;
			return false;
		}

		string spawnPointName = data[0];
		string spawnX = data[1];
		string spawnY = data[2];

		printf("[World] \tLoading Spawn point \"%s\"\n", spawnPointName.c_str());	// debug
		SpawnPoint newSpawnPoint (spawnPointName, atoi(spawnX.c_str()), atoi(spawnY.c_str()));

		SPAWNPOINT.push_back(newSpawnPoint);
	} else if (header == "music") {
		printf("[World] \tLoading Map music \"%s\"\n", data[0].c_str());	//debug
		musicFile = data[0];
	} else if (header == "coord") {		// Load map coordinate data
		if (data.size() != 3) {
			cout << endl << "[World] \tError: Invalid coord data" << endl;
			return false;
		}

		string xTileCoord = data[0];
		string yTileCoord = data[1];
		string canPass = data[2];

		DATA.setPassable( atoi(xTileCoord.c_str()), atoi(yTileCoord.c_str()), static_cast<bool>( atoi(canPass.c_str()) ) );
	} else if (header == "row") {	// Load a series of coordinate data
		// Check if invalid parsing occurred
		if (data.size() != 2) {
			cout << endl << "[World] \tError: Invalid cooridnate series data" << endl;
			return false;
		}

		// Acquire row number
		int yTileCoord = atoi(data[0].c_str());
		int xTileCoord;

		// Interperet each character in the tile row
		string temp = data[1];
		// printf("row:%s (%d chars)\n", data[0].c_str(), static_cast<int>(temp.length()));	// debug
		for (xTileCoord = 0; xTileCoord < temp.length(); xTileCoord++) {
			// Acquire information about a tile
			// printf("xTileCoord: %d ", xTileCoord);	// debug
			Tile k = tileindex->tile(temp[xTileCoord]);
			// cout << "[World] Tile Data: " << k.key << " " << k.id << " " << k.name << " " << k.passable << " " << k.height << endl;	// debug

			// Store passability data for the current tile
			DATA.setPassable(xTileCoord, yTileCoord, k.passable);
			// printf("[World] Setting passability\n");	// debug

			/* TODO: */
			// Store name data for the current tile
			// Store world height data for the current tile
			// Store action data for the current tile
		}
	} else if (header == "doorway") {
		// Check for correct amount of data
		if (data.size() != 6) {
			printf("\n[World] \tError: Invalid doorway data\n");	// debug
			return false;
		}

		// Acquire Doorway's coordinates and destination info
		string doorName = data[0];
		char doorTileKey = data[1][0];
		int doorX = atoi(data[2].c_str());
		int doorY = atoi(data[3].c_str());
		string destMap = data[4];
		string destSpawnPointName = data[5];
		string doorTileFileName = tileindex->tile(doorTileKey).filename;
		// printf("[World] \tDoorway \"%s\", key:%c, file:%s, coord:(%d,%d), dest:%s @%s\n", doorName.c_str(), doorTileKey, doorTileFileName.c_str(), doorX, doorY, destMap.c_str(), destSpawnPointName.c_str());	// debug

		// Store the doorway's data
		Doorway tempDoorway(doorName, destMap, doorX, doorY, destSpawnPointName, doorTileFileName);
		// printf("[World] \tDoorway \"%s\", file:%s, coord:(%d,%d), dest:%s @%s\n", tempDoorway.doorName.c_str(), tempDoorway.filename.c_str(), tempDoorway.x, tempDoorway.y, tempDoorway.destMap.c_str(), tempDoorway.destSpawnName.c_str());	// debug
		DOORWAY.push_back(tempDoorway);
	} else if (header == "end") {
		return true;
	} else {
		cout << endl << "[World] \tError: Invalid header was read, aborting" << endl;
		return false;
	}

	return true;
}
bool World::adjacent (TileCoord a, TileCoord b) {
	// Apply the distance formula
	double distance = getDistance(a, b);

	if (distance == 1.0) return true;	// if the blocks are less than 2 blocks apart, return true
	else return false;
}
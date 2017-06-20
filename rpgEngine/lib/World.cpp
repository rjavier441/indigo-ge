#include "World.h"
using namespace std;

/*Class World*/
World::World () {
	DATA.setName("???");
	MAPRENDER.create(3200,3200);	// Default rendertexture size to max map size in pixels
	MainChar.setName("Antonius").setLevel(0).setExperience(0).setMaxHealth(100).setHP(100).setArmor(100).setMagic(1).setAttack(10);
	MainChar.setImage("hero_test.png");
}
World::World (sf::RenderWindow* w) {
	WINDOW = w;
	DATA.setName("???");
	MAPRENDER.create(3200,3200);	// Default rendertexture size to max map size in pixels
	MainChar.setName("Antonius").setLevel(0).setExperience(0).setMaxHealth(100).setHP(100).setArmor(100).setMagic(1).setAttack(10);
	MainChar.setImage("hero_test.png");
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

	file.close();
	return true;
}

string World::Show () {
/*
	// Format world view
		VIEW.setCenter(POS.x,POS.y);
		VIEW.setSize(DATA.pixelX(),DATA.pixelY());
		// VIEW.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));	// shows center-half rectangle of screen
		VIEW.setViewport(sf::FloatRect(0.2f, 0.2, 0.6f, 0.6f));

		// Setup map image
		MAPRENDER.clear(sf::Color::Black);

		// Draw stuff in map render texture and "save it" (display it)
		sf::Sprite mapImg(MAP);
		MAPRENDER.draw(mapImg);
		MAPRENDER.display();

		// Create the hero sprite
		sf::Texture HeroTexture;
		if (MAINCHARIMAGE.empty()) {
			cout << endl << "[World] Error: Main character image not set" << endl;
			return "Error";
		}
		if (!HeroTexture.loadFromFile("img/characters/" + MAINCHARIMAGE)) {
			cout << endl << "[World] Error: " << MAINCHARIMAGE << "failed to load" << endl;
			return "Error";
		}
		sf::Sprite HeroSprite(HeroTexture);
		HeroSprite.setPosition( POS.x, POS.y );

		// Animate the main char image to simulate movement
		animate(&HeroSprite, &POS, &LOCATION);

		// Clear window
		WINDOW->clear();

		// Draw map texture and hero to window
		sf::Sprite mapImgSprite(MAPRENDER.getTexture());
		WINDOW->draw(mapImgSprite);
		WINDOW->setView(VIEW);
		WINDOW->draw(HeroSprite);

		// Event processing
		sf::Event event;
		while (WINDOW->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				return "Quitting";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				return "Paused";
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				move(Left);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				move(Right);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				move(Down);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				move(Up);
			}
		}

		// Display
		WINDOW->display();
		return "";
*/
	// Format world view
	Position MainCharacterPos = MainChar.getPosition();
	VIEW.setCenter(MainCharacterPos.x, MainCharacterPos.y);
	VIEW.setSize(DATA.pixelX(), DATA.pixelY());
	// VIEW.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));	// shows center-half rectangle of screen
	VIEW.setViewport(sf::FloatRect(0.2f, 0.2, 0.6f, 0.6f));

	// Setup map image
	MAPRENDER.clear(sf::Color::Black);

	// Draw stuff in map render texture and "save it" (display it)
	sf::Sprite mapImg(MAP);
	MAPRENDER.draw(mapImg);
	MAPRENDER.display();

	// Create the main character's sprite
	sf::Texture HeroTexture;
	if (MainChar.getImage() == "") {
		cout << endl << "[World] Error: Main character image not set" << endl;
		return "Error";
	}
	if (!HeroTexture.loadFromFile("img/characters/" + MainChar.getImage())) {
		cout << endl << "[World] Error: " << MainChar.getImage() << "failed to load" << endl;
		return "Error";
	}
	sf::Sprite HeroSprite(HeroTexture);
	HeroSprite.setPosition( MainCharacterPos.x, MainCharacterPos.y );

	// Draw NPC sprite(s)

	// Animate the main char image to simulate movement
	animateChar(&HeroSprite, &MainChar);

	// Animate NPC sprite movement(s)

	// Clear window
	WINDOW->clear();

	// Draw map texture and hero to window
	sf::Sprite mapImgSprite(MAPRENDER.getTexture());
	WINDOW->draw(mapImgSprite);
	WINDOW->setView(VIEW);
	WINDOW->draw(HeroSprite);

	// Draw NPC sprite(s) to window


	// Event processing
	sf::Event event;
	while (WINDOW->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			return "Quitting";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return "Paused";
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

	// Display
	WINDOW->display();
	return "";
}
string World::getName () {
	return DATA.getName();
}
Player* World::getMainCharPtr () {
	return &MainChar;
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
bool World::parseData (string str) {
	/*
		Data files will be formatted like so:
		name:[Name of Map]\n
		size:[Size of Map]\n
		spawn:[Spawn Point Data 0]\n
		spawn:[Spawn Point Data 1]....\n
		coord:[Coord Data 0]\n
		coord:[Coord Data 1]....\n
		end:end

		Name Data will be formatted like so:
		name:[alphanumeric name with or without spaces]\n

		Size Data will be formatted like so:
		size:[xPixels]x[yPixels]\n

		Spawn Point Data (each map will have at least one spawn tile where the player spawns) will be formatted like so:
		spawn:[Alphanumeric Spawn Point Name with underscores as space chars] [xTileCoord] [yTileCoord]\n

		Coord Data will be formatted like so:
		coord:[xTileCoord] [yTileCoord] p[passability is 0 or 1]\n
	*/
	string header = "";
	vector <string> data;

	// Grab the header
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
		cout << endl << "[World] Error: Invalid data detected" << endl;
		return false;
	}

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
		} else {
			tempdata += str[i];
		}
	}

	// Handle adding data
	if (header == "name") {		// Load map name
		string tempstring = "";
		if (data.size() > 1) {
			for (int k = 0; k < data.size(); k++) {
				if (k > 0) {
					tempstring += " ";
				}
				tempstring += data[k];
			}
		} else if (data.size() == 1) {
			tempstring = data[0];
		} else {
			cout << endl << "[World] Error: Data file missing name parameter" << endl;
			return false;
		}

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
			cout << endl << "[World] Error: Invalid size parameter format" << endl;
			return false;
		} else if (divider == 0 || divider == temp.length() - 1) {
			cout << endl << "[World] Error: Invalid size parameter" << endl;
			return false;
		}

		string xstr = temp.substr(0, divider);
		string ystr = temp.substr(divider + 1);
		DATA.setSize( atoi(xstr.c_str()), atoi(ystr.c_str()) );
	} else if (header == "spawn") {		// Load map spawn point(s)
		if (data.size() != 3) {
			cout << endl << "[World] Error: Invalid spawn point data" << endl;
			return false;
		}

		string spawnPointName = data[0];
		string spawnX = data[1];
		string spawnY = data[2];

		SpawnPoint newSpawnPoint (spawnPointName, atoi(spawnX.c_str()), atoi(spawnY.c_str()));

		SPAWNPOINT.push_back(newSpawnPoint);
	} else if (header == "coord") {		// Load map coordinate data
		if (data.size() != 3) {
			cout << endl << "[World] Error: Invalid coord data" << endl;
			return false;
		}

		string xTileCoord = data[0];
		string yTileCoord = data[1];
		string canPass = data[2];

		DATA.setPassable( atoi(xTileCoord.c_str()), atoi(yTileCoord.c_str()), static_cast<bool>( atoi(canPass.c_str()) ) );
	} else if (header == "end") {
		return true;
	} else {
		cout << endl << "[World] Error: Invalid header was read, aborting" << endl;
		return false;
	}

	return true;
}

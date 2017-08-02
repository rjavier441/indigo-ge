#include "Game.h"
using namespace std;

Game::Game(){
	gameTitle = "undefined";
	videoModes = sf::VideoMode::getFullscreenModes();
	currentVideoMode = 0;
}
Game::Game(string t){
	gameTitle = t;
	videoModes = sf::VideoMode::getFullscreenModes();
	currentVideoMode = 0;
}

// GameState Game::StartScreen(sf::RenderWindow& window){
	
// }

void Game::Start(){
	// Initialize local variables
	Difficulty gameDifficulty;
	bool playingMusic = false;
	bool menuUnscaled = true;
	// sf::SoundBuffer buffer;
	// sf::Sound soundEffect;
	// sf::Music music;
	sf::Clock clk;
	OverlayMenuData omData;
	int testi = 0;

	// Acquire supported display modes for later user customization
	printf("[Game] Acquiring supported Display Modes...");
	for (size_t sz = 0; sz < videoModes.size(); ++sz) {
		sf::VideoMode md = videoModes[sz];
		// printf("Mode %d: %dx%d - %d bpp\n", (int) sz, md.width, md.height, md.bitsPerPixel);
	}
	printf("Done\n");

	// Create main window (use first full screen mode as display mode) & record initial window sizes
	WINDOW.create(videoModes[currentVideoMode], gameTitle);	// uses first mode in videoModes
	windowX = videoModes[currentVideoMode].width;
	windowY = videoModes[currentVideoMode].height;
	// WINDOW.create(sf::VideoMode::getDesktopMode(), gameTitle);

	// Create window icon
	sf::Image gameIcon;
	if (!gameIcon.loadFromFile("img/resources/Point-19_carat_diamond_cut_blue_Yogo_sapphireCROP.jpg")) {
		cout << endl << "[Game] Icon load failed" << endl;
	} else {
		WINDOW.setIcon(256, 256, gameIcon.getPixelsPtr());
	}

	// Load all recurring files here; loading/reloading them during each state could be taxing on the cpu/gpu
	sf::Texture splashTexture;
	sf::Font splashFont;
	sf::Texture pauseTexture;
	sf::Font pauseFont;
	sf::Texture newgameTexture;
	sf::Font newgameFont;
	printf("[Game] Loading resources...");	// debug
	if (!newgameTexture.loadFromFile("img/splashscreen2.png")){	// Load new game window background
		cout << endl << "[Game] Error: newgameTexture load unsuccessful" << endl;
		changeState(Error);
		WINDOW.close();
	};
	if (!newgameFont.loadFromFile("fonts/Garuda.ttf")){	// Load splash screen font
		cout << endl << "[Game] Error: newgameFont load unsuccessful" << endl;
		changeState(Error);
		WINDOW.close();
	};
	if (!pauseTexture.loadFromFile("img/pausescreen.png")){	// Load pause screen background
		changeState(Error);
		cout << endl << "[Game] Error: pauseTexture load unsuccessful" << endl;
		WINDOW.close();
	}
	if (!pauseFont.loadFromFile("fonts/FreeSerif.ttf")){	// Load pause screen font
		changeState(Error);
		cout << endl << "[Game] Error: pauseFont load unsuccessful" << endl;
		WINDOW.close();
	};
	if (!splashTexture.loadFromFile("img/splashscreen2.png")){	// Load splash screen background
		cout << endl << "[Game] Error: splashTexture load unsuccessful" << endl;
		changeState(Error);
		WINDOW.close();
	};
	if (!splashFont.loadFromFile("fonts/Garuda.ttf")){	// Load splash screen font
		cout << endl << "[Game] Error: splashFont load unsuccessful" << endl;
		changeState(Error);
		WINDOW.close();
	};
	printf("Done\n");	// debug

	// Load tile set information
	printf("[Game] Loading tile set...");
	if (!WORLD.loadTiles("maps/tiledb/TileIndex.txt")) {
		cout << endl << "[Game] Error: WORLD could not load Tile Data" << endl;
		changeState(Error);
		WINDOW.close();
	}
	printf("Done\n");

	// Setup a world variable for later use
	WORLD.setWindow(&WINDOW);

	// Begin processing game state changes in a loop
	while(WINDOW.isOpen()){
		// Acquire Current Window Size
		sf::Vector2u winsize = WINDOW.getSize();
		// printf("%d %d\n", winsize.x, winsize.y);

		// Respond to state transitions
		switch(STATE){
			case Uninitialized:{
				// Initialize scaling of menu objects

				// Determine desired element positions
				unsigned int TitleX = videoModes[currentVideoMode].width/30;	// 1/30 of screen width
				unsigned int TitleY = videoModes[currentVideoMode].height/30;	// 1/30 of screen height
				// printf("%d %d\n", videoModes[currentVideoMode].width, videoModes[currentVideoMode].height);	// debug

				// Load splash screen music
				if (!playingMusic){
					playingMusic = true;
					if (!music.openFromFile("audio/750286_Sedisverse-Ost--Shadows.ogg")){
						changeState(Error);
						break;
					}
					music.setLoop(true);
					music.play();
				}

				// Initialize and properly scale background objects
				sf::Sprite splashSprite(splashTexture);
				splashScaler.scale(&splashSprite, &WINDOW);
				splashSprite.setScale(splashScaler.xScale(), splashScaler.yScale());
				sf::Text splashTitle(gameTitle,splashFont,70);
				splashTitle.setColor(sf::Color::White);
				splashTitle.setStyle(sf::Text::Italic);
				splashTitle.setPosition(TitleX,TitleY);

				// After drawing menu elements, Draw title to window
				WINDOW.clear();
				WINDOW.draw(splashSprite);
				WINDOW.draw(splashTitle);

				// Initialize and properly scale main menu
				Menu mainmenu("MainMenu", &WINDOW);
				mainmenu.setWindowDimensions(windowX, windowY);	// to properly scale mouse coords
				if (!menuUnscaled) {	// Note: FloatScaler defaults to x= 0 and y=0
					// Change scale so that it matches the ratios of the FIRST FRAME (Note: not doing so will cause the sprites to be scaled in an awkward way when resizing window)
					mainmenu.setScale(menuScaler.xScale(), menuScaler.yScale());	// to properly scale menu items
					mainmenu.setBackgroundScale(menuBkgdScaler.xScale(), menuBkgdScaler.yScale());	// to properly scale menu backings
				}
				list<string> btn;
				btn.push_front("Quit");
				// btn.push_front("Pause");
				btn.push_front("Load");
				btn.push_front("New");
				mainmenu.assign(btn);
				if (menuUnscaled) {	// only scale on START
					menuUnscaled = false;
					menuScaler.scale(mainmenu.getScaleX(), mainmenu.getScaleY());	// scale menu buttons and clickable regions
					menuBkgdScaler.scale(mainmenu.getBackgroundScaleX(), mainmenu.getBackgroundScaleY());	// scale menu backings
				}
				mainmenu.setTitlePosition(windowX/22, windowY/2);	// to properly position the menu title

				// Draw main menu
				string status = mainmenu.Show();

				// Handle menu response
				if (status != ""){
					// cout << endl << "[Game] Status: " << status << endl;
					// Load and play a sound when an option was selected
					if (!buffer.loadFromFile("audio/sfx/fire_bow_sound-mike-koenig.wav")) changeState(Error);
					soundEffect.setBuffer(buffer);
					soundEffect.setVolume(25);
					soundEffect.play();

					// // Stop background music
					// if (playingMusic){
					// 	playingMusic = false;
					// 	music.stop();
					// }
				}
				if (status == "New"){
					changeState(NewGameSetup);
				} else if (status == "Quitting" || status == "Quit"){
					changeState(Quitting);
				} else if (status == "Error"){
					changeState(Error);
				}

				break;
			}
			case Paused:{
				// Initialize objects
				sf::Sprite pauseSprite(pauseTexture);
				pauseSprite.setScale(splashScaler.xScale(), splashScaler.yScale());
				// sf::Text pauseText("Paused", pauseFont, 50);

				// Draw to window after resetting and clearing
				WINDOW.clear();
				WINDOW.setView(WINDOW.getDefaultView());
				WINDOW.draw(pauseSprite);
				// WINDOW.draw(pauseText);

				// Initialize pause menu
				StatMenu pausemenu("Paused", &WINDOW, WORLD.getMainCharPtr());
				pausemenu.setWindowDimensions(windowX, windowY);	// to properly scale mouse coords
				pausemenu.setScale(menuScaler.xScale(), menuScaler.yScale());	// to properly scale menu items
				pausemenu.setBackgroundScale(menuBkgdScaler.xScale(), menuBkgdScaler.yScale());	// to properly scale menu backings
				list<string> btn;
				btn.push_front("Quit");
				btn.push_front("Return");
				pausemenu.assign(btn);
				pausemenu.setTitlePosition(windowX/22, windowY/2);	// to properly position the menu title

				// Draw pause menu
				string status = pausemenu.Show();

				// Handle menu response
				if (status != ""){
					// Load and play a sound when an option was selected
					if (!buffer.loadFromFile("audio/sfx/fire_bow_sound-mike-koenig.wav")) changeState(Error);
					soundEffect.setBuffer(buffer);
					soundEffect.setVolume(25);
					soundEffect.play();
				}
				if (status == "Return") {
					changeState(PREVSTATE);
				} else if (status == "Quitting" || status == "Quit") {
					changeState(Quitting);
				} else if (status == "Error") {
					changeState(Error);
				}

				break;
			}
			case CheckingInventory:{
				// WORLD.getMainCharPtr()->printInventory();	// debug

				// Draw to window after resetting and clearing
				WINDOW.clear();
				WINDOW.setView(WINDOW.getDefaultView());

				// Initialize inventory menu
				InventoryMenu imenu("Inventory", &WINDOW, WORLD.getMainCharPtr());
				imenu.setSlotImg("img/menu_inventory_slot_default.png");
				imenu.setWindowDimensions(windowX, windowY);	// to properly scale mouse coords
				imenu.setScale(menuScaler.xScale(), menuScaler.yScale());	// to properly scale 
				imenu.setBackgroundScale(menuBkgdScaler.xScale(), menuBkgdScaler.yScale());	// to properly scale menu backings
				list<string> btn;
				btn.push_front("Return");
				// btn.push_front("Weapons");
				// btn.push_front("Quest Items");
				// btn.push_front("Consumables");
				// btn.push_front("Armor");
				imenu.assign(btn);
				imenu.setTitlePosition(windowX/22, windowY/2);	// to properly position the menu title

				// Draw inventory menu
				string status = imenu.Show();

				// Handle menu response
				if (status != "") {
					// Load and play a sound when an option was selected
					if (!buffer.loadFromFile("audio/sfx/fire_bow_sound-mike-koenig.wav")) changeState(Error);
					soundEffect.setBuffer(buffer);
					soundEffect.setVolume(25);
					soundEffect.play();
				}
				if (status == "Return") {
					changeState(PREVSTATE);
				} else if (status == "Quitting") {
					changeState(Quitting);
				} else if (status == "Error") {
					changeState(Error);
				}
				
				break;
			}
			case Interacting:{	// i.e. open doors, loot corpses, pick up quest items/objects, etc.
				Player* mc = WORLD.getMainCharPtr();
				Position mcPos = mc->getPosition();
				vector<sf::Sprite> iDrawings;
				vector<sf::Texture> iTextures;

				// Acquire elements of the last frame
				if (!getLastFrame(&iDrawings, &iTextures)) {
					printf("[Game] Failed to draw previous Freeroaming frame\n");
					changeState(Error);
					break;
				}

				// Test: remain in interaction mode for 3 sec
				// sf::Time now = clk.getElapsedTime();
				// float sec = now.asSeconds();
				// if (testi == 0) {
				// 	printf("[Game] Interacting...");
				// 	testi = 1;
				// }
				// if (sec >= 3.0) {
				// 	printf("Done\n");
				// 	changeState(Freeroaming);
				// 	testi = 0;
					clk.restart();
				// }

				// Draw previous frame
				WINDOW.clear();
				for (int i = 0; i < iDrawings.size(); i++) {
					WINDOW.draw(iDrawings[i]);
				}
				// WINDOW.draw(randTxt);
				// WINDOW.display();	// handled by Overlay.h

				// Draw interaction overlay menu
				OverlayMenu om(&WINDOW, mcPos.x + 32, mcPos.y);
				om.setName("Interact");
				om.setFont("CaviarDreams.ttf");
				/*
					om.setWidth(128);
					om.setFontSize(60);
					om.setTitlePos(0, -60);
					om.setOptionOffset(0,0);
					om.setDynamic();	// done automatically
				*/
				om.setBackground("overlay_default.png");
				om.setCursorImg("overlay_cursor_default.png");
				om.setCursorPos(&omData.cursor_position);
				om.setViewTop(&omData.range_top);
				om.showTitle();
				
				/* TODO: */
				// Acquire context (determine what nearby objects the character can interact with, and how to interact with them)
				Context* mcContext = WORLD.getContextPtr();
				
				// Add the options (i.e. action names) of each available context action
				vector<string>* vectPtr = mcContext->getActionStringPtr();
				for (int i = 0; i < mcContext->size(); i++){
					om.addOption(vectPtr->at(i).c_str());
				}

				string status = om.Show();

				// Handle all possible interaction state feedback here
				if (status != "") {
					if (status == "Error") {
						changeState(Error);
					} else if (status == "Cancel" || status == "Return") {
						changeState(PREVSTATE);
					} else {
						/* TODO: */
						// Determine appropriate action based on the returned option.
						Interaction temp = WORLD.interact(om.getCursorPosition() - 1);	// cursor index is offet by 1 due to "Cancel" being the first button

						printf("[Game] Interaction: %d -> %d\n", static_cast<int>(temp.action), static_cast<int>(temp.target));	//debug
						execute(&temp);	// Note: this also automatically peforms a changeState() call
						// changeState(PREVSTATE);	// debug
					}

					printf("[Game] Overlay status: %s\n", status.c_str());	// debug
				}

				break;
			}
			case Loading:{
				break;
			}
			case Saving:{
				
				break;
			}
			case NewGameSetup:{
				// Determine desired element positions
				unsigned int TitleX = videoModes[currentVideoMode].width/30;	// 1/30 of screen width
				unsigned int TitleY = videoModes[currentVideoMode].height/30;	// 1/30 of screen 

				// Initialize objects
				sf::Sprite newgameSprite(newgameTexture);
				sf::Text newgameTitle(gameTitle,newgameFont,70);
				newgameSprite.setScale(splashScaler.xScale(), splashScaler.yScale());
				newgameTitle.setColor(sf::Color::White);
				newgameTitle.setStyle(sf::Text::Italic);
				newgameTitle.setPosition(TitleX,TitleY);

				// Draw to window after clearing
				WINDOW.clear();
				WINDOW.draw(newgameSprite);
				WINDOW.draw(newgameTitle);

				// Initialize new game setup menu
				Menu setup("New Game - Difficulty", &WINDOW);
				setup.setWindowDimensions(windowX, windowY);	// to properly scale mouse coords
				setup.setScale(menuScaler.xScale(), menuScaler.yScale());	// to properly scale menu items
				setup.setBackgroundScale(menuBkgdScaler.xScale(), menuBkgdScaler.yScale());	// to properly scale menu backings
				list<string> btns;
				btns.push_front("Return");
				btns.push_front("Hard");
				btns.push_front("Normal");
				btns.push_front("Easy");
				setup.assign(btns);
				setup.setTitlePosition(windowX/22, windowY/2);	// to properly position the menu title

				// Draw newgame setup menu
				string status = setup.Show();

				// Handle menu response
				if (status != ""){
					// cout << endl << "[Game] Status: " << status << endl;
					// Load and play a sound when an option was selected
					if (!buffer.loadFromFile("audio/sfx/fire_bow_sound-mike-koenig.wav")) changeState(Error);
					soundEffect.setBuffer(buffer);
					soundEffect.setVolume(25);
					soundEffect.play();

					if (status == "Return"){
						changeState(PREVSTATE);
						break;
					} else if (status == "Quitting") {
						changeState(Quitting);
						break;
					} else {
						// Stop background music
						if (playingMusic){
							playingMusic = false;
							music.stop();
						}

						// Set game difficulty
						if (status == "Easy") {
							gameDifficulty = Easy;
						} else if (status == "Normal") {
							gameDifficulty = Normal;
						} else if (status == "Hard"){
							gameDifficulty = Hard;
						} else {
							gameDifficulty = Easy;
						}

						// Prepare player's starting inventory
						// Item Deed("Deed", "Quest Item", "img/items/scroll.png", "The deed to your mansion", 0,1);
						// Item EightBall("8-ball", "Quest Item", "img/Farm-Fresh_sport_8ball.png", "A magic 8-ball that can make decisions for you", 1,1);
						// Item Cutlass("Cutlass", "Weapon", "img/items/cutlass.png", "A plain but well made shortsword", 10,1);
						// Item PlatedShield("Plated Shield", "Armor", "img/items/shield.png", "A cast-iron shield", 10, 1);
						// Item Tome("Valindyr's Tome", "Quest Item", "img/items/Valindyrs_Tome.png", "The memorial tome of Sir Valindyr III", 4, 1);
						// WORLD.getMainCharPtr()->pickup(Deed);
						// WORLD.getMainCharPtr()->pickup(EightBall);
						// WORLD.getMainCharPtr()->pickup(Cutlass);
						// WORLD.getMainCharPtr()->pickup(PlatedShield);
						// WORLD.getMainCharPtr()->pickup(Tome);

						// Prepare the starting world
						WORLD.setWorldName("Kingdom of York");	// name of realm, NOT map
						WORLD.setDest("TestArea");
						WORLD.setDestSpawn("Spawn1");
						changeState(ChangingMap);
					}
				}

				break;
			}
			case ChangingMap:{
				// Stop music
				if (playingMusic) {
					playingMusic = false;
					music.stop();
				}

				// Load map
				printf("[Game] Loading map \"%s\"...\n", WORLD.getDest().c_str());	// debug
				if (!WORLD.loadMap(WORLD.getDest() + ".png")) {
					cout << endl << "[Game] Map load failed" << endl;
					changeState(Error);
					break;
				}
				if (!WORLD.loadData(WORLD.getDest() + ".txt")) {
					cout << endl << "[Game] Data load failed" << endl;
					changeState(Error);
					break;
				}
				printf("[Game] Done loading map\n");	// debug
				
				// Set the player's location (no args = default spawn point)
				printf("[Game] Spawning at spawn point \"%s\"...", WORLD.getDestSpawn().c_str());	// debug
				if (!WORLD.setSpawn(WORLD.getDestSpawn())) {
					printf("[Game] Error: spawn unsuccessful\n");	// debug
					changeState(Error);
					break;
				}
				printf("[Game] Done spawning\n");	// debug

				changeState(Freeroaming);

				break;
			}
			case Shopping:{
				break;
			}
			case Fighting:{
				break;
			}
			case Freeroaming:{
				// Load map music
				if (!playingMusic){
					playingMusic = true;
					if (!music.openFromFile("audio/" + WORLD.getMusic())){
						printf("[Game] Error: Unable to play map music \"\"");
						changeState(Error);
						break;
					}
					music.setLoop(true);
					music.play();
				}

				string status = WORLD.Show();
				
				if (status != "") {
					if (status == "Quitting") {
						changeState(Quitting);
					} else if (status == "Interact") {
						// Acquire a snapshot of the prev frame (i.e. so that the interaction menu can be overlayed above it to give the illusion that the game is paused while the user decides what to do)
						// sf::Vector2u winSize = WINDOW.getSize();
						// if (!temporaryTexture.create(winSize.x, winSize.y)) {
						// 	printf("[Game] Unable to create temporaryTexture\n");
						// 	changeState(Error);
						// 	break;
						// }
						// temporaryTexture.update(WINDOW);
						clk.restart();
						omData.cursor_position = 0;	// reset OverlayMenu cursor to point to option 0
						omData.range_top = 0;	// reset OverlayMenu range top to point to the first "viewRange" number of options
						changeState(Interacting);
					} else if (status == "Inventory") {
						changeState(CheckingInventory);
					} else if (status == "Paused") {
						changeState(Paused);
					} else if (status == "Error") {
						changeState(Error);
					}
				}
				break;
			}
			case Cutscene:{

				break;
			}
			case Quitting:{
				cout << endl << "[Game] Quitting" << endl;
				WINDOW.close();
				break;
			}
			case Error:{
				cout << endl << "[Game] An error occurred... sorry!     ( *_*)? " << endl;
				WINDOW.close();
				break;
			}
		}
	}

	return;
}

void Game::changeState(GameState s){
	GameState temp = s;
	PREVSTATE = STATE;
	STATE = temp;
	return;
}

bool Game::getLastFrame(vector<sf::Sprite>* spritePtr, vector<sf::Texture>* texturePtr){
	/*
		texturePtr:
			[0] -> references the player's texture
			[...] -> TBD
	*/

	Player* mc = WORLD.getMainCharPtr();
	Position mcPos = mc->getPosition();

	// Load previous frame from WORLD; pass it to spritePtr
	sf::Sprite snapshot;
	/*snapshot.setTexture((WORLD.getFrame())->getTexture());
	snapshot.setTexture((*WORLD.getMap()));*/
	snapshot.setTexture((WORLD.getMapRender())->getTexture());	// loads map texture
	spritePtr->push_back(snapshot);

	// Draw previous frame's player; pass it to spritePtr
	sf::Sprite playerSnapshot;
	sf::Texture playerSnapshotTexture;
	if (!playerSnapshotTexture.loadFromFile("img/characters/" + mc->getImage())) {
		printf("[Game] Error: unable to load player texture \"%s\"\n", mc->getImage().c_str());
		return false;
	}
	texturePtr->push_back(playerSnapshotTexture);
	playerSnapshot.setTexture((*texturePtr)[0]);
	playerSnapshot.setPosition(mcPos.x, mcPos.y);
	WORLD.animateChar(&playerSnapshot, WORLD.getMainCharPtr());
	spritePtr->push_back(playerSnapshot);

	// TODO: Pass other elements back to be drawn to the window (i.e. npcs, objects, etc.)


	return true;
}
bool Game::execute (Interaction* ptr) {	// performs the action indicated by "ptr"; whether or not a player is able to do the action is up to World::interact()
	int action = static_cast<int>(ptr->action);
	int target = static_cast<int>(ptr->target);
	int cid = ptr->cid;
	int eid = ptr->eid;

	/*BEGIN: debug*/
	string actionStr, targetStr;
	switch (action) {
		case AT_UNDEFINED:
			actionStr = "undefined";
			break;
		case AT_ENTER:
			actionStr = "enter";
			break;
		case AT_EXAMINE:
			actionStr = "examine";
			break;
		case AT_PICKUP:
			actionStr = "pickup";
			break;
		default:
			actionStr = "";
	}
	switch (target) {
		case MO_UNKNOWN:
			targetStr = "unknown";
			break;
		case MO_DOORWAY:
			targetStr = "doorway";
			break;
		case MO_TRAVELPOINT:
			targetStr = "travelpoint";
			break;
		case MO_CONTAINER:
			targetStr = "container";
			break;
		case MO_ATTAINABLE:
			targetStr = "attainable";
			break;
		default:
			targetStr = "";
	}
	printf("[Game] \tContext[%d]: Executing \"%s\" to \"%s[%d]\" (%s)\n", cid, actionStr.c_str(), targetStr.c_str(), eid, ptr->actionDesc.c_str());
	/*END: debug*/

	switch (action) {
		case AT_UNDEFINED:
			// Do nothing...
			changeState(PREVSTATE);	// restore state
			break;
		case AT_ENTER: {
			switch (target) {
				case MO_UNKNOWN:
					// Do nothing...
					changeState(PREVSTATE);	// restore state
					break;
				case MO_DOORWAY: {
					// Acquire destination information about the doorway specified by the Interaction
					Doorway temp = WORLD.getDoorwayPtr()->at(eid);
					string destMap = temp.destMap;
					string destSpawnName = temp.destSpawnName;
					printf("[Game] \tInitiating transfer to \"%s\" in \"%s\"\n", destSpawnName.c_str(), destMap.c_str());	// debug

					// Initiate Inter-Map Travel
					WORLD.setDest(destMap);
					WORLD.setDestSpawn(destSpawnName);
					changeState(ChangingMap);	// change map
					break;
				}
				case MO_TRAVELPOINT:
					/* TODO */
					break;
				default:
					printf("[Game] Invalid MapObject \"%d\" associated with ActionType \"%d\"", target, action);	// debug
					changeState(PREVSTATE);	// restore state
					return false;
			}
			break;
		}
		default:
			printf("[Game] Unrecognized ActionType \"%d\"", action);	// debug
			changeState(PREVSTATE);	// restore state
			return false;
	}

	return true;
}

/*Initialize static vars*/
GameState Game::STATE = Uninitialized;
GameState Game::PREVSTATE = Game::STATE;
sf::RenderWindow Game::WINDOW;
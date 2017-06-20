#include "Game.h"
#include "Menu2.h"
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
	// Acquire supported display modes for later user customization
	printf("Acquiring supported Display Modes...");
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

	// Initialize local variables
	Difficulty gameDifficulty;
	// sf::SoundBuffer buffer;
	// sf::Sound soundEffect;
	// sf::Music music;
	bool playingMusic = false;
	bool menuUnscaled = true;

	// Load all recurring files here; loading/reloading them during each state could be taxing on the cpu/gpu
	sf::Texture splashTexture;
	sf::Font splashFont;
	sf::Texture pauseTexture;
	sf::Font pauseFont;
	sf::Texture newgameTexture;
	sf::Font newgameFont;
	if (!newgameTexture.loadFromFile("img/splashscreen.png")){	// Load new game window background
		cout << endl << "Error: newgameTexture load unsuccessful" << endl;
		changeState(Error);
		WINDOW.close();
	};
	if (!newgameFont.loadFromFile("fonts/Garuda.ttf")){	// Load splash screen font
		cout << endl << "Error: newgameFont load unsuccessful" << endl;
		changeState(Error);
		WINDOW.close();
	};
	if (!pauseTexture.loadFromFile("img/ironman_III.png")){	// Load pause screen background
		changeState(Error);
		cout << endl << "Error: pauseTexture load unsuccessful" << endl;
		WINDOW.close();
	}
	if (!pauseFont.loadFromFile("fonts/FreeSerif.ttf")){	// Load pause screen font
		changeState(Error);
		cout << endl << "Error: pauseFont load unsuccessful" << endl;
		WINDOW.close();
	};
	if (!splashTexture.loadFromFile("img/splashscreen.png")){	// Load splash screen background
		cout << endl << "Error: splashTexture load unsuccessful" << endl;
		changeState(Error);
		WINDOW.close();
	};
	if (!splashFont.loadFromFile("fonts/Garuda.ttf")){	// Load splash screen font
		cout << endl << "Error: splashFont load unsuccessful" << endl;
		changeState(Error);
		WINDOW.close();
	};

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
					if (!music.openFromFile("audio/Greensleeves-1-greensleeves-2096-6987.ogg")){
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

				// Draw to window after clearing
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
				// sf::Sprite pauseSprite(pauseTexture);
				// sf::Text pauseText("Paused", pauseFont, 50);

				// Draw to window after resetting and clearing
				WINDOW.clear();
				WINDOW.setView(WINDOW.getDefaultView());
				// WINDOW.draw(pauseSprite);
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

					// Stop background music
					if (playingMusic){
						playingMusic = false;
						music.stop();
					}
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
				// Draw to window after resetting and clearing
				WINDOW.clear();
				WINDOW.setView(WINDOW.getDefaultView());

				// Initialize inventory menu
				InventoryMenu imenu("Inventory", &WINDOW, WORLD.getMainCharPtr());
				imenu.setWindowDimensions(windowX, windowY);	// to properly scale mouse coords
				imenu.setScale(menuScaler.xScale(), menuScaler.yScale());	// to properly scale 
				imenu.setBackgroundScale(menuBkgdScaler.xScale(), menuBkgdScaler.yScale());	// to properly scale menu backings
				list<string> btn;
				btn.push_front("Return");
				imenu.assign(btn);
				imenu.setTitlePosition(windowX/22, windowY/2);	// to properly position the menu title

				// Draw inventory menu
				string status = imenu.Show();

				// Handle menu response
				if (status == "Return") {
					changeState(PREVSTATE);
				} else if (status == "Error") {
					changeState(Error);
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
				// Initialize objects
				sf::Sprite newgameSprite(newgameTexture);
				sf::Text newgameTitle("The Arc Stones",newgameFont,70);
				newgameSprite.setScale(splashScaler.xScale(), splashScaler.yScale());
				newgameTitle.setColor(sf::Color::White);
				newgameTitle.setStyle(sf::Text::Italic);
				newgameTitle.setPosition(30,30);

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
					} else {
						// Stop background music
						if (playingMusic){
							playingMusic = false;
							music.stop();
						}

						if (status == "Easy") {
							gameDifficulty = Easy;
						} else if (status == "Normal") {
							gameDifficulty = Normal;
						} else if (status == "Hard"){
							gameDifficulty = Hard;
						} else {
							gameDifficulty = Easy;
						}

						// Prepare the starting world
						WORLD.setWorldName("Kingdom of York");
						if (!WORLD.loadMap("TestRoom.png")) {
							cout << endl << "[Game] World load failed" << endl;
							changeState(Error);
							break;
						}
						if (!WORLD.loadData("TestRoom.txt")) {
							cout << endl << "[Game] World load failed" << endl;
							changeState(Error);
							break;
						}
						WORLD.setLocation();	// set the player's location to the default spawn point

						changeState(Freeroaming);
					}
				}

				break;
			}
			case Shopping:{
				break;
			}
			case Fighting:{
				break;
			}
			case Freeroaming:{
				string status = WORLD.Show();
				
				if (status != "") {
					if (status == "Quitting") {
						changeState(Quitting);
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
}

/*Initialize static vars*/
GameState Game::STATE = Uninitialized;
GameState Game::PREVSTATE = Game::STATE;
sf::RenderWindow Game::WINDOW;
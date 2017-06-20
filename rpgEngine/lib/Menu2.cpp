#include "Menu2.h"
// #include <typeinfo>
using namespace std;


/*Misc Functions*/
string stringify(int i){
	char buffer [200];
	sprintf(buffer, "%d", i);

	return buffer;
}



/*Class MenuButton*/
MenuButton::MenuButton(string name, string action, int left, int top, int width, int height){
	Name = name;
	Action = action;
	Left = left;
	Top = top;
	Width = width;
	Height = height;
	Hovering = false;
}
void MenuButton::setHovering(bool b){
	Hovering = b;
}
bool MenuButton::isClicked(int x, int y){
	// printf("Mouse-x:%d y:%d\n", x, y);	// debug
	if(Left < x && (Left + Width) > x && Top < y && (Top + Height) > y){
		return true;
	} else {
		return false;
	}
}
string MenuButton::getName(){
	return Name;
}
string MenuButton::getAction(){
	return Action;
}
int MenuButton::getTop(){
	return Top;
}
int MenuButton::getLeft(){
	return Left;
}
int MenuButton::getHeight(){
	return Height;
}
int MenuButton::getWidth(){
	return Width;
}
bool MenuButton::getHovering(){
	return Hovering;
}




/*Class Menu*/
Menu::Menu(string title, sf::RenderWindow* w){
	Title = title;
	WINDOW = w;

	// Default settings
	titlePos.x = 40;
	titlePos.y = 350;
	backgroundImg = "img/menu_default.png";
	textFont = "fonts/CaviarDreams_Italic.ttf";
	buttonImg = "img/menubutton_default.png";
	windowWidth = 0;
	windowHeight = 0;
}
Menu::Menu(string title, list<string>& names,sf::RenderWindow* w){
	Title = title;
	WINDOW = w;

	// Default settings
	titlePos.x = 40;
	titlePos.y = 350;
	backgroundImg = "img/menu_default.png";
	textFont = "fonts/CaviarDreams_Italic.ttf";
	buttonImg = "img/menubutton_default.png";
	windowWidth = 0;
	windowHeight = 0;

	assign(names);
}
void Menu::setWindowDimensions(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	return;
}
void Menu::setMenuBackground(string path) {
	backgroundImg = path;
	return;
}
void Menu::setMenuButtonBackground(string path) {
	buttonImg = path;
	return;
}
void Menu::setMenuFont(string path) {
	textFont = path;
	return;
}
void Menu::setTitlePosition(int x, int y) {
	titlePos.x = x;
	titlePos.y = y;
	return;
}
void Menu::assign(list<string>& names) {
	/*
		Menu::assign() - assigns the buttons their clickable positions

		Ideally, I'd want only a max of 8 butons, 4 on one side, 4 on the other. Here are the coordinates for the ideally
		positioned buttons (in their corresponding positions; coords are in left/top/width/heigth order):

		MenuTitle
		___________________________________________
		|	48,502,422,44		550,502,422,44    |
		|	48,560,422,44		550,560,422,44    |
		|	48,618,422,44		550,618,422,44    |
		|	48,676,422,44		550,676,422,44    |	
		__________________________________________
	*/

	//Clear buttons if it isn't already empty (useful since it allows you to reuse an existing menu obj)
	if (!Buttons.empty()) {
		Buttons.clear();
	}

	// Acquire window dimensions (if not set)
	if (windowWidth == 0 && windowHeight == 0) {
		sf::Vector2u windowSize;
		windowSize = WINDOW->getSize();
		windowWidth = windowSize.x;
		windowHeight = windowSize.y;
	}
	// cout << endl << "[Game] Window width " << windowWidth << "   Window height " << windowHeight;	// debug
	
	// Calculate button scales
	sf::Texture buttonBackgroundTexture;
	if (!buttonBackgroundTexture.loadFromFile(buttonImg)) {	//load texture file
		cout << endl << "Error: buttonBackgroundTexture load failed" << endl;
		return;
	}
	sf::Sprite buttonBackgroundSprite(buttonBackgroundTexture);
	sf::FloatRect tempRect = buttonBackgroundSprite.getGlobalBounds();
	localMenuScaler.scale(&buttonBackgroundSprite, windowWidth, windowHeight);	// get button scale factors relative to window

	/*
		Clickable Region Scaling is done using
			
			N = D * F_s * R

			where

			N = New Dimension (i.e. width or height), in (int) pixels
			D = Original Dimension (i.e. width or height), in (float) pixels
			F_s = Scaling Factor (from FloatScaler), in (float) pixels
			R = Ratio of the dimension relative to the window, in a (float)

			(D * F_s) scales the dimension to that of the window, and R scales it down to the desired percentage of the window
	*/
	int l, t;	// absolute coordinates, in reference to the 2D window
	int w = static_cast<int>((tempRect.width * localMenuScaler.xScale()) * (5.0/12.0));
	int h = static_cast<int>((tempRect.height * localMenuScaler.yScale()) * (1.0/16.0));
	// printf("\nw%d h%d tRw%f tRh%f mSx%f mSy%f windowx:%d windowy:%d ", w, h, tempRect.width, tempRect.height, localMenuScaler.xScale(), localMenuScaler.yScale(), windowWidth, windowHeight);	// debug
	int num = 0;

	// Calculate menu background scale
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile(backgroundImg)) {
		cout << endl << "Error: backgroundTexture load failed" << endl;
		return;
	}
	sf::Sprite backgroundSprite(backgroundTexture);
	localBackgroundScaler.scale(&backgroundSprite, windowWidth, windowHeight);

	// Calculate button positions
	/*
		Positioning:
			Left Column Buttons: ?
	*/
	list<string>::iterator it;
	for (it = names.begin(); it != names.end(); it++) {	//turn the names into menu buttons
		if (num < 4) {
			l = windowWidth / 21.33;
		} else {
			l = windowWidth / 1.86;
		}
		if (num == 0 || num == 4) {
			t = windowHeight / 1.53;
		} else {
			t += windowHeight / 13.24;
		}

		if (num <= 7) {
			string temp = (*it);
			MenuButton a(temp, temp, l, t, w, h);
			Buttons.push_front(a);

			// cout << endl << "[Game] Button " << a.getName() << " (l,t,w,h):(" << a.getLeft() << "," << a.getTop() << "," << a.getWidth() << "," << a.getHeight() << ")";

			num++;
		} else {
			break;
		}
	}
}
void Menu::setScale (float x, float y) {
	localMenuScaler.scale(x, y);
	return;
}
float Menu::getScaleX () {
	return localMenuScaler.xScale();
}
float Menu::getScaleY () {
	return localMenuScaler.yScale();
}
void Menu::setBackgroundScale(float x, float y) {
	localBackgroundScaler.scale(x,y);
	return;
}
float Menu::getBackgroundScaleX() {
	return localBackgroundScaler.xScale();
}
float Menu::getBackgroundScaleY() {
	return localBackgroundScaler.yScale();
}
void Menu::checkHovering(int x, int y) {
	string buttonName = isHovering(x,y);
	if (buttonName != "") {
		list<MenuButton>::iterator hoveringButton;
		for (hoveringButton = Buttons.begin(); hoveringButton != Buttons.end(); hoveringButton++) {
			if ((*hoveringButton).getName() == buttonName) {
				(*hoveringButton).setHovering(true);
			}
		}
	}
}
/*
Mouse Coordinate Scaling:
	Since mouse coordinates work off of the absolute window size (and not in the coordinate system relative to what's inside the window), a window resize would cause graphics to scale down, but the mouse coordinate system to remain the same, therefore casusing a mismatch between the two (i.e. a window's menu w/ two adjacent buttons, if resized, would scale the buttons down so they remain in both halves of the window, but the mouse coordinate system would not scale down with them).

	To solve this, I am scaling the mouse coordinate system w/ the window's relative coordinate system using a ratio:

	x_mouse/x_window = x_o/x_orig, therefore x_o = x_orig * (x_mouse/x_window)

	where
	x_mouse = current mouse coord (in its absolute coord form)
	x_window = current window dimension (in its absolute coord form)
	x_o = (the target) the mouse coord within the window's relative coord system
	x_orig = the orig max value of this dimension
	(NOTE: the term "absolute" refers to the size of your computer's screen. the term "relative" refers to the size of the game's window)
*/
float Menu::adjustMouseDimension (float absoluteMouseCoord, float absoluteWindowDim, float originalWindowDim) {
	return (absoluteMouseCoord/absoluteWindowDim) * originalWindowDim;
}
string Menu::Show() {
	if (Buttons.empty()) {
		cout << endl << "Error: No buttons in menu" << endl;
		return "Error";
	}

	// Load menu background
	sf::Texture menuTexture;
	if (!menuTexture.loadFromFile(backgroundImg/*, sf::IntRect(0, 0, windowWidth, windowHeight)*/)) {
		cout << endl << "Error: menuTexture load unsuccessful" << endl;
		return "Error";
	};

	// Load menu font
	sf::Font menuFont;
	if (!menuFont.loadFromFile(textFont)) {
		cout << endl << "Error: menuFont load unsuccessful" << endl;
		return "Error";
	};

	// Initialize primary menu objects
	sf::Sprite menuSprite(menuTexture);
	sf::Text menuTitle(Title,menuFont,50);
	menuSprite.setScale(localBackgroundScaler.xScale(), localBackgroundScaler.yScale());
	menuTitle.setStyle(sf::Text::Bold);
	menuTitle.setColor(sf::Color::White);
	menuTitle.setPosition(titlePos.x,titlePos.y);

	// Draw primary menu objects
	WINDOW->draw(menuSprite);
	WINDOW->draw(menuTitle);

	// Event processing
	/*
		The reason I'm putting the event processing before the frame is to enable a button's text to be editted when hovering over it, increasing the apparence that a button is hovered over
	*/
	sf::Event event;
	while (WINDOW->pollEvent(event)) {
		// Music->stop();
		// Get mouse coords every frame instead of waiting for the mouse moved event
		sf::Vector2i vect = sf::Mouse::getPosition(*WINDOW);
		sf::Vector2u winsize = WINDOW->getSize();
		float mouseX = adjustMouseDimension(static_cast<float>(vect.x),static_cast<float>(winsize.x),static_cast<float>(windowWidth));
		float mouseY = adjustMouseDimension(static_cast<float>(vect.y),static_cast<float>(winsize.y),static_cast<float>(windowHeight));
		// printf("%f %f \n", mouseX, mouseY);	// debug
		checkHovering(mouseX, mouseY);
		
		// handle events
		if (event.type == sf::Event::Closed) {
			return "Quitting";
		}
		if (event.type == sf::Event::MouseMoved) {
			
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {	//selection
				string resultStatus;

				// resultStatus = leftClick(event.mouseButton.x, event.mouseButton.y);
				resultStatus = leftClick(mouseX, mouseY);
				cout << endl << "[Game] leftClick -> resultStatus: " << resultStatus << endl;

				return resultStatus;
			}
			// cout << endl << "[Game] Pausing" << endl;
			// return "Paused";
		}
	}

	// Initialize and draw menu buttons
	sf::Texture optionTexture;
	sf::Sprite optionSprite[8];	//delcare variables here to keep their lifetime up until display
	sf::Text optionText[8];
	bool loadErr = false;
	short k = 0;
	list<MenuButton>::iterator it;
	for (it = Buttons.begin(); it != Buttons.end(); it++){
		// Make no more than 8 buttons
		if (k > 7) break;

		// Load button backing
		// cout << endl << "[Game] " << (*it).getName() << " size: " << (*it).getWidth() << "x" << (*it).getHeight();
		sf::IntRect buttonArea(0, 0, (*it).getWidth(), (*it).getHeight());	//set a rect. with btn area initially at (0,0)
		if (!optionTexture.loadFromFile(buttonImg)) {	//load texture file
			cout << endl << "Error: optionTexture load failed" << endl;
			loadErr = true;
			break;
		}

		// Create and place sprite
		optionSprite[k].setTexture(optionTexture);
		optionSprite[k].setTextureRect(buttonArea);	//set button area
		optionSprite[k].setPosition((*it).getLeft(), (*it).getTop());

		// cout << endl << "[Game] Drawing " << (*it).getName() << " @ (x,y)=(" << (*it).getLeft() << "," << (*it).getTop() << ")";

		// Create and place text
		// sf::Color color(51, 153, 51);	//lime green
		sf::Color color(255,255,255);	//white
		int buttonTextSize = 30;
		optionText[k].setString((*it).getName());
		optionText[k].setFont(menuFont);
		if ( (*it).getHovering() ) {
			buttonTextSize = 35;
		}
		optionText[k].setCharacterSize( buttonTextSize );
		optionText[k].setColor(color);
		optionText[k].setStyle(sf::Text::Italic | sf::Text::Bold);
		optionText[k].setPosition((*it).getLeft() + 50, (*it).getTop() );

		// Draw sprite and text
		WINDOW->draw(optionSprite[k]);
		WINDOW->draw(optionText[k]);

		k++;
	}
	if (loadErr){
		return "Error";
	}

	// Display all to window
	WINDOW->display();

	return "";
}
string Menu::leftClick(int x, int y){
	// Look to see if any of the buttons were clicked
	list<MenuButton>::iterator it;
	cout << endl << "[Game] leftClick -> Buttons: " << Buttons.size();
	for(it = Buttons.begin(); it != Buttons.end(); it++){
		cout << endl << "[Game] Checking " << (*it).getAction() << " | x:" << x << " y:" << y << " | Clicked?:" << (*it).isClicked(x, y) ;
		if((*it).isClicked(x,y)){
			cout << endl << "[Game] Clicked \"" << (*it).getAction() << "\"";
			return (*it).getAction();
		}
	}

	// If no button was clicked, return an empty action
	cout << endl << "[Game] No button clicked";
	return "";
}
string Menu::isHovering(int x, int y){
	// Look to see if the mouse is hovering over any one of the buttons
	list<MenuButton>::iterator it;
	for(it = Buttons.begin(); it != Buttons.end(); it++){
		if((*it).isClicked(x,y)){
			// cout << endl << "[Game] Clicked \"" << (*it).getAction() << "\"";
			return (*it).getName();
		}
	}
	return "";
}



/*Class StatMenu*/
StatMenu::StatMenu (string title, sf::RenderWindow* w, Player* p) : Menu (title, w) {
	WINDOW = w;

	// Default settings
	statImg = "img/menu_default.png";
	statFont = "fonts/CaviarDreams_Italic.ttf";
	
	loadPlayerStats(p);
}
StatMenu::StatMenu (string title, list<string>& names, sf::RenderWindow* w, Player* p) : Menu (title, names, w) {
	WINDOW = w;

	// Default settings
	statImg = "img/menu_default.png";
	statFont = "fonts/CaviarDreams_Italic.ttf";
	
	loadPlayerStats(p);
}

void StatMenu::loadPlayerStats (Player* p) {
	Stats.name = p->getName();
	Stats.level = p->getLevel();
	Stats.xp = p->getExperience();
	Stats.maxhp = p->getMaxHealth();
	Stats.hp = p->getHP();
	Stats.armor = p->getArmor();
	Stats.magic = p->getMagic();
	Stats.atk = p->getAttack();
}

string StatMenu::Show () {
	// Load stats menu background image (defaults to the same image as the basic Menu)
	sf::Texture statTexture;
	if (!statTexture.loadFromFile(statImg)) {
		return "Error";
	}

	// Get the stats menu background image size
	sf::Vector2u statImgVect = statTexture.getSize();

	// Create stat menu background sprite and rotate the image such that it appears on the upper right hand corner
	sf::Sprite statSprite(statTexture);
	statSprite.setOrigin(statImgVect.x, statImgVect.y); // Sets image origin at the bottom right corner of screen such that image is off screen (images are drawn from top-left to bottom-right; that top-left is defined by the origin)
	statSprite.setRotation(180);	// Rotates the image back to screen about botom right corner such that it is now upside down and on screen

	// // Clear stat menu render texture and populate it with statSprite 
	// STATMENU.clear(sf::Color::Black);
	// STATMENU.draw(statSprite);
	WINDOW->draw(statSprite);

	// Load stats menu font
	sf::Font statFontType;
	if (!statFontType.loadFromFile(statFont)) {
		cout << endl << "Error: statFontType load failed" << endl;
		return "Error";
	}

	// Compile the stats into a single string
	string statString;
	statString += Stats.name + " - Lvl " + stringify(Stats.level) + "\n";
	statString += "XP: " + stringify(Stats.xp) + "/" + stringify( (Stats.level + 1) * 1000) + "\n";
	statString += "Health: " + stringify(Stats.hp) + "/" + stringify(Stats.maxhp) + "\n";
	statString += "Armor: " + stringify(Stats.armor) + "\n";
	statString += "Magic: " + stringify(Stats.magic) + "\n";
	statString += "Attack: " + stringify(Stats.atk) + "\n";

	// Create the stats menu text
	sf::Text heroStats;
	heroStats.setFont(statFontType);
	heroStats.setString(statString);
	heroStats.setCharacterSize(30);
	heroStats.setStyle(sf::Text::Bold);
	heroStats.setColor(sf::Color::White);
	heroStats.move(60,30);

	// // Populate stat menu render texture with the hero's stats
	// STATMENU.draw(heroStats);

	// Finalize stat menu render texture and draw it to window
	// STATMENU.display();
	// sf::Sprite finalSprite(STATMENU.getTexture());
	WINDOW->draw(heroStats);
	// WINDOW->draw(heroStats);

	// Run Menu's show status result
	return Menu::Show();
}



/*
	Class InventoryMenu
*/
InventoryMenu::InventoryMenu (string title, sf::RenderWindow* w, Player* p) : Menu (title, w) {
	invTitle = title;
	WINDOW = w;
	INV = NULL;

	// Default settings
	setImg("img/menu_inventory_default.png");
	setFont("fonts/CaviarDreams_Italic.ttf");

	loadInventory(p);
}

void InventoryMenu::setImg (string i) {
	invImg = i;
}
void InventoryMenu::setFont (string f) {
	invFont = f;
}

string InventoryMenu::Show () {
	// Load inventory menu background image (defaults to the same image as the basic Menu)
	sf::Texture invTexture;
	if (!invTexture.loadFromFile(invImg)) {
		cout << ">>>>Critical<<<<" << endl;
		return "Error";
	}

	// Get the stats menu background image size
	sf::Vector2u invImgVect= invTexture.getSize();

	// Create stat menu background sprite and rotate the image such that it appears on the upper right hand corner
	sf::Sprite invSprite(invTexture);
	invSprite.setOrigin(invImgVect.x, invImgVect.y);
	invSprite.setRotation(270);
	WINDOW->draw(invSprite);

	// Run Menu's show status result
	return Menu::Show();
}

void InventoryMenu::loadInventory (Player* p) {
	INV = p->getInventoryPtr();
}
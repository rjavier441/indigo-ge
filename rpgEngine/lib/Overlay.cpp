#include "Overlay.h"
using namespace std;


/*
	struct OverlayMenuData
*/
OverlayMenuData::OverlayMenuData () {
	cursor_position = 0;
	range_top = 0;
}

/*
	class Overlay - the base class for all overlayable objects
*/
Overlay::Overlay () {
	WINDOW = NULL;
	position.x = 0;
	position.y = 0;
	width = 0;
	height = 0;
}
Overlay::Overlay (sf::RenderWindow* rw, Position p, int w, int h) {
	WINDOW = rw;
	position.x = p.x;
	position.y = p.y;
	width = w;
	height = h;
}
Overlay::Overlay (sf::RenderWindow* rw, int x, int y, int w, int h) {
	WINDOW = rw;
	position.x = x;
	position.y = y;
	width = w;
	height = h;
}

void Overlay::setWindowPtr (sf::RenderWindow* p) {
	WINDOW = p;
	return;
}
void Overlay::setName (string n) {
	name = n;
	return;
}
void Overlay::setPosition (Position* p) {
	position.x = p->x;
	position.y = p->y;
	return;
}
void Overlay::setX (int x) {
	position.x = x;
	return;
}
void Overlay::setY (int y) {
	position.y = y;
	return;
}
void Overlay::setWidth (int w) {
	width = w;
	return;
}
void Overlay::setHeight (int h) {
	height = h;
	return;
}

sf::RenderWindow* Overlay::getWindowPtr () {
	return WINDOW;
}
Position* Overlay::getPositionPtr () {
	return &position;
}
string Overlay::getName () {
	return name;
}
int Overlay::getWidth () {
	return width;
}
int Overlay::getHeight () {
	return height;
}





/*
	class OverlayMenu
*/
OverlayMenu::OverlayMenu () : Overlay () {	// default; calls parent's default constructor
	path = OVERLAYMENU_DEFAULT_PATH;
	file = "";
	fontpath = OVERLAYMENU_DEFAULT_FONTPATH;
	fontfile = "";
	cursorpath = OVERLAYMENU_DEFAULT_PATH;
	cursorfile = "";
	fontsize = OVERLAYMENU_DEFAULT_FONTSIZE;
	optionOffsetX = 0;
	optionOffsetY = 0;
	cursorPosition = NULL;
	cursorWidth = 0;
	cursorHeight = 0;
	viewTop = NULL;
	viewRange = OVERLAYMENU_DEFAULT_CAPACITY;
	dynamicSetting = true;
	titleSetting = false;
	titlePosition.x = getPositionPtr()->x;
	titlePosition.y = getPositionPtr()->y - TILEHEIGHT - OVERLAYMENU_DEFAULT_MARGIN;	// recall that +y points down screen
	options.push_back("Cancel");
}
OverlayMenu::OverlayMenu (sf::RenderWindow* rw, Position p, int w, int h) : Overlay (rw, p, w, h) {
	path = OVERLAYMENU_DEFAULT_PATH;
	file = "";
	fontpath = OVERLAYMENU_DEFAULT_FONTPATH;
	fontfile = "";
	cursorpath = OVERLAYMENU_DEFAULT_PATH;
	cursorfile = "";
	fontsize = OVERLAYMENU_DEFAULT_FONTSIZE;
	optionOffsetX = 0;
	optionOffsetY = 0;
	cursorPosition = NULL;
	cursorWidth = 0;
	cursorHeight = 0;
	viewTop = NULL;
	viewRange = OVERLAYMENU_DEFAULT_CAPACITY;
	dynamicSetting = true;
	titleSetting = false;
	titlePosition.x = getPositionPtr()->x;
	titlePosition.y = getPositionPtr()->y - TILEHEIGHT - OVERLAYMENU_DEFAULT_MARGIN;
	options.push_back("Cancel");
}
OverlayMenu::OverlayMenu (sf::RenderWindow* rw, int x, int y, int w, int h) : Overlay (rw, x, y, w, h) {
	path = OVERLAYMENU_DEFAULT_PATH;
	file = "";
	fontpath = OVERLAYMENU_DEFAULT_FONTPATH;
	fontfile = "";
	cursorpath = OVERLAYMENU_DEFAULT_PATH;
	cursorfile = "";
	fontsize = OVERLAYMENU_DEFAULT_FONTSIZE;
	optionOffsetX = 0;
	optionOffsetY = 0;
	cursorPosition = NULL;
	cursorWidth = 0;
	cursorHeight = 0;
	viewTop = NULL;
	viewRange = OVERLAYMENU_DEFAULT_CAPACITY;
	dynamicSetting = true;
	titleSetting = false;
	titlePosition.x = getPositionPtr()->x;
	titlePosition.y = getPositionPtr()->y - TILEHEIGHT - OVERLAYMENU_DEFAULT_MARGIN;
	options.push_back("Cancel");
}
OverlayMenu::OverlayMenu (sf::RenderWindow* rw, Position p, int vr) : Overlay () {
	setWindowPtr(rw);
	setPosition(&p);

	path = OVERLAYMENU_DEFAULT_PATH;
	file = "";
	fontpath = OVERLAYMENU_DEFAULT_FONTPATH;
	fontfile = "";
	cursorpath = OVERLAYMENU_DEFAULT_PATH;
	cursorfile = "";
	fontsize = OVERLAYMENU_DEFAULT_FONTSIZE;
	optionOffsetX = 0;
	optionOffsetY = 0;
	cursorPosition = NULL;
	cursorWidth = 0;
	cursorHeight = 0;
	viewTop = NULL;
	viewRange = vr;
	dynamicSetting = true;
	titleSetting = false;
	titlePosition.x = getPositionPtr()->x;
	titlePosition.y = getPositionPtr()->y - TILEHEIGHT - OVERLAYMENU_DEFAULT_MARGIN;
	options.push_back("Cancel");

	// custom overlay dimensions
	setWidth(OVERLAYMENU_DEFAULT_WIDTH + 2 * OVERLAYMENU_DEFAULT_MARGIN);
	setHeight(viewRange * (fontsize + 2 * OVERLAYMENU_DEFAULT_MARGIN));
}
OverlayMenu::OverlayMenu (sf::RenderWindow* rw, int x, int y, int vr) : Overlay () {
	setWindowPtr(rw);
	setX(x);
	setY(y);

	path = OVERLAYMENU_DEFAULT_PATH;
	file = "";
	fontpath = OVERLAYMENU_DEFAULT_FONTPATH;
	fontfile = "";
	cursorpath = OVERLAYMENU_DEFAULT_PATH;
	cursorfile = "";
	fontsize = OVERLAYMENU_DEFAULT_FONTSIZE;
	optionOffsetX = 0;
	optionOffsetY = 0;
	cursorPosition = NULL;
	cursorWidth = 0;
	cursorHeight = 0;
	viewTop = NULL;
	viewRange = vr;
	dynamicSetting = true;
	titleSetting = false;
	titlePosition.x = getPositionPtr()->x;
	titlePosition.y = getPositionPtr()->y - TILEHEIGHT - OVERLAYMENU_DEFAULT_MARGIN;
	options.push_back("Cancel");

	// custom overlay dimensions
	setWidth(OVERLAYMENU_DEFAULT_WIDTH + 2 * OVERLAYMENU_DEFAULT_MARGIN);
	setHeight(viewRange * (fontsize + 2 * OVERLAYMENU_DEFAULT_MARGIN));
}

void OverlayMenu::showTitle () {
	titleSetting = true;
	return;
}
void OverlayMenu::hideTitle () {
	titleSetting = false;
	return;
}
void OverlayMenu::setStatic () {
	dynamicSetting = false;
	return;
}
void OverlayMenu::setDynamic () {
	dynamicSetting = true;
	return;
}
void OverlayMenu::setImgPath (string p) {
	path = p;
	return;
}
void OverlayMenu::setBackground (string b) {
	file = b;
	return;
}
void OverlayMenu::setAbsoluteTitlePos (int x, int y) {
	titlePosition.x = x;
	titlePosition.y = y;
	return;
}
void OverlayMenu::setTitlePos (int x, int y) {
	titlePosition.x = getPositionPtr()->x + x;
	titlePosition.y = getPositionPtr()->y + y;
	return;
}
void OverlayMenu::setFont (string f) {
	fontfile = f;
	return;
}
void OverlayMenu::setFontPath (string p) {
	fontpath = p;
	return;
}
void OverlayMenu::setFontSize (int s) {
	fontsize = s;
	setHeight(viewRange * (fontsize + 2 * OVERLAYMENU_DEFAULT_MARGIN));	// re-adjust height
	return;
}
void OverlayMenu::setOptionOffset (int x, int y) {
	optionOffsetX = x;
	optionOffsetY = y;
	return;
}
void OverlayMenu::setCursorPath (string s) {
	cursorpath = s;
	return;
}
void OverlayMenu::setCursorImg (string s) {
	cursorfile = s;
	return;
}
void OverlayMenu::setCursorPos (int* s, bool reset) {
	cursorPosition = s;
	if (reset) *cursorPosition = 0;
	return;
}
void OverlayMenu::setViewRange (int vr) {
	viewRange = vr;
	setHeight(viewRange * (fontsize + 2 * OVERLAYMENU_DEFAULT_MARGIN));	// re-adjust height
	return;
}
void OverlayMenu::setViewTop (int* t) {
	viewTop = t;
	return;
}
void OverlayMenu::addOption (string s) {
	options.push_back(s);
	return;
}
void OverlayMenu::clearOptions () {
	options.clear();
	return;
}

string OverlayMenu::Show () {
	sf::RenderWindow* rw = getWindowPtr();

	// Check for prerequesites
	if (rw == NULL) {
		printf("[OverlayMenu] Error: Unspecified window pointer\n");
		return "Error";
	}
	if (file == "") {
		printf("[OverlayMenu] Error: Unspecified background image\n");
		return "Error";
	}
	if (fontfile == "") {
		printf("[OverlayMenu] Error: Unspecified font file\n");
		return "Error";
	}
	if (cursorfile == "") {
		printf("[OverlayMenu] Error: Unspecified cursor image\n");
		return "Error";
	}
	if (cursorPosition == NULL) {
		printf("[OverlayMenu] Error: Unreferenced cursor position\n");
		return "Error";
	}
	if (viewTop == NULL) {
		printf("[OverlayMenu] Error: Unreferenced view top\n");
		return "Error";
	}
	if (viewRange < 1) {
		printf("[OverlayMenu] Error: Invalid view range\n");
		return "Error";
	}
	if (options.size() < 1) {
		printf("[OverlayMenu] Error: No content\n");
		return "Error";
	}

	// Load background img
	sf::Texture omTexture;
	if (!omTexture.loadFromFile(path + file)) {
		printf("[OverlayMenu] Error: Background \"%s%s\" could not be loaded\n", path.c_str(), file.c_str());
		return "Error";
	}

	// Load cursor img
	sf::Texture omCursorTexture;
	if (!omCursorTexture.loadFromFile(cursorpath + cursorfile)) {
		printf("[OverlayMeny] Error: Cursor \"%s%s\" could not be loaded\n", cursorpath.c_str(), cursorfile.c_str());
		return "Error";
	}

	// Load font
	sf::Font omFont;
	if (!omFont.loadFromFile((fontpath + fontfile))) {
		printf("[OverlayMenu] Error: Font \"%s%s\" could not be loaded\n", fontpath.c_str(), fontfile.c_str());
		return "Error";
	}
	
	// Initialize primary menu objects
	Position* omPosition = getPositionPtr();
	sf::Sprite omBackground(omTexture);
	sf::Text omTitle;
	sf::Sprite omCursor;
	vector<sf::Text> omOptionText;

	// Adjust menu size dynamically (only if desired, and if there are fewer options than the view range total)
	if (dynamicSetting && options.size() < viewRange) {
		setHeight(options.size() * (fontsize + 2 * OVERLAYMENU_DEFAULT_MARGIN));	// By default, set height to the the size of the font times the amount of options, plus margins for top and bottom of each menu option
	}

	// Determine background placement and scaling
	FloatScaler omBkgdScaler;
	omBkgdScaler.scale(&omBackground, static_cast<float>(getWidth()), static_cast<float>(getHeight()));
	omBackground.setPosition(omPosition->x, omPosition->y + OVERLAYMENU_DEFAULT_MARGIN);
	omBackground.setScale(omBkgdScaler.xScale(), omBkgdScaler.yScale());

	// Format overlay menu title (if true)
	if (titleSetting) {
		FloatScaler omTitleScaler;
		omTitle.setFont(omFont);
		omTitle.setPosition(titlePosition.x, titlePosition.y);
		omTitle.setString(getName());
		omTitle.setCharacterSize(fontsize + OVERLAYMENU_DEFAULT_TEXT_PRESCALE);
		omTitleScaler.scale(&omTitle, static_cast<float>(getWidth()), fontsize - OVERLAYMENU_DEFAULT_MARGIN);
		// printf("%f\n", omTitleScaler.xScale());	// debug
		omTitle.setScale(omTitleScaler.xScale(), omTitleScaler.yScale());	// scale text to match menu's width 
	}

	// Draw elements to window
	/*
		Draw order (from lowest layer to top):
		omBackground
		omTitle
		omCursor
		omOptionText
	*/
	// rw->clear();	// handled by Game.h
	rw->draw(omBackground);
	if (titleSetting) rw->draw(omTitle);

	// Event Processing (do before drawing omOptionText so I can add necessary animations)
	sf::Event event;
	while (rw->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			return "Quitting";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			// immediately return to previous state (i.e. exit menu)
			return "Return";
		}
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Down && *cursorPosition < options.size() - 1) {
				*cursorPosition = *cursorPosition + 1;	// move cursor down the list
				if (*cursorPosition > *viewTop + viewRange - 1) {
					*viewTop = *viewTop + 1;	// move the subset of viewable options down the list
				}
			} else if (event.key.code == sf::Keyboard::Up && *cursorPosition > 0) {
				*cursorPosition = *cursorPosition - 1;	// move cursor up the list
				if (*cursorPosition < *viewTop) {
					*viewTop = *viewTop - 1;	// move the subset of viewable options up the list
				}
			}
			// printf("[OverlayMenu] Option %d: %s\n", *cursorPosition, options[*cursorPosition].c_str());	// debug
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {	// hitting "enter"
			// return the name of the currently selected option ONLY upon key release
			return options[*cursorPosition].c_str();
		}
	}

	// Scale, place, and draw omCursor
	FloatScaler omCursorScaler;
	Position omCursorPosition;	// holds pixel position of the cursor
	omCursor.setTexture(omCursorTexture);
	if (cursorWidth != 0 && cursorHeight != 0) {	// if custom cursor settings are available
		omCursorScaler.scale(&omCursor, cursorWidth, cursorHeight);
	} else {
		int tempint = viewRange;
		if (options.size() < viewRange) tempint = options.size();
		omCursorScaler.scale(&omCursor, getWidth(), getHeight() / tempint);	// default cursor settings
	}
	omCursor.setScale(omCursorScaler.xScale(), omCursorScaler.yScale());
	placeCursor(&omCursorPosition);
	omCursor.setPosition(omCursorPosition.x, omCursorPosition.y);	// TODO
	rw->draw(omCursor);
	
	// Scale, place, and draw option texts (only those in the view range)
	for (int i = 0; i < viewRange; i++) {
		FloatScaler omOptionTextScaler;
		int tempint = viewRange;
		if (options.size() < viewRange) tempint = options.size();
		int divHeight = getHeight() / tempint;
		int index = *viewTop + i;
		
		// prevent accessing a non-existent index of "options" (i.e. if fewer options than viewRange count)
		if (index == options.size()) {
			break;
		}

		sf::Text tempText;
		tempText.setString(options[index]);
		tempText.setFont(omFont);
		tempText.setCharacterSize(fontsize + OVERLAYMENU_DEFAULT_TEXT_PRESCALE);
		/*if (cursorPosition == 0) tempText.setPosition(getPositionPtr()->x + OVERLAYMENU_DEFAULT_MARGIN, getPositionPtr()->y); // if first element, don't too much margin up top
		else*/ tempText.setPosition(getPositionPtr()->x + OVERLAYMENU_DEFAULT_MARGIN + optionOffsetX, getPositionPtr()->y + i * divHeight + optionOffsetY + OVERLAYMENU_DEFAULT_MARGIN/2);
		omOptionTextScaler.scale(&tempText, static_cast<float>(getWidth()) - static_cast<float>(3 * OVERLAYMENU_DEFAULT_MARGIN), static_cast<float>(divHeight) - static_cast<float>(3 * OVERLAYMENU_DEFAULT_MARGIN));
		// omOptionTextScaler.scale(&tempText, static_cast<float>(getWidth()) - static_cast<float>(2 * OVERLAYMENU_DEFAULT_MARGIN), static_cast<float>(getHeight()));
		// tempText.setScale(omOptionTextScaler.xScale(), 1);	// scale with the width of the menu, and minus twice the margin
		tempText.setScale(omOptionTextScaler.xScale(), omOptionTextScaler.yScale());	// scale with the width of the menu, and minus twice the margin
		rw->draw(tempText);
	}

	// Display all to window
	rw->display();

	return "";
}
int OverlayMenu::getCursorPosition () {
	if (cursorPosition != NULL) return *cursorPosition;
	else return -1;
}

void OverlayMenu::placeCursor (Position* p) {
	int offset = OVERLAYMENU_DEFAULT_MARGIN;
	int top = *viewTop;
	int maxsize = viewRange;
	if (options.size() < viewRange) maxsize = options.size();
	int pos = *cursorPosition;
	int divHeight = getHeight() / maxsize;

	p->x = getPositionPtr()->x;	// align cursor's left edge with overlay menu's left edge
	p->y = getPositionPtr()->y + offset + divHeight * (pos - top);	// place cursor on the selected option
	return;
}





/*
	class Hud
*/
Hud::Hud () : Overlay () {

}
Hud::Hud (sf::RenderWindow* rw, Position p, int w, int h) : Overlay (rw, p, w, h) {

}
Hud::Hud (sf::RenderWindow* rw, int x, int y, int w, int h) : Overlay (rw, x, y, w, h) {

}

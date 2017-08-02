#pragma once	// a surprisingly widely-supported/cross-compatible construct functioning like standard include guards; may POSSIBLY acheive faster compile times
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdio>	// printf()
#include <string>	// string
#include "Utilities.h"	// Position
#include "Scaling.h"	// FloatScaler
using namespace std;

#define OVERLAYMENU_DEFAULT_PATH "./img/"
#define OVERLAYMENU_DEFAULT_FONTPATH "./fonts/"
#define OVERLAYMENU_DEFAULT_FONTSIZE 30	// in pixels
// #define OVERLAYMENU_DEFAULT_MARGIN 2
#define OVERLAYMENU_DEFAULT_TEXT_PRESCALE 100
#define OVERLAYMENU_DEFAULT_MARGIN 4
#define OVERLAYMENU_DEFAULT_CAPACITY 4
#define OVERLAYMENU_DEFAULT_WIDTH 64	// in pixels
#define OVERLAYMENU_DEFAULT_HEIGHT 128	// in pixels
#define TILEHEIGHT 32

/*
	struct OverlayMenuData - a collection of external data for use in conjunction with class OverlayMenu
*/
struct OverlayMenuData {
	OverlayMenuData();	// default

	int cursor_position;	// can record the current position of the overlay menu marker
	int range_top;			// can record the index of the option that is currently at the top of the view range
};
typedef struct OverlayMenuData OverlayMenuData;

/*
	class Overlay - The base class for all overlayable entities
*/
class Overlay {
public:
	Overlay();	// default
	Overlay(sf::RenderWindow* rw, Position p, int w, int h);
	Overlay(sf::RenderWindow* rw, int x, int y, int w, int h);

	void setWindowPtr(sf::RenderWindow*);
	void setName(string);
	void setPosition(Position*);
	void setX(int);
	void setY(int);
	void setWidth(int);
	void setHeight(int);

	sf::RenderWindow* getWindowPtr();
	Position* getPositionPtr();
	string getName();
	int getWidth();
	int getHeight();
private:
	sf::RenderWindow* WINDOW;	// pointer to the game's window
	Position position;			// the overlay's current position
	int width;					// the overlay's width in pixels
	int height;					// the overlay's height in pixels
	string name;				// the name of the overlay
};

/*
	class OverlayMenu - an overlayed (and scrollable) menu that uses the arrow and return keys for option selection

		By default, the menu's position, scaling, and transformations are set with respect to the menus's origin, which is the upper-left corner of the menu texture's sprite
*/
class OverlayMenu : public Overlay {
public:
	OverlayMenu();	// default
	OverlayMenu(sf::RenderWindow* rw, Position p, int w, int h);
	OverlayMenu(sf::RenderWindow* rw, int x, int y, int w, int h);
	OverlayMenu(sf::RenderWindow* rw, Position p, int vr = OVERLAYMENU_DEFAULT_CAPACITY);	// sets height based off of view range
	OverlayMenu(sf::RenderWindow* rw, int x, int y, int vr = OVERLAYMENU_DEFAULT_CAPACITY);	// sets height based off of view range

	void showTitle();			// sets titleSetting to true
	void hideTitle();			// sets titleSetting to false
	void setStatic();			// sets dynamicSetting to false
	void setDynamic();			// sets dynamicSetting to true
	void setImgPath(string);	// sets menu background image path "path"
	void setBackground(string);	// sets menu background image filename "file"
	void setAbsoluteTitlePos(int x, int y);	// positions the title (if shown) relative to the screen
	void setTitlePos(int x, int y);	// positions the title (if shown) relative to the option menu's position
	void setFont(string);		// sets font filename
	void setFontPath(string);	// sets font file path
	void setFontSize(int);		// sets fontsize (in px)
	void setOptionOffset(int x, int y);	// set the x and y axis offsets for option text (in px)
	void setCursorPath(string);	// sets cursor image path "cursorpath"
	void setCursorImg(string);	// sets cursor image filename "cursorfile"
	void setCursorPos(int* ptr, bool reset = false);	// acquires reference to menu cursor's current position; if "reset" is true, immediately resets the value pointed by "ptr" to 0
	void setViewRange(int);		// sets "viewRange"
	void setViewTop(int* ptr);	// sets "viewTop"
	void addOption(string);		// adds an option to the menu
	void clearOptions();		// clears "options"
	
	string Show();				// displays OverlayMenu on screen & returns a status string reflecting the corresponding sf::Event
	int getCursorPosition();	// returns the value of cursorPosition if set; otherwise, returns -1

private:
	void placeCursor(Position*);// sets the pixel position of the cursor based on its place within the view range

	string path;			// the path to the OverlayMenu's menu background; if not set, defaults to OVERLAYMENU_DEFAULT_PATH
	string file;			// the filename of the OverlayMenu's menu background
	string fontpath;		// the path to the OverlayMenu's menu font; if not set, defaults to OVERLAYMENU_DEFAULT_FONTPATH
	string fontfile;		// the filename of the OverlayMenu's menu font
	string cursorpath;		// the path to the OverlayMenu's cursor image(s); if not set, defaults to OVERLAYMENU_DEFAULT_PATH
	string cursorfile;		// the filename of the OverlayMenu's cursor image
	int fontsize;			// the size of the font (in px); defaults to OVERLAYMENU_DEFAULT_FONTSIZE
	int optionOffsetX;		// used to fine-tune the position of option text in the x-axis; defaults to 0
	int optionOffsetY;		// used to fine-tune the position of option text in the y-axis; defaults to 0
	int* cursorPosition;	// the index of the currently selected option; must be tracked externally
	int cursorWidth;		// width of the cursor sprite; by default, this is set to 0, and the cursor's width equals the width of the OverlayMenu
	int cursorHeight;		// height of the cursor sprite; by default, this is set to 0, and the cursor's height equals the OverlayMenu's height divided by the viewRange
	int* viewTop;			// the index of the top-most option currently shown in the view; must be tracked externally
	int viewRange;			// the number of options that will be shown in the overlay menu box at any given time; if the number of elements in "options" is above this number, the overlay menu will act like a scollable menu, popping and pushing options as necessary; if not set, defaults to OVERLAYMENU_DEFAULT_CAPACITY
	bool dynamicSetting;	// defaults to true; if false, OverlayMenu::Show() will NOT scale the menu down if there are less options than the maximum capacity (i.e. options.size() < viewRange)
	bool titleSetting;		// defaults to false; if true, OverlayMenu::Show() will display the name of the OverlayMenu (inherited from the class Overlay) at the position indicated by titlePosition
	Position titlePosition;	// the position of the menu title text (if shown); by default, title is positioned TILEHEIGHT's height (px) above the menu background image with a margin of OVERLAYMENU_DEFAULT_MARGIN (px)
	vector<string> options;	// the different selectable options in the OverlayMenu; also acts as the status returned from "OverlayMenu::Show()"; by default, has one option "Cancel" at index 0
};

/*
	class Hud - a displayable hud
*/
class Hud : public Overlay {
public:
	Hud();	// default
	Hud(sf::RenderWindow* rw, Position p, int w, int h);
	Hud(sf::RenderWindow* rw, int x, int y, int w, int h);
};
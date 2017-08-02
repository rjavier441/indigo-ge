#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdio>	//sprintf()
#include <cstdlib>	//itoa()
#include <string>
#include <list>
// #include "Player.h"
#include "Character.h"
#include "Scaling.h"
#include "Items.h"
using namespace std;

struct PixelCoordinate {
	int x, y;
};
struct PlayerStat {
	string name;
	int level;
	int xp;
	int maxhp;
	int hp;
	int armor;
	int magic;
	int atk;
};

string stringify(int);	//turns an int to a string and returns the string

class MenuButton {
public:
	MenuButton(string, string, int, int, int, int);		//constructor w/ button name, assoc. action, left, top, width, and height (note: the action is the exact same value as the name)

	void setHovering(bool);		//sets the hovering status as true or false

	bool isClicked(int x, int y);	//checks position of clicks/mouse hovers, and returns action if Box was clicked
	string getName();
	virtual string getAction();
	int getTop();
	int getLeft();
	int getHeight();
	int getWidth();
	bool getHovering();
private:
	string Name;
	string Action;
	int Top;
	int Left;
	int Height;
	int Width;
	bool Hovering;
};

class InventorySlot : public MenuButton {
public:
	InventorySlot(string item_name, string action, int left, int top, int width, int height);

	void insert(Item);	// insert item data into the inventory slot
	// void insert(Weapon);	// ^

	Item* getItem();	// return pointer to item information represented by this slot
	
	string getAction();
private:
	Item item;
	bool empty;
};

class Menu {
friend class InventoryMenu;
public:
	Menu(string menu_name, sf::RenderWindow* w);	//constructor with menu title (you'll need to call assign before the menu is used)
	Menu(string menu_name, list<string>& n, sf::RenderWindow* w);		//constructor w/ menu title, list of buttons to add

	void setWindowDimensions(int width, int height);	// set window dimensions (disables automatic dimension calculations done by the  assign() function)
	void setMenuBackground(string path);	//set the menu background img
	void setMenuButtonBackground(string path);	//set the menu button background img
	void setMenuFont(string path);	//set font
	void setTitlePosition(int xpixel, int ypixel);	//set title position
	virtual void assign(list<string>&);	//assign/reassign buttons to the menu object. Also automatically scales objects, if scaling hasn't been done already

	virtual string Show(bool overrideMenuImg = false);	//runs the menu; allows control over whether to display the base menu's texture
	string leftClick(int, int);	//handles a left-clicking event when in a menu; takes an x,y coords of an event.mouseButton object
	virtual string isHovering(int, int);	//returns a button name if mouse is hovering over a button, else returns empty string
	sf::RenderWindow* getWindowPtr();

	// Button Backing/Click Region Scaling Functions
	void setScale(float x, float y);
	float getScaleX();
	float getScaleY();

	// Menu Background Scaling Functions
	void setBackgroundScale(float x, float y);
	float getBackgroundScaleX();
	float getBackgroundScaleY();

	string backgroundImg;	// Path to background img
	string buttonImg;	// Path to button backing img
	string textFont;	// Path to text font
private:
	virtual void checkHovering(int, int);	//checks to see if the mouse is hovering over a button, and changes the button's Hovering status accordingly; takes x,y coords from an event.mouseMove object
	float adjustMouseDimension (float absoluteMouseCoord, float absoluteWindowDim, float originalWindowDim); // calculates mouse position dimension based on a ratio of the mouse's current absolute position and window's absolute size, and the original absolute size of the window. This effectively maps the dimension in the window's relative coordinate system.

	sf::RenderWindow* WINDOW;
	int windowHeight;
	int windowWidth;
	PixelCoordinate titlePos;
	string Title;
	list<MenuButton> Buttons;
	FloatScaler localMenuScaler;	// click region scaler
	FloatScaler localBackgroundScaler;	// background texture scaler
};

class StatMenu : public Menu {
public:
	StatMenu(string menu_name, sf::RenderWindow* w, Player* p);
	StatMenu(string menu_name, list<string>& n, sf::RenderWindow* w, Player* p);

	string Show();
private:
	void loadPlayerStats(Player* p);

	sf::RenderWindow* WINDOW;	// since menu base class's WINDOW is private, stat menu needs its own
	sf::RenderTexture STATMENU;
	PlayerStat Stats;
	string statImg;	// Path to background img of the stat menu
	string statFont; // Path to font file of the stat menu
};

class InventoryMenu : public Menu {
public:
	InventoryMenu(string menu_name, sf::RenderWindow* window_pointer, Player* main_character);

	void setImg(string imgFileName);	//image must be stored in img/
	void setSlotImg(string path);		// sets path of inventory slot img
	void setFont(string fontFileName);	//font must be stored in fonts/
	void assign(list<string>&);	//assign inventory buttons/item slots

	string Show();

	string isHovering(int, int);
private:
	void checkHovering(int, int);
	void loadInventory(Player* main_character);	// Loads main character's inventory to the InventoryMenu

	sf::RenderWindow* WINDOW;
	sf::RenderTexture IMENU;
	Inventory* INV;
	string invTitle;
	string invImg;
	string invSlotImg;
	string invFont;
	list<InventorySlot> invSlots;
	FloatScaler invSlotScaler;
};
#pragma once
#include <string>
#include <vector>
#include "Utilities.h"
using namespace std;

// Defined Item Types
enum ItemType {
	Unknown_t,
	Quest_t,
	Weapon_t,
	Potion_t,
	Key_t,
	Armor_t,
	Clothing_t
};





// Basic Barebones Item
struct Item {
	Item();
	Item(string n, ItemType tc, string i, string d, int w, int a);
	Item(string n, string t, string i, string d, int w, int a);	// will deprecate soon

	Item operator=(const Item&);
	string findType(ItemType tc);	// returns the string name corresponding to the ItemType "tc"

	string Name;	// The name of the item
	string Type;	// The type of item
	ItemType TypeCode;	// the type of item, in the form of an enumeration ItemType
	string Image;	// The item's image
	string Description;	// The item's description
	int Weight;		// The item's weight
	int Amount;		// The amount of the item
};
typedef struct Item Item;





// Basic Item Types
struct Weapon : Item {
	Weapon();	// default
	Weapon(string n, string i, string d, int w, int a, int dmg);

	int Damage;		// The damage output of this item; defaults to 0
};
typedef struct Weapon Weapon;

struct Potion : Item {	// includes antidotes
	Potion();	// default
	Potion(string n, string i, string d, int w, int a, int ptcy);

	int Potency;		// The amount of points the potion buffs hp/mp/armor for; defaults to 0
};
typedef struct Potion Potion;

struct Key : Item {
	Key();		// default
	Key(string n, string i, string d, int w, int a, string dname);

	string DoorName;	// The name of the door that the key opens; defaults to empty string
};
typedef struct Key Key;

struct Armor : Item {	// includes clothing
	Armor();

	int Defense;	// The amount of attack points this armor negates; defaults to 0
};
typedef struct Armor Armor;





// Standard Inventory
struct Inventory {
	short Capacity;	// The maximum size of your inventory (in number of items)
	short Size;		// The current amount of items in your inventory
	short Weight;	// The current weight of your inventory
	short MaxWeight;	// The maximum amount of weight your inventory can hold

	bool hasKey(string dn);	// Returns true if the inventory has the key to open the door named "dn"

	vector<Item> items;
	vector<Weapon> weapons;
	vector<Potion> potions;
	// vector<Antidote> antidotes;	// DEPRECATED
	vector<Key> keys;
	vector<Armor> armors;
	// vector<Clothing> clothes;	// DEPRECATED
	int gp;			// The character's currency; It's in here so that your amount of currency does not affect inventory usage
};
typedef struct Inventory Inventory;

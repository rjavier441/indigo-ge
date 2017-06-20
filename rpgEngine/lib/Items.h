#pragma once
#include <string>
#include "Utilities.h"
using namespace std;

// Basic Barebones Item
struct Item {
	Item();

	string Name;	// The name of the item
	string Type;	// The type of item
	string Image;	// The item's image
	string Description;	// The item's description
	int Amount;		// The amount of the item
};

// Basic Item Types
struct Weapon : Item {
	Weapon();

	int Damage;		// The damage output of this item
};
struct Potion : Item {
	Potion();

	int Potency;		// The amount of points the potion buffs hp/mp/armor for
};
struct Antidote : Potion {
	Antidote();


};
struct Key : Item {
	Key();

	string DoorName;	// The name of the door that the key opens
};
struct Armor : Item {
	Armor();

	int Defense;	// The amount of attack points this armor negates
};
struct Clothing : Item {
	Clothing();

	int Defense;	// The amount of attack points this clothing negates (lower than armor)
};




// Standard Inventory
struct Inventory {
	short Capacity;	// The maximum size of your inventory
	short Size;		// The current amount of items in your inventory
	int gp;			// The character's currency; It's in here so that your amount of currency does not affect inventory usage
};
typedef struct Inventory Inventory;
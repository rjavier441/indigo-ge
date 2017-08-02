#include "Items.h"	// type Item

/*
	type Item
*/
Item::Item () {
	Name = "";
	TypeCode = Unknown_t;
	Type = "";
	Image = "";
	Description = "";
	Weight = 0;
	Amount = 0;
}
Item::Item (string n, ItemType tc, string i, string d, int w, int a) {
	Name = n;
	TypeCode = tc;
	Type = findType(tc);
	Image = i;
	Description = d;
	Weight = w;
	Amount = a;
}
Item::Item (string n, string t, string i, string d, int w, int a) {
	Name = n;
	TypeCode = Unknown_t;
	Type = t;
	Image = i;
	Description = d;
	Weight = w;
	Amount = a;
}

Item Item::operator= (const Item& i) {
	Item temp;
	temp.Name = i.Name;
	temp.Type = i.Type;
	temp.TypeCode = i.TypeCode;
	temp.Image = i.Image;
	temp.Description = i.Description;
	temp.Weight = i.Weight;
	temp.Amount = i.Amount;

	return temp;
}
string Item::findType (ItemType tc) {
	string temp;
	switch (tc) {
		case Unknown_t:
			temp = "Unknown Item";
			break;
		case Quest_t:
			temp = "Quest Item";
			break;
		case Weapon_t:
			temp = "Weapon";
			break;
		case Potion_t:
			temp = "Potion";
			break;
		case Key_t:
			temp = "Key";
			break;
		case Armor_t:
			temp = "Armor";
			break;
		case Clothing_t:
			temp = "Clothing";
			break;
		default:
			temp = "";
			break;
	}

	return temp;
}





/*
	Struct Weapon
*/
Weapon::Weapon () : Item () {
	TypeCode = Weapon_t;
	Type = findType(TypeCode);
	Damage = 0;
}
Weapon::Weapon (string n, string i, string d, int w, int a, int dmg) : Item (n, Weapon_t, i, d, w, a) {
	Type = findType(TypeCode);
	Damage = dmg;
}


/*
	Struct Potion
*/
Potion::Potion () : Item () {
	TypeCode = Potion_t;
	Type = findType(TypeCode);
	Potency = 0;
}
Potion::Potion (string n, string i, string d, int w, int a, int ptcy) : Item (n, Potion_t, i, d, w, a) {
	Type = findType(TypeCode);
	Potency = ptcy;
}


/*
	Struct Key
*/
Key::Key () : Item () {
	TypeCode = Key_t;
	Type = findType(TypeCode);
	DoorName = "";
}
Key::Key (string n, string i, string d, int w, int a, string dname) : Item (n, Key_t, i, d, w, a) {
	Type = findType(TypeCode);
	DoorName = dname;
}


/*
	Struct Armor
*/
Armor::Armor () : Item () {
	TypeCode = Armor_t;
	Type = findType(TypeCode);
	Defense = 0;
}






/*
	Struct Inventory
*/
bool Inventory::hasKey (string n) {
	// if no keys in possession, automatically return false
	if (keys.empty()) return false;

	for (int i = 0; i < keys.size(); i++) {
		// if key[i] opens the door named "n", return true;
		if (keys[i].DoorName == n) {
			return true;
		}
	}

	return false;
}

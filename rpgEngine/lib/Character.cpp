#include "Character.h"
#include "Items.h"	//Inventory, Items
using namespace std;

/*Class Character*/
Character::Character () {
	Name = "???";
	Image = "";
	Pos.x = 0;
	Pos.y = 0;
	Loc.x = 0;
	Loc.y = 0;
	Dir = D;
	completedMove = true;
	animationPhase = 0;
}
Character::Character (string n) {
	Name = n;
	Image = "";
	Pos.x = 0;
	Pos.y = 0;
	Loc.x = 0;
	Loc.y = 0;
	Dir = D;
	completedMove = true;
	animationPhase = 0;
}

Character& Character::setName (string n) {
	Name = n;
	return *this;
}
Character& Character::setImage (string s) {
	Image = s;
	return *this;
}
bool Character::setLocation (MapData* DATA, int x, int y) {
	cout << endl << "[Character] x:" << x << " y:" << y << "  Width:" << DATA->getWidth() << " Height:" << DATA->getHeight() << endl;

	if (x > DATA->getWidth() || y > DATA->getHeight() || x < 0 || y < 0) {
		cout << endl << "[Character] Error: Location out of bounds" << endl;
		return false;
	} else {
		Loc.x = x;
		Loc.y = y;
		setPosition(Loc.x * 32, Loc.y * 32);
		cout << "Loc:(" << Loc.x << "," << Loc.y << ") Pos:(" << Pos.x << "," << Pos.y << ")" << endl;
		return true;
	}
}
void Character::move (MapData* DATA, Move movement) {
	// Movement by tiles
	if (movement == Left) {
		Dir = L;	// Character will face this Direction, even if the adjacent tile is not passable
		if (Loc.x > 0 && DATA->isPassable(Loc.x - 1, Loc.y) && completedMove) {
			Loc.x--;
			completedMove = false;
		}
	} else if (movement == Right) {
		Dir = R;	// Character will face this Direction, even if the adjacent tile is not passable
		if (Loc.x < DATA->getWidth() && DATA->isPassable(Loc.x + 1, Loc.y) && completedMove) {
			Loc.x++;
			completedMove = false;
		}
	} else if (movement == Up) {
		Dir = U;	// Character will face this Direction, even if the adjacent tile is not passable
		if (Loc.y > 0 && DATA->isPassable(Loc.x, Loc.y - 1) && completedMove) {
			Loc.y--;
			completedMove = false;
		}
	} else if (movement == Down) {
		Dir = D;	// Character will face this Direction, even if the adjacent tile is not passable
		if (Loc.y < DATA->getHeight() && DATA->isPassable(Loc.x, Loc.y + 1) && completedMove) {
			Loc.y++;
			completedMove = false;
		}
	}
	// cout << endl << "[Character] New Coordinates: (" << Loc.x << "," << Loc.y << ")";
}
bool Character::setPosition (int x, int y) {
	if (x < 0 || y < 0) {
		cout << endl << "[Character] Error: Negative position" << endl;
		return false;
	} else {
		Pos.x = x;
		Pos.y = y;
		return true;
	}
}
void Character::setMoveDone (bool b) {
	completedMove = b;
}
void Character::setPhase (int p) {
	animationPhase = p;
}

string Character::getName () {
	return Name;
}
string Character::getImage () {
	return Image;
}
Position Character::getPosition () {
	return Pos;
}
TileCoord Character::getLocation () {
	return Loc;
}
Direction Character::getDirection () {
	return Dir;
}
Position* Character::getPositionPtr () {
	return &Pos;
}
TileCoord* Character::getLocationPtr () {
	return &Loc;
}
bool Character::finishedMove () {
	return completedMove;
}
int Character::getPhase () {
	return animationPhase;
}



/*Class Player*/
Player::Player () : Character () {
	Level = 0;
	Experience = 0;
	MaxHealth = 100;
	Health = 100;
	ArmorPts = 0;
	Magic = 0;
	Attack = 10;
}
Player::Player (string n, int lvl, int xp, int mhp, int hp, int ap, int md, int ad) : Character (n) {
	Level = lvl;
	Experience = xp;
	MaxHealth = mhp;
	Health = hp;
	ArmorPts = ap;
	Magic = md;
	Attack = ad;
}

Player& Player::setName (string s) {
	Character::setName(s);
	return *this;
}
Player& Player::setImage (string s) {
	Character::setImage(s);
	return *this;
}
Player& Player::setLevel (int l) {
	Level = l;
	return *this;
}
Player& Player::setExperience (int x) {
	Experience = x;
	return *this;
}
Player& Player::setMaxHealth (int m) {
	MaxHealth = m;
	return *this;
}
Player& Player::setHP (int h) {
	Health = h;
	return *this;
}
Player& Player::setArmor (int a) {
	ArmorPts = a;
	return *this;
}
Player& Player::setMagic (int m) {
	Magic = m;
	return *this;
}
Player& Player::setAttack (int a) {
	Attack = a;
	return *this;
}
Player& Player::pickup (Item i) {
	Bag.items.push_back(i);
	return *this;
}
Player& Player::pickup (Weapon w) {
	Bag.weapons.push_back(w);
	return *this;
}
Player& Player::pickup (Potion p) {
	Bag.potions.push_back(p);
	return *this;
}
// Player& Player::pickup (Antidote a) {	// DEPRECATED
// 	Bag.antidotes.push_back(a);
// 	return *this;
// }
Player& Player::pickup (Key k) {
	Bag.keys.push_back(k);
	return *this;
}
Player& Player::pickup (Armor a) {
	Bag.armors.push_back(a);
	return *this;
}
// Player& Player::pickup (Clothing c) {	// DEPRECATED
// 	Bag.clothes.push_back(c);
// 	return *this;
// }

void Player::printInventory () {
	printf("%s\n", "[Player] Inventory Contents:");

	// Print Items
	printf("[Player]===Items===\n");
	if (Bag.items.empty()) {
		printf("[Player]\tEmpty\n");
	} else {
		for (int i = 0; i < Bag.items.size(); i++) {
			printf("[Player]\t%s [%s type] (path:%s), %s {%d lbs} <Qty:%d>\n", Bag.items[i].Name.c_str(), Bag.items[i].Type.c_str(), Bag.items[i].Image.c_str(), Bag.items[i].Description.c_str(), Bag.items[i].Weight, Bag.items[i].Amount);
		}
	}

	// // Print Weapons
	// printf("[Player]===Weapons===");
	return;
}

int Player::getLevel () {
	return Level;
}
int Player::getExperience () {
	return Experience;
}
int Player::getMaxHealth () {
	return MaxHealth;
}
int Player::getHP () {
	return Health;
}
int Player::getArmor () {
	return ArmorPts;
}
int Player::getMagic () {
	return Magic;
}
int Player::getAttack () {
	return Attack;
}
Inventory* Player::getInventoryPtr () {
	return &Bag;
}
#pragma once
#include <cstdio>	// printf()
#include <string>	// string
// #include "Items.h"	// DO NOT INCLUDE: causes circular dependency w/ Utilities.h
using namespace std;

#define DOOR_MINRANGE 1	// player must be one tile away to access the door

/*
	Interactions.h - constructs defining interactions and usage properties of world objects
*/

// Action Types - the different types of actions the player can do in the world
enum ActionType {
	AT_UNDEFINED = 0,	// undefined action
	AT_ENTER,		// inter-map travel
	AT_EXAMINE,		// acquire an object's description
	AT_PICKUP		// add item to inventory
};




// Map Object Types - the different types of objects in the world that the player can interact with
enum MapObject {
	MO_UNKNOWN = 0,		// undefined object
	MO_DOORWAY,		// e.g. Doors (locked or unlocked)
	MO_TRAVELPOINT,	// e.g. entryways, passages, etc. (things that allow the player to travel between maps OTHER THAN doorways)
	MO_CONTAINER,	// e.g. chests, closets, etc. (things that can have inventories/contain items)
	MO_ATTAINABLE	// e.g. tools, quest items, gp, etc. (things that can be added to the player's inventory)
};





// Object Properties - characteristics of useable/interactive items/objects in the map
struct Exploitable {	// mandatory struct for all interactable objects in the World
	Exploitable();		// default
	Exploitable(int);	// sets minimum interaction range

	ActionType action;	// the type(s) of action for this object
	int minRange;		// the minimum range (in tiles) required to interact with the exploitable object; defaults to 0 (i.e. the player must be directly standing on the object in question)
};

struct Lockable {	// struct for a lockable object; minRange defaults to LOCKABLE_DEFAULT_MINRANGE
	Lockable(bool lockState = false);	// if lockState = true, the door starts out in a locked state

	void setKeyName(string kn);	// sets "keyName"
	bool lock(string k);	// attempt to lock a lockable object with Key Name "k"; returns true on success, false otherwise
	bool unlock(string k);// attempt to unlock a lockable object with Key Name "k"; returns true on success, false otherwise

	bool isLocked();	// returns the value of "locked"
private:
	bool locked;	// determines whether a door requires a key to open; defaults to false
	string keyName;	// the name of the required key to unlock this door
};





// Interaction - a construct associating an action with a target object
/*
	Note: A "nulled interaction" is an interaction whose action and target members are set to their designated "undefined" values (i.e. action = AT_UNDEFINED, target = MO_UNKNOWN)
*/
struct Interaction {
	Interaction();		// default
	Interaction(ActionType a, string aStr, string aDesc, MapObject t, int contextId, int elementId);

	int cid;	// the index of the action's context information; can be used to locate relevant information within a context struct
	ActionType action;	// the enum of the action to perform
	string actionStr;	// the string representation of "action"
	string actionDesc;	// a description of the action
	MapObject target;	// the enum of the object to manipulate
	int eid;		// the index of an object's data; can be used to locate relevant information of said data within the appropriate class World member (i.e. locate a doorway's data using this index with the vector "World::DOORWAY")
};
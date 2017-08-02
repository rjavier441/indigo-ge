#include "Interactions.h"	// Exploitable

/*
	struct Exploitable - a base class for all interactable entities within the world
*/
Exploitable::Exploitable () {
	minRange = 0;
}
Exploitable::Exploitable (int mr) {
	minRange = mr;
}





/*
	struct Lockable
*/
Lockable::Lockable (bool lockState) {
	locked = lockState;
	keyName = "";
}

void Lockable::setKeyName (string kn) {
	keyName = kn;
	return;
}
bool Lockable::lock (string k) {
	if (k == keyName) {
		locked = true;
		return true;
	}
	return false;
}
bool Lockable::unlock (string k) {
	if (k == keyName) {
		locked = false;
		return true;
	}
	return false;
}

bool Lockable::isLocked () {
	return locked;
}





/*
	struct Interaction
*/
Interaction::Interaction () {
	cid = 0;
	action = AT_UNDEFINED;
	actionStr = "";
	actionDesc = "";
	target = MO_UNKNOWN;
	eid = 0;
}
Interaction::Interaction (ActionType a, string aStr, string aDesc, MapObject t, int contextId, int elementId) {
	cid = contextId;
	action = a;
	actionStr = aStr;
	actionDesc = aDesc;
	target = t;
	eid = elementId;
}

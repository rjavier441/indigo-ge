/*
Scaling.h - Keeping things "to scale"

	The constructs defined in this implementation (header) file are meant to properly scale 2D elements within a window. This makes them suitable for scaling elements in the event than the window is resized (and later: in the event a video mode is changed).
*/

#ifndef SCALING_H
#define SCALING_H

#include <SFML/Graphics.hpp>

using namespace std;
/*
struct intScaler {
	int x;
	int y;
};
typedef struct intScaler intScaler;

struct floatScaler {
	float x;
	float y;
};
typedef struct floatScaler floatScaler;

struct doubleScaler {
	double x;
	double y;
};
typedef struct doubleScaler doubleScaler;
*/

typedef struct {
	bool scaled;
	int x, y;
} ScaleInt;
// typedef struct ScaleInt ScaleInt;

typedef struct {
	bool scaled;
	float x, y;
} ScaleFloat;
// typedef struct ScaleFloat ScaleFloat;

typedef struct {
	bool scaled;
	double x, y;
} ScaleDouble;
// typedef struct ScaleDouble ScaleDouble;


/*
Class FloatScaler - scale using floats
	Float scaler is used to calculate the x & y ratios between a sf::Sprite's global bounds (a sf::FloatRect) and the current sf::RenderWindow. Once scale() is called, the ratios can be acquired using xScale() and yScale(), and can then be multiplied/divided as desired to precisely scale a sprite.
*/
class FloatScaler {
public:
	FloatScaler();
	FloatScaler(sf::Sprite* s, sf::RenderWindow* w);	// invokes scale() on creation

	bool isUnscaled();	// returns true if scale is not scaled
	void reset();	// marks the scale as unscaled and enables rescaling
	void scale(sf::Sprite* s, sf::RenderWindow* w);	// calculates 2D scaling parameters for s based on w's dimensions; this method automatically checks if scale is scaled. Calling the function scale() (after previously scaling) without calling reset() has no effect.
	void scale(sf::Sprite* s, int x, int y);	// same as above, but allows direct input of window dimensions; can also be used to acquire the scale of s in reference to an arbitrary size "x" by "y" rect
	void scale(sf::Text* t, int x, int y);	// same as above, but for text elements
	void scale(float x, float y);	// same as above for sf::Sprite*, but allows direct input of the scale factor parameters
	void inferScale(sf::Sprite* src, float srcScaleX, float srcScaleY, float objWidth, float objHeight);	// scale an object based off of another object's scale and dimensions
	float xScale();	// returns the scaling factor for the x axis
	float yScale();	// returns the scaling factor for the y axis
private:
	ScaleFloat Scale;
};

#endif
/* SCALING_H */
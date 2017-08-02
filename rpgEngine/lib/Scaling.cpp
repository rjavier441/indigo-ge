#include "Scaling.h"
#include <cstdio>	// printf()

/*
	Class FloatScaler
*/
FloatScaler::FloatScaler () {
	Scale.scaled = false;
	Scale.x = 0;
	Scale.y = 0;
}

FloatScaler::FloatScaler (sf::Sprite* s, sf::RenderWindow* w) {
	Scale.scaled = false;
	Scale.x = 0;
	Scale.y = 0;
	scale(s, w);
}

bool FloatScaler::isUnscaled () {
	return !Scale.scaled;
}

void FloatScaler::reset () {
	Scale.scaled = false;
	return;
}

void FloatScaler::scale (sf::Sprite* s, sf::RenderWindow* w) {
	if (this->isUnscaled()) {
		// printf("Scaling...");	// debug
		// Acquire Current Window Size
		sf::Vector2u winsize = w->getSize();

		// Acquire size of sprite rectangle in this current frame
		sf::FloatRect spriteRect = s->getGlobalBounds();

		// Scale
		Scale.x = (float) winsize.x / (float) spriteRect.width;
		Scale.y = (float) winsize.y / (float) spriteRect.height;
		// printf("x:%f y:%f\n", Scale.x, Scale.y);	// debug
		Scale.scaled = true;
	}
	return;
}

void FloatScaler::scale (sf::Sprite* s, int windowWidth, int windowHeight) {
	if (this->isUnscaled()) {
		// Acquire size of sprite rectangle in this current frame
		sf::FloatRect spriteRect = s->getGlobalBounds();

		// Scale
		Scale.x = (float) windowWidth / (float) spriteRect.width;
		Scale.y = (float) windowHeight / (float) spriteRect.height;
		// printf("x:%f y:%f\n", Scale.x, Scale.y);	// debug
		Scale.scaled = true;
	}
	return;
}

void FloatScaler::scale (sf::Text* t, int windowWidth, int windowHeight) {
	if (this->isUnscaled()) {
		// Acquire size of sprite rectangle in this current frame
		sf::FloatRect spriteRect = t->getGlobalBounds();

		// Scale
		Scale.x = (float) windowWidth / (float) spriteRect.width;
		Scale.y = (float) windowHeight / (float) spriteRect.height;
		// printf("x:%f y:%f\n", Scale.x, Scale.y);	// debug
		Scale.scaled = true;
	}
	return;
}

void FloatScaler::scale (float x, float y) {
	if (this->isUnscaled()) {
		// printf("Implicit Scaling...");	// debug
		Scale.x = x;
		Scale.y = y;
		// printf("x:%f y:%f\n", Scale.x, Scale.y);	// debug
		Scale.scaled = true;
	}
	return;
}

void FloatScaler::inferScale (sf::Sprite* src, float srcScaleX, float srcScaleY, float objWidth, float objHeight) {
	// Infer window's original dimensions (i.e. at the time of the src's scaling)
	sf::FloatRect srcRect = src->getGlobalBounds();
	float windowX = srcScaleX * srcRect.width;
	float windowY = srcScaleY * srcRect.height;

	// Infer obj's scale based on the inferred window's dimensions
	float objScaleX = windowX / objWidth;
	float objScaleY = windowY / objHeight;

	// Set inferred scale
	scale(objScaleX, objScaleY);
	return;
}

float FloatScaler::xScale () {
	return Scale.x;
}

float FloatScaler::yScale () {
	return Scale.y;
}
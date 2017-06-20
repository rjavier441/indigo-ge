#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdio>	// printf()
using namespace std;

int main (void) {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Scale Test");

	bool scaled = false;
	float scaleX;
	float scaleY;
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			sf::Vector2u size = window.getSize();
			unsigned int wWidth = size.x;
			unsigned int wHeight = size.y;
			printf("Window:%dx%d ", wWidth, wHeight);

			if (event.type == sf::Event::Closed) {
				printf("Window Closed\n");
				window.close();
			}

			window.clear(sf::Color::Black);

			sf::Texture texture;
			if (!texture.loadFromFile("../img/splashscreen.png")) {
				printf("Error");
				window.close();
				return 1;
			}

			sf::Sprite splashSprite(texture);
			sf::FloatRect spriteRect = splashSprite.getGlobalBounds();
			printf(" Sprite:%fx%f ", spriteRect.width, spriteRect.height);

			if (!scaled) {
				scaleX = (float) wWidth/(float) spriteRect.width;
				scaleY = (float) wHeight/(float) spriteRect.height;
				scaled = true;
			}
			printf(" scaleX:%f scaleY:%f\n", scaleX, scaleX);
			splashSprite.setScale(scaleX, scaleY);

			window.draw(splashSprite);

			window.display();
		}
	}

	return 0;
}
#include <iostream>

#include <SFML/Graphics.hpp>

#include "World/World/World.h"

int main() {
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pirate Game");
	window.setVerticalSyncEnabled(false);

	PirateGame::World world(&window);

	world.setUpWorld();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
    	world.gameLoop(event);
		window.display();
    }

	return 0;
}

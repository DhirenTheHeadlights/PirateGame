#pragma once

/// This class contains all the global values used throughout the game.

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

namespace PirateGame::Globals {
	inline bool showHUD = true;
	inline bool showInventory = false;
	inline sf::RenderWindow* window = nullptr;

	inline sf::Vector2f getGlobalMousePosition() {
		const sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		return window->mapPixelToCoords(mousePosition);
	}

	std::string keyToString(sf::Keyboard::Key key);

	std::string buttonToString(sf::Mouse::Button button);
}
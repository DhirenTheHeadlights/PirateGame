#pragma once

/// Global font handler for pirate game

#include <SFML/Graphics.hpp>
#include <iostream>

namespace PirateGame {
	namespace Font {
		// Fonts
		inline sf::Font timesNewRoman;
		inline sf::Font pixelifySansRegular;
		inline sf::Font pixelifySansMedium;
		inline sf::Font pixelifySansSemiBold;
		inline sf::Font pixelifySansBold;
		inline sf::Font globalFont;

		inline void setUpFonts() {
			// Initialize the fonts
			if (!timesNewRoman.loadFromFile(RESOURCES_PATH "Fonts/times_new_roman.ttf")) {
				std::cout << "Error loading Times New Roman font" << '\n';
			}
			if (!pixelifySansRegular.loadFromFile(RESOURCES_PATH "Fonts/PixelifySans-Regular.ttf")) {
				std::cout << "Error loading Pixelify Sans Regular font" << '\n';
			}
			if (!pixelifySansMedium.loadFromFile(RESOURCES_PATH "Fonts/PixelifySans-Medium.ttf")) {
				std::cout << "Error loading Pixelify Sans Medium font" << '\n';
			}
			if (!pixelifySansSemiBold.loadFromFile(RESOURCES_PATH "Fonts/PixelifySans-SemiBold.ttf")) {
				std::cout << "Error loading Pixelify Sans SemiBold font" << '\n';
			}
			if (!pixelifySansBold.loadFromFile(RESOURCES_PATH "Fonts/PixelifySans-Bold.ttf")) {
				std::cout << "Error loading Pixelify Sans Bold font" << '\n';
			}
			if (!globalFont.loadFromFile(RESOURCES_PATH "Fonts/PixelifySans-Regular.ttf")) {
				std::cout << "Error loading global font" << '\n';
			}
		};
	};
}
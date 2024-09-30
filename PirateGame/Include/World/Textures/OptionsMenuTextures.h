#pragma once

/// Options menu textures

#include "Globals/TextureHandler.h"

namespace PirateGame {
	class OptionsMenuTextureHandler : public TextureHandler {
	public:
		OptionsMenuTextureHandler() {
			// Load all the textures
			background.loadFromFile(RESOURCES_PATH "Sprites/Menu/OptionsMenu/options_menu_background.png");
			leftInteractable.loadFromFile(RESOURCES_PATH "Sprites/Menu/OptionsMenu/options_menu_button_gray_left.png");
			dropDown.loadFromFile(RESOURCES_PATH "Sprites/Menu/OptionsMenu/options_menu_drop_down_right_gray.png");
			rightInteractable.loadFromFile(RESOURCES_PATH "Sprites/Menu/OptionsMenu/options_menu_right_interactable.png");
			tab.loadFromFile(RESOURCES_PATH "Sprites/Menu/OptionsMenu/options_menu_tab.png");
		}

		// Getters
		sf::Texture& getBackground() { return background; }
		sf::Texture& getLeftInteractable() { return leftInteractable; }
		sf::Texture& getDropDown() { return dropDown; }
		sf::Texture& getRightInteractable() { return rightInteractable; }
		sf::Texture& getTab() { return tab; }

	private:
		// Textures
		sf::Texture background;
		sf::Texture leftInteractable;
		sf::Texture dropDown;
		sf::Texture rightInteractable;
		sf::Texture tab;
	};
}
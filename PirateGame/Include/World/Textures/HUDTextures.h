#pragma once

/// HUD textures for the game.

#include "Globals/TextureHandler.h"

namespace PirateGame {
	class HUDTextureHandler : public TextureHandler {
	public:
		HUDTextureHandler() {
			// Load health bar textures
			healthBarGreen.loadFromFile(RESOURCES_PATH "Sprites/Menu/HUDMenu/health_bar_green.png");
			healthBarRed.loadFromFile(RESOURCES_PATH "Sprites/Menu/HUDMenu/health_bar_red.png");
			miniMap.loadFromFile(RESOURCES_PATH "Sprites/Menu/HUDMenu/minimap_sprite.png");
			miniMapShipIcon.loadFromFile(RESOURCES_PATH "Sprites/Menu/HUDMenu/minimap_ship_icon.png");
			settingsButton.loadFromFile(RESOURCES_PATH "Sprites/Menu/HUDMenu/settings_button.png");
			infoBox.loadFromFile(RESOURCES_PATH "Sprites/Menu/HUDMenu/HUD_info_icon.png");
		}

		// Getters
		sf::Texture& getHealthBarGreen() { return healthBarGreen; }
		sf::Texture& getHealthBarRed() { return healthBarRed; }
		sf::Texture& getMiniMap() { return miniMap; }
		sf::Texture& getMiniMapShipIcon() { return miniMapShipIcon; }
		sf::Texture& getSettingsButton() { return settingsButton; }
		sf::Texture& getInfoBox() { return infoBox; }
	private:
		sf::Texture healthBarGreen;
		sf::Texture healthBarRed;
		sf::Texture miniMap;
		sf::Texture miniMapShipIcon;
		sf::Texture settingsButton;
		sf::Texture infoBox;
	};
}
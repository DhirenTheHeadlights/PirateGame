#pragma once

/// Tileable and repeatable textures for the menus.

#include "Globals/TextureHandler.h"

namespace PirateGame {
	class InventoryTextureHandler : public TextureHandler {
	public:
		InventoryTextureHandler() {
			background.loadFromFile(RESOURCES_PATH "Sprites/Menu/InventoryMenu/inventory_menu.png");
			inventoryDisplay.loadFromFile(RESOURCES_PATH "Sprites/Menu/InventoryMenu/inventory_inventory_display.png");
			inventoryItemDisplay.loadFromFile(RESOURCES_PATH "Sprites/Menu/InventoryMenu/inventory_menu_item_display.png");
			inventoryTextDisplay.loadFromFile(RESOURCES_PATH "Sprites/Menu/InventoryMenu/inventory_text_display.png");
			inventoryShipDisplay.loadFromFile(RESOURCES_PATH "Sprites/Menu/InventoryMenu/inventory_ship_display.png");
		}

		// Getters
		sf::Texture& getBackground() { return background; }
		sf::Texture& getInventoryDisplay() { return inventoryDisplay; }
		sf::Texture& getInventoryItemDisplay() { return inventoryItemDisplay; }
		sf::Texture& getInventoryTextDisplay() { return inventoryTextDisplay; }
		sf::Texture& getInventoryShipDisplay() { return inventoryShipDisplay; }

	private:
		sf::Texture background;
		sf::Texture inventoryDisplay;
		sf::Texture inventoryItemDisplay;
		sf::Texture inventoryTextDisplay;
		sf::Texture inventoryShipDisplay;
	};
}
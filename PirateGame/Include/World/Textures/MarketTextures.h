#pragma once

/// Market texture handler

#include "Globals/TextureHandler.h"

namespace PirateGame {
	class MarketTextureHandler : public TextureHandler {
	public:
		MarketTextureHandler() {
			// Load all the textures
			bottomRightLeft.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/General/market_bottom_right_left.png");
			buySell.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Item/market_buy_sell_dark_gray.png");
			marketFarLeftRight.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Item/market_interactable_far_left_right_dark_gray.png");
			leftRightNavigation.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/General/market_left_right_navigation.png");
			marketMenu.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Item/market_menu.png");
			marketMiddle.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/General/market_middle.png");
			marketTopLeftRight.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Item/market_top_left_right_dark_gray.png");
			initialMenu.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Initial/enter_island_menu_initial.png");
			initialMenuButton.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Initial/enter_island_menu_button.png");
			islandBanner.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Initial/island_banner.png");
			marketTopMiddle.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Item/market_top_middle_dark_gray.png");
			marketBottomMiddle.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/General/market_bottom_middle.png");
			marketLeftRightNavigation.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/General/market_left_right_navigation.png");

			shipBuyMenu.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Ship/market_menu_buy_ship.png");
			shipBuyMenuTopLeft.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Ship/market_buy_ship_top_left.png");
			shipBuyMenuTopRight.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Ship/market_buy_ship_top_right.png");
			shipBuyMenuMiddleLeft.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Ship/market_buy_ship_middle_left.png");
			shipBuyMenuMiddleRight.loadFromFile(RESOURCES_PATH "Sprites/Menu/MarketMenu/Ship/market_buy_ship_middle_right.png");
		}

		// Getters
		sf::Texture& getBottomRightLeft() { return bottomRightLeft; }
		sf::Texture& getBuySell() { return buySell; }
		sf::Texture& getMarketFarLeftRight() { return marketFarLeftRight; }
		sf::Texture& getLeftRightNavigation() { return leftRightNavigation; }
		sf::Texture& getMarketMenu() { return marketMenu; }
		sf::Texture& getMarketMiddle() { return marketMiddle; }
		sf::Texture& getMarketTopLeftRight() { return marketTopLeftRight; }
		sf::Texture& getInitialMenu() { return initialMenu; }
		sf::Texture& getInitialMenuButton() { return initialMenuButton; }
		sf::Texture& getIslandBanner() { return islandBanner; }
		sf::Texture& getMarketTopMiddle() { return marketTopMiddle; }
		sf::Texture& getMarketBottomMiddle() { return marketBottomMiddle; }
		sf::Texture& getMarketLeftRightNavigation() { return marketLeftRightNavigation; }

		sf::Texture& getShipBuyMenu() { return shipBuyMenu; }
		sf::Texture& getShipBuyMenuTopLeft() { return shipBuyMenuTopLeft; }
		sf::Texture& getShipBuyMenuTopRight() { return shipBuyMenuTopRight; }
		sf::Texture& getShipBuyMenuMiddleLeft() { return shipBuyMenuMiddleLeft; }
		sf::Texture& getShipBuyMenuMiddleRight() { return shipBuyMenuMiddleRight; }
	private:
		// Sprites
		sf::Texture bottomRightLeft;
		sf::Texture buySell;
		sf::Texture marketFarLeftRight;
		sf::Texture leftRightNavigation;
		sf::Texture marketMenu;
		sf::Texture marketMiddle;
		sf::Texture marketTopLeftRight;
		sf::Texture marketTopMiddle;
		sf::Texture marketBottomMiddle;
		sf::Texture initialMenu;
		sf::Texture initialMenuButton;
		sf::Texture islandBanner;
		sf::Texture marketLeftRightNavigation;

		sf::Texture shipBuyMenu;
		sf::Texture shipBuyMenuTopLeft;
		sf::Texture shipBuyMenuTopRight;
		sf::Texture shipBuyMenuMiddleLeft;
		sf::Texture shipBuyMenuMiddleRight;
	};
}

#pragma once

/// This is a child menu class for the island menu.

#include <utility>

#include "UI/Menu/Menu.h"
#include "World/Objects/Ship/General/PlayerShip.h"
#include "World/Objects/General/ShopItem.h"

namespace PirateGame {
	enum class Page {
		marketPage1,
		marketPage2,
		marketPage3,
		shipUpgrades,
	};

	class IslandMenu : public Menu {
	public:
		IslandMenu(Context& context, std::vector<ShopItem>& market) : Menu(context), market(market) {};

		void setUpMenu() override;
		void setInteractablePositions() override;
		void addInteractablesToMenu() override;
		void addShipInventoryInteractables();
		void updateMarket();
		void draw() override;
		void update() override;
		void interactWithMenuItems() override;

		// Setters
		void setShip(PlayerShip& ship) { this->ship = &ship; };
		void setMarket(std::vector<ShopItem> market) const { this->market = std::move(market); }
		void setEnteredIsland(bool enteredIsland) { this->enteredIsland = enteredIsland; }
		void setHasPlayerSaidNo(bool playerPromptedOnce) { this->hasPlayerSaidNo = playerPromptedOnce; }

		// Getters
		bool getEnteredIsland() const { return enteredIsland; }
		bool getPlayerPromptedOnce() const { return hasPlayerSaidNo; }
	private:
		// Helpers
		void addMarketInteractables();
		void addGeneralInteractables();
		void addShipBuyInteractables();

		void drawMarket();
		void drawShipBuy();

		void interactWithMarket();
		void interactWithShipBuy();

		// Menu items
		float padding = 10.f;
		float gold = 1000.f;
		int textSize = 40;
		int interactableTextSizeSmall = 30;
		int interactableTextSizeBig = 60;
		const int numShipsForSale = 5;

		bool enteredIsland = false;
		bool addedInteractables = false;
		bool hasPlayerSaidNo = false;

		PlayerShip* ship = nullptr;

		Page currentPage = Page::marketPage1;

		std::vector<Page> pages = { Page::marketPage1, Page::shipUpgrades };

		sf::Sprite banner;
		sf::Sprite initialMenu;

		std::vector<Button> initialButtons;
		std::vector<Button> buyButtons;
		std::vector<Button> sellButtons;
		std::vector<TextDisplayBox> merchandise;
		std::vector<TextDisplayBox> shipInventoryInteractables;
		std::vector<TextDisplayBox> marketInventory;
		std::vector<Button> uiButtons;
		std::vector<Button> leftRightNavButtons;
		std::vector<TextDisplayBox> shipBuyTabs;
		std::vector<std::pair<ShipClass, std::vector<TextDisplayBox>>> shipStats;
		std::vector<Button> shipBuyButtons;

		sf::Vector2f bannerScale = sf::Vector2f(1.5f, 1.5f);

		// Gold text display box
		TextDisplayBox shipGoldDisplay;
		TextDisplayBox islandGoldDisplay;

		// Names
		TextDisplayBox islandNameDisplay;
		TextDisplayBox shipNameDisplay;
		TextDisplayBox marketNameDisplay;

		std::vector<ShopItem>& market;
		std::vector<ShopItem> shipInventory;

		std::string islandName = "Island Name";

		sf::Clock buyClock;

		// Specific values for menu item placement

		const sf::Vector2f initialButtonPositionLeft = sf::Vector2f(12.f, 12.f);
		const sf::Vector2f initialButtonPositionRight = sf::Vector2f(251.f, 12.f);

		const sf::Vector2f marketTopMiddle = sf::Vector2f(400.f, 22.f);
		const sf::Vector2f marketTopLeft = sf::Vector2f(20.f, 22.f);
		const sf::Vector2f marketTopRight = sf::Vector2f(1204.f, 22.f);
		const sf::Vector2f marketMiddle = sf::Vector2f(400.f, 162.f);
		const sf::Vector2f marketLeftMiddle = sf::Vector2f(20.f, 162.f);
		const sf::Vector2f marketSell = sf::Vector2f(210.f, 162.f);
		const sf::Vector2f marketBuy = sf::Vector2f(1204.f, 162.f);
		const sf::Vector2f marketRightMiddle = sf::Vector2f(1394.f, 162.f);
		const sf::Vector2f marketBottomLeft = sf::Vector2f(20.f, 883.f);
		const sf::Vector2f marketNavigationLeft = sf::Vector2f(304.f, 883.f);
		const sf::Vector2f marketNavigationRight = sf::Vector2f(1204.f, 883.f);
		const sf::Vector2f marketBottomRight = sf::Vector2f(1300.f, 883.f);
		const sf::Vector2f marketBottomMiddle = sf::Vector2f(400.f, 883.f);

		const sf::Vector2f marketLeftNav = sf::Vector2f(304.f, 883.f);
		const sf::Vector2f marketRightNav = sf::Vector2f(1204.f, 883.f);

		const sf::Vector2f shipBuyTopLeft = sf::Vector2f(20.f, 22.f);
		const sf::Vector2f shipBuyTopRightStart = sf::Vector2f(404.f, 22.f);
		const sf::Vector2f shipBuyMiddleLeftStart = sf::Vector2f(20.f, 121.f);
		const sf::Vector2f shipBuyMiddleRightStart = sf::Vector2f(404.f, 121.f);
	};
}
#pragma once

/// <summary>
/// This class handles all the menu related functions for the game.
/// It also contains every menu object and their respective functions.
/// </summary>

#include "UI/Menu/InGameHUD.h"
#include "UI/Menu/InventoryMenu.h"
#include "UI/Menu/OptionsMenu.h"
#include "UI/Menu/StartMenu.h"

namespace PirateGame {
	// Enum for the different types of menus
	enum class MenuType {
		StartMenu,
		OptionsMenu,
		HUD,
		InventoryMenu
	};

	class MenuHandler {
	public:
		MenuHandler(Context& context) : context(context) {};
		~MenuHandler() {};

		void createMenus(WindHandler& WH);
		void setUpMenus() const;
		void openMenu(MenuType menuType) const;

		StartMenu* getStartMenu() const { return startMenu.get(); }
		OptionsMenu* getOptionsMenu() const { return optionsMenu.get(); }
		InGameHUD* getHUD() const { return HUD.get(); }
		InventoryMenu* getInventoryMenu() const { return inventoryMenu.get(); }
		
	private:
		// Reference to the global context
		Context& context;

		// Map of menu types and game states to the menu objects
		std::unordered_map<MenuType, std::shared_ptr<Menu>> menus;

		// Pointers to the different menus
		std::shared_ptr<StartMenu> startMenu;
		std::shared_ptr<OptionsMenu> optionsMenu;
		std::shared_ptr<InGameHUD> HUD;
		std::shared_ptr<InventoryMenu> inventoryMenu;
		//...
	};
}

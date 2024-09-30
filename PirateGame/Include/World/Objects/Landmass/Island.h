#pragma once

/// Island class

#include <SFML/Graphics.hpp>
#include "World/Objects/Landmass/Landmass.h"

namespace PirateGame {
	class Island : public Landmass {
	public:
		Island(Context& context) : Landmass(context) {};

		void createLandMass() override;

		IslandMenu* getIslandMenu() const { return islandMenu.get(); }
		std::vector<ShopItem>& getMarket() { return market; }

		const sf::Image& getImage(Context& context) override { return Textures::landmassTextures.getIslandTextures().getImage(type); }
		LandMassType getType() override { return LandMassType::Island; }
	private:
		std::unique_ptr<IslandMenu> islandMenu;

		IslandType type = IslandType::Island1;

		std::vector<ShopItem> market;
	};
}
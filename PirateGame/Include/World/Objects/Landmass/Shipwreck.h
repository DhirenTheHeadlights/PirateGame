#pragma once

/// Shipwreck class

#include <SFML/Graphics.hpp>

#include "World/Objects/Landmass/Landmass.h"

namespace PirateGame {
	class Shipwreck : public Landmass {
	public:
		Shipwreck(Context& context) : Landmass(context) {};

		void createLandMass() override;

		std::vector<ShopItem>& getLoot() { return loot; }
		const sf::Image& getImage(Context& context) override { return Textures::landmassTextures.getShipwreckTextures().getImage(type); }
		LandMassType getType() override { return LandMassType::Shipwreck; }
	private:
		ShipwreckType type = ShipwreckType::Shipwreck1;

		std::vector<ShopItem> loot;
	};
}
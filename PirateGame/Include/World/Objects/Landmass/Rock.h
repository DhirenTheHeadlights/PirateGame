#pragma once

/// Rock class

#include <SFML/Graphics.hpp>

#include "World/Objects/Landmass/Landmass.h"

namespace PirateGame {
	class Rock : public Landmass {
	public:
		Rock(Context& context) : Landmass(context) {};

		void createLandMass() override;

		const sf::Image& getImage(Context& context) override { return Textures::landmassTextures.getRockTextures().getImage(type); }
		LandMassType getType() override { return LandMassType::Rock; }
	private:
		RockType type = RockType::Rock1;
	};
}
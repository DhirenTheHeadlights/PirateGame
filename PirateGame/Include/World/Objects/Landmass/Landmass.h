#pragma once

/// This class is used to represent the land masses in the game.
/// The types of land masses include: islands, rocks, and shipwrecks.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <variant>
#include <Lib/VectorMath.h>

#include "World/Architecture/Textures.h"
#include "World/Objects/General/ShopItem.h"
#include "UI/Menu/IslandMenu.h"
#include "World/Objects/Landmass/LandmassTypeGenerator.h"

namespace PirateGame {
	class Landmass {
	public:
		Landmass(Context& context) : context(context), id(context.gidm->generateID()) {}

		virtual void createLandMass() = 0;
		void setRandomRotation() { sprite.setRotation(vm::randomValue(0.f, 360.f)); }

		// Getters
		sf::Sprite& getSprite() { return sprite; }
		virtual const sf::Image& getImage(Context& context) = 0;
		virtual LandMassType getType() = 0;
		bool isActive() const { return active; }
		ID* getID() const { return id.get(); }

		// Setters
		void deactivate() { active = false; }

		// Draw the land mass
		void draw(sf::RenderWindow& window) const {
			window.draw(sprite); 
		}

	protected:
		// Global context
		Context& context;

		// Sprite to represent the land mass
		sf::Sprite sprite;

		// Active flag
		bool active = true;

		// ID
		std::shared_ptr<ID> id;

		// Type generator
		LandMassTypeGenerator<LandMassType> typeGenerator;

		static std::vector<ShopItem> createLootPool(int marketSize, int marketPrice, int marketItems);
	};
}
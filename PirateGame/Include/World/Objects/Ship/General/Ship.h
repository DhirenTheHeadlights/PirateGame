#pragma once

/// Ship class is used to represent the ships in the game.

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Globals/Context.h"
#include "World/Architecture/Textures.h"

#include "World/Objects/Ship/Handlers/General/ShipCannonHandler.h"
#include "World/Objects/Ship/Handlers/General/ShipMovementHandler.h"
#include "World/Objects/Ship/Handlers/General/ShipInputHandler.h"
#include "World/Objects/Ship/Handlers/General/ShipSailHandler.h"
#include "World/Objects/Ship/Handlers/General/ShipInventoryHandler.h"
#include "ShipEnums.h"
#include "World/Architecture/Region.h"

namespace PirateGame {
	class Ship {
	public:
		Ship(Context& context) : context(context), id(context.gidm->generateID()) {};

		// Create the ship and set its values. Random ship class if not specified.
		void setUpShip(const ShipClass shipClass = ShipClass::Random, const Region region = Region::SandyShores);
		virtual void customShipSetUp() = 0; // Virtual method to allow for custom ship setup
		void update(const sf::Vector2f& windDirection, float windSpeed);
		virtual void customShipUpdate() = 0; // Virtual method to allow for custom ship update
		void draw();
		virtual void customShipDraw() = 0; // Virtual method to allow for custom ship draw

		// Setters
		void damageShip(const float damagePerFrame) {
			health -= (health < 0.f) ? 0.f : damagePerFrame;
		}
		void changeShipClass(const ShipClass shipClass) {
			this->shipClass = shipClass;
			setUpShip(shipClass);
		}
		void setGroupId(ID* groupId) { this->groupID = groupId; }
		void setDead(const bool isDead) { this->isDead = isDead; }
		void setHealth(const float health) { this->health = health; }

		// Getters
		float getHealth() const { return health; }
		sf::Sprite& getSprite() { return sprite; }
		ID* getID() const { return id.get(); }
		ID* getGroupId() const { return groupID; }
		bool getIsDead() const { return isDead; }
		Region getBirthRegion() const { return birthRegion; }

		ShipProperties& getSpecificShipProperties() { return shipProperties; }
		ShipClass getShipClass() const { return shipClass; }

		virtual ShipCannonHandler* getCannonHandler() { return sch.get(); };
		virtual ShipSailHandler* getSailHandler() { return ssh.get(); };
		virtual ShipMovementHandler* getMovementHandler() { return smh.get();}
		virtual ShipInputHandler* getInputHandler() { return sih.get(); }
		virtual ShipInventoryHandler* getInventoryHandler() { return sIvH.get(); }

		std::string getShipClassString() const {
			switch (shipClass) {
			case ShipClass::Sloop:
				return "Sloop";
			case ShipClass::Brigantine:
				return "Brigantine";
			case ShipClass::Frigate:
				return "Frigate";
			case ShipClass::ManOWar:
				return "Man O' War";
			case ShipClass::Galleon:
				return "Galleon";
			default: ;
			}
			return "Error: Ship class not found.";
		}

	private:
		// Static map for ship configurations
		static std::unordered_map<ShipClass, ShipProperties> ShipConfig;

		// Helper methods
		void setHealthBarPosition();
		void regenerateHealth();

		// SFML Objects
		sf::Clock deltaTime;
		sf::Sprite sprite;

		// Variables to store the ship's values
		float health = 0;
		float scalingFactor = 4;
		bool isDead = false;

		sf::Vector2f constSpriteBounds;

		ShipClass shipClass = ShipClass::Sloop;
		ShipProperties shipProperties;
		Region birthRegion = Region::SandyShores;

		// Clock for regenerating health
		sf::Clock healthRegenClock;

		// Unique ID and group ID
		std::shared_ptr<ID> id;
		ID* groupID = nullptr;
	protected:
		// Context
		Context& context;

		// Rectangle shape for the health bar
		sf::RectangleShape healthBarGreen;
		sf::RectangleShape healthBarRed;

		// Handlers
		std::unique_ptr<ShipCannonHandler> sch;
		std::unique_ptr<ShipSailHandler> ssh;
		std::unique_ptr<ShipInputHandler> sih;
		std::unique_ptr<ShipInventoryHandler> sIvH;
		std::unique_ptr<ShipMovementHandler> smh;
	};
}

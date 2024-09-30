#pragma once

/// This class contains the methods for handling the input
/// for the ship. This includes shooting, etc.

#include <SFML/Graphics.hpp>

#include "Globals/SoundHandler.h"

#include "World/Objects/Ship/Handlers/General/ShipCannonHandler.h"
#include "World/Objects/Ship/Handlers/General/ShipMovementHandler.h"
#include "World/Objects/Ship/Handlers/General/ShipSailHandler.h"

namespace PirateGame {
	class ShipInputHandler {
	public:
		ShipInputHandler(JsonLoader* json, const sf::Sprite& sprite, SoundManager* GSM) : sprite(sprite), gsm(GSM), json(json) {}

		void update(const sf::Texture& cannonballTexture, IdManager* GIDM, sf::Vector2f windDirection, float windSpeed);
		virtual void handleCannonFire(const sf::Texture& cannonballTexture, IdManager* GIDM) = 0;
		virtual void handleCannonAim() = 0;
		virtual void handleAnchorDrop() = 0;
		virtual void handleSailChange(const sf::Vector2f& windDirection) = 0;

		// Setters
		void setBaseSpeed(float baseSpeed) { this->baseSpeed = baseSpeed; }
		void setCannonHandler(ShipCannonHandler* SCH) { this->sch = SCH; }
		void setMovementHandler(ShipMovementHandler* SMH) { this->smh = SMH; }
		void setSailHandler(ShipSailHandler* SSH) { this->ssh = SSH; }
		void setInAudioRange(bool inAudioRange) { this->inAudioRange = inAudioRange; }
		void setCooldown(sf::Time cooldown) { this->cooldown = cooldown; }

		// Getters
		ShipCannonHandler* getCannonHandler() const { return sch; }

	protected:
		SoundManager* gsm = nullptr;
		JsonLoader* json;

		const sf::Sprite& sprite;

		// Handlers
		ShipCannonHandler* sch = nullptr;
		ShipMovementHandler* smh = nullptr;
		ShipSailHandler* ssh = nullptr;

		// Ship properties
		float baseSpeed = 1.f;

		// Cooldown
		sf::Clock cannonCooldownClock;
		sf::Time cooldown =json->getGameData().gameConfig.shipData.cannonCooldown;
		bool inAudioRange = false;
	};
}

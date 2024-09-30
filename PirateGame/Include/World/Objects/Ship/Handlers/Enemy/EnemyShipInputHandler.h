#pragma once

/// This class contains the methods for handling the input for enemy ships.

#include <SFML/Graphics.hpp>

#include "Globals/SoundHandler.h"

#include "World/Handlers/WindHandler.h"

#include "World/Objects/Ship/Handlers/General/ShipInputHandler.h"

namespace PirateGame {
	class EnemyShipInputHandler : public ShipInputHandler {
	public:
		EnemyShipInputHandler(JsonLoader* json, sf::Sprite& sprite, SoundManager* GSM) : ShipInputHandler(json, sprite, GSM) {};
		~EnemyShipInputHandler() {};

		void handleCannonFire(const sf::Texture& cannonballTexture, IdManager* GIDM) override;
		void handleCannonAim() override;
		void handleAnchorDrop() override;
		void handleSailChange(const sf::Vector2f& windDirection) override;

		// Setters
		void setTargetPos(sf::Vector2f targetPos) { 
			this->targetPos = targetPos;
			sch->setTargetPos(targetPos);
		}
		void setFiringDistance(float firingDistance) { this->firingDistance = firingDistance; }
	private:


		sf::Vector2f targetPos;
		float firingDistance = 0.f;
	};
}

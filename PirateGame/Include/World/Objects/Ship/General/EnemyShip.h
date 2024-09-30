#pragma once

/// This class is almost identical to PlayerShip, but it is used for the enemy ships.

#include <SFML/Graphics.hpp>

#include "Globals/Context.h"
#include "World/Objects/Ship/General/Ship.h"
#include "World/Objects/Ship/Handlers/Enemy/EnemyShipInputHandler.h"
#include "World/Objects/Ship/Handlers/Enemy/EnemyShipMovementHandler.h"

namespace PirateGame {
	class EnemyShip : public Ship {
	public:
		EnemyShip(Context& context) : Ship(context) {}

		// Custom functions
		void customShipSetUp() override;
		void customShipUpdate() override;
		void customShipDraw() override;

		// Setters
		void setTargetPosition(sf::Vector2f targetPos) {
			// Perform a dynamic cast to check if SIH and SMH are enemy types
			if (const auto sihEnemy = dynamic_cast<EnemyShipInputHandler*>(sih.get())) {
				sihEnemy->setTargetPos(targetPos);
			}
			if (const auto smhEnemy = dynamic_cast<EnemyShipMovementHandler*>(smh.get())) {
				smhEnemy->setTargetPosition(targetPos);
			}
			this->targetPosition = targetPos;
		}

		void setDifficultyScaling(const float difficultyScaling) {
			getSpecificShipProperties().baseSpeed *= difficultyScaling;
			getSpecificShipProperties().maxHealth *= difficultyScaling;
			getSpecificShipProperties().regenRate *= difficultyScaling;
			setHealth(this->getSpecificShipProperties().maxHealth);
		}

		// Overridden getters
		EnemyShipInputHandler* getInputHandler() override { return dynamic_cast<EnemyShipInputHandler*>(sih.get()); }
		EnemyShipMovementHandler* getMovementHandler() override { return dynamic_cast<EnemyShipMovementHandler*>(smh.get()); }
	private:
		// Variables
		sf::Vector2f targetPosition;
		bool debug = false;
	};
}


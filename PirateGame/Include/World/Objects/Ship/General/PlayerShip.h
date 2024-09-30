#pragma once

/// This class is used to represent the player ship in the game.

#include <cmath>

#include "Globals/Context.h"

#include "Ship.h"
#include "World/Objects/Ship/Handlers/Player/PlayerShipInputHandler.h"
#include "World/Objects/Ship/Handlers/Player/PlayerShipMovementHandler.h"

namespace PirateGame {
	class PlayerShip : public Ship {
	public:
		PlayerShip(Context& context) : Ship(context) {};

		// Experience
		void addExperience(const float exp) {
			experience += exp;
		}
		float getExp() const { return experience; }
		float getExpToLevelUp() const { return experienceToLevelUp; }
		int getPlayerLevel() const { return playerLevel; }

		// Create the ship and set its values
		virtual void customShipSetUp() override;
		virtual void customShipUpdate() override;
		virtual void customShipDraw() override;

		// Overridden getters
		PlayerShipInputHandler* getInputHandler() override { return dynamic_cast<PlayerShipInputHandler*>(sih.get()); }
		PlayerShipMovementHandler* getMovementHandler() override { return dynamic_cast<PlayerShipMovementHandler*>(smh.get()); }
	private:
		// Experience
		float experience = context.jsl->getGameData().saveData.playerExperience;
		float experienceToLevelUp = context.jsl->getGameData().saveData.playerExperienceToLevelUp;
		int playerLevel = context.jsl->getGameData().saveData.playerLevel;
	};
}

#include "World/Objects/Ship/General/PlayerShip.h"

using namespace PirateGame;

/// Custom functions

void PlayerShip::customShipSetUp() {
	sih = std::make_unique<PlayerShipInputHandler>(context.jsl.get(), getSprite(), context.gsm.get());
	smh = std::make_unique<PlayerShipMovementHandler>(Globals::window, getSprite(), getSpecificShipProperties().baseSpeed, context.jsl.get());
	
	sIvH = std::make_unique<ShipInventoryHandler>();
	sIvH->addGold(context.jsl->getGameData().saveData.playerGold);
	sIvH->setInventory(context.jsl->getGameData().saveData.playerInventory);
	
	sih->setBaseSpeed(getSpecificShipProperties().baseSpeed);
	sih->setCannonHandler(getCannonHandler());
	sih->setMovementHandler(smh.get());
	sih->setSailHandler(getSailHandler());

	getInputHandler()->setInAudioRange(true);
}

void PlayerShip::customShipUpdate() {
	// If the experience is greater than the experience to level up
	// Level up the ship and also up the amount of exp to level up
	if (experience > experienceToLevelUp) {
		experience = 0.f;
		experienceToLevelUp *= 2;
		playerLevel += 1;
	}
}

void PlayerShip::customShipDraw() {
	// Draw the health bar
	sf::RenderWindow* window = Globals::window;
	
	getCannonHandler()->drawCannons(window);
	getSailHandler()->draw(window);
}
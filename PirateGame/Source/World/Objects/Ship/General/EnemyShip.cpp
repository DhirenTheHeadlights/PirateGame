#include "World/Objects/Ship/General/EnemyShip.h"


using namespace PirateGame;

void EnemyShip::customShipSetUp() {
	// Add handlers
	sih = std::make_unique<EnemyShipInputHandler>(context.jsl.get(), getSprite(), context.gsm.get());
	smh = std::make_unique<EnemyShipMovementHandler>(getSprite(), getSpecificShipProperties().baseSpeed, context.jsl.get());

	sih->setBaseSpeed(getSpecificShipProperties().baseSpeed);
	sih->setCannonHandler(getCannonHandler());
	sih->setMovementHandler(smh.get());
	sih->setSailHandler(getSailHandler());
}

void EnemyShip::customShipUpdate() {
}

void EnemyShip::customShipDraw() {
	// Draw the health bar
	sf::RenderWindow* window = Globals::window;
	window->draw(healthBarRed);
	window->draw(healthBarGreen);

	getCannonHandler()->drawCannons(window);
	getSailHandler()->draw(window);

	if (debug) {
		TextQueue::displayText("Health: " + std::to_string(getSpecificShipProperties().maxHealth), getSprite().getPosition() + sf::Vector2f(0, 50), sf::Color::White);
	}
}


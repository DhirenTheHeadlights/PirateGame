#include "World/Objects/Ship/General/Ship.h"
#include "Globals/Clock.h"

using namespace PirateGame;

// Create the ship
void Ship::setUpShip(const ShipClass level, const Region region) {
	// If the level is random, generate a random number between 1 and 5
	if (level == ShipClass::Random) {
		shipClass = getRandomShipClass();
	}
	else {
		shipClass = level;
	}

	// Set class
	shipProperties = getShipProperties(shipClass);
	health = shipProperties.maxHealth;
	birthRegion = region;

	// Load the texture
	const sf::Vector2f scaling(shipProperties.scaleX * scalingFactor, shipProperties.scaleY * scalingFactor);

	sprite.setTexture(Textures::shipTextures.getShipTextureManagerByRegion(birthRegion).getTexture(shipClass));
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setScale(scaling);

	// Set the constant sprite bounds
	constSpriteBounds = sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	// Load the cannon handler
	sch = std::make_unique<ShipCannonHandler>(context.jsl.get(), sprite);
	sch->initializeCannons(Textures::shipTextures.getCannonTextureManagerByRegion(birthRegion).getTexture(shipClass), 
						Textures::shipTextures.getShipTextureManagerByRegion(region).getImage(shipClass), 
						shipProperties.numCannons, id.get(), scaling);

	// Load the sail handler
	ssh = std::make_unique<ShipSailHandler>();
	ssh->loadSailPositions(Textures::shipTextures.getSailTextureManagerByRegion(birthRegion).getTextureGroup(shipClass), Textures::shipTextures.getShipTextureManagerByRegion(birthRegion).getImage(shipClass), scaling);

	// Execute custom ship setup
	customShipSetUp();
}

// Draw and update the ship
void Ship::update(const sf::Vector2f& windDirection, const float windSpeed) {
	setHealthBarPosition();
	regenerateHealth();

	// Update handlers
	sch->updateCannons(Globals::window, Clock::getDeltaTime());
	ssh->update(sprite, smh->getVelocity(), context.jsl->getGameData().gameConfig.shipData.maxSailRotationOffset);
	sih->update(Textures::landmassTextures.getMiscTextures().getTexture(MiscType::Cannonball), context.gidm.get(), windDirection, windSpeed);
	smh->update(ssh->getAverageSailDirection(), Clock::getDeltaTime(), windDirection, windSpeed);

	// 

	// Execute custom ship update
	customShipUpdate();
}

void Ship::draw() {
	Globals::window->draw(sprite);

	// Draw sails
	ssh->draw(Globals::window);

	// Custom ship draw
	customShipDraw();
}

// Regen Health
void Ship::regenerateHealth() {
	// Regen health
	if (healthRegenClock.getElapsedTime().asMilliseconds() > context.jsl->getGameData().gameConfig.shipData.shipHealthRegenTime.asMilliseconds()) {
		health += shipProperties.regenRate;
		healthRegenClock.restart();
	}
	// Restart the damage clock too
	if (deltaTime.getElapsedTime().asSeconds() > 1) {
		deltaTime.restart();
	}
	if (health > shipProperties.maxHealth) health = shipProperties.maxHealth;
}

// Draw the health bars
void Ship::setHealthBarPosition() {
	// Determine the size of the health bar green based on health
	healthBarGreen.setSize(sf::Vector2f(-context.jsl->getGameData().gameConfig.shipData.shipHealthBarSize.x * health / shipProperties.maxHealth, context.jsl->getGameData().gameConfig.shipData.shipHealthBarSize.y));
	healthBarGreen.setFillColor(sf::Color::Green);

	// Determine the size of the health bar red based on health
	healthBarRed.setSize(healthBarGreen.getSize());
	healthBarRed.setFillColor(sf::Color::Red);

	// Define the offset from the center of the ship to where the health bar should be
	const sf::Vector2f healthBarOffset(-1 * constSpriteBounds.x / 2, constSpriteBounds.y / 2);

	// Calculate the health bar's position based on the ship's rotation
	const sf::Vector2f offset(healthBarRed.getSize().x / 2, healthBarOffset.y + healthBarRed.getSize().y);
	const sf::Vector2f healthBarPosition = vm::relativeRotationTransformedPosition(sprite.getPosition(), offset, sprite.getRotation());

	// Set the position and rotation of the health bars
	healthBarGreen.setPosition(healthBarPosition);
	healthBarRed.setPosition(healthBarPosition );
	healthBarGreen.setRotation(sprite.getRotation());
	healthBarRed.setRotation(sprite.getRotation());
}

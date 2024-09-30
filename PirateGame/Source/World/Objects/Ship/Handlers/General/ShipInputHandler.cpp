#include "World/Objects/Ship/Handlers/General/ShipInputHandler.h"

using namespace PirateGame;

void ShipInputHandler::update(const sf::Texture& cannonballTexture, IdManager* GIDM, const sf::Vector2f windDirection, const float windSpeed) {
	handleCannonFire(cannonballTexture, GIDM);
	handleCannonAim();
	handleAnchorDrop();
	handleSailChange(windDirection);
}
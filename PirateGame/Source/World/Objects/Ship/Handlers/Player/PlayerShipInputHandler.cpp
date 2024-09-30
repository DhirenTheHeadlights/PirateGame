#include "World/Objects/Ship/Handlers/Player/PlayerShipInputHandler.h"

using namespace PirateGame;

void PlayerShipInputHandler::handleCannonFire(const sf::Texture& cannonballTexture, IdManager* gidm) {
	// Fire the cannons
	if (Input::isKeyPressedOnce(fireKey) && cannonCooldownClock.getElapsedTime().asSeconds() > cooldown.asSeconds()) {
		sch->shootCannonballs(cannonballTexture, gidm);
		cannonCooldownClock.restart();
		if (inAudioRange) gsm->playSound(SoundId::CannonShot);
	}
}

void PlayerShipInputHandler::handleCannonAim() {
	// Set the firing side of the ship
	if (Input::isMouseButtonPressedOnce(portMouseButton)) {
		sch->setFiringSide(FiringSide::Port);
	}
	if (Input::isMouseButtonPressedOnce(starboardMouseButton)) {
		sch->setFiringSide(FiringSide::Starboard);
	}

	// Rotate the cannons based on the mouse position if cannon mode is set to manual
	if (Input::isKeyToggled(manualAimKey)) {
		sch->setFiringState(FiringState::TowardsMouse);
		smh->setStopShipRotationFlag(true);
	}
	else {
		sch->setFiringState(FiringState::Untargeted);
		smh->setStopShipRotationFlag(false);
	}
}

void PlayerShipInputHandler::handleAnchorDrop() {
	if (Input::isKeyPressedOnce(anchorDropKey)) {
		smh->setAnchorDrop(!smh->getDroppedAnchor());
	}
}

void PlayerShipInputHandler::handleSailChange(const sf::Vector2f& windDirection) {
	if (Input::isKeyHeld(sailUpKey)) {
		ssh->moveSailsUp(sailUpKey);
	}
	if (Input::isKeyHeld(sailDownKey)) {
		ssh->moveSailsDown(sailDownKey);
	}
	if (Input::isKeyHeld(sailLeftKey)) {
		ssh->moveSailsLeft(sailLeftKey, json->getGameData().gameConfig.shipData.sailRotationSpeed);
	}
	if (Input::isKeyHeld(sailRightKey)) {
		ssh->moveSailsRight(sailRightKey, json->getGameData().gameConfig.shipData.sailRotationSpeed);
	}

	ssh->moveSailLeftRightAutomatically(windDirection, sprite.getRotation(), json->getGameData().gameConfig.shipData.sailRotationSpeed);
}
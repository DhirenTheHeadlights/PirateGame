#include "World/Objects/Ship/Handlers/Enemy/EnemyShipInputHandler.h"

using namespace PirateGame;

void EnemyShipInputHandler::handleCannonFire(const sf::Texture& cannonballTexture, IdManager* GIDM) {
	// Only fire if the player is within firingRange
	const float distance = vm::distance(sprite.getPosition(), targetPos);
	if (distance > firingDistance) {
		return;
	}

    // Check if the angle is within the allowed firing arc
    if (std::abs(sch->getFiringDirectionAngle()) <= sch->getMaxFiringAngle()			// Check if the player is within the firing arc
        && targetPos != sf::Vector2f(0, 0)											// Check if the target position is valid
        && cannonCooldownClock.getElapsedTime() > cooldown) {							// Check if the cooldown has expired

        sch->shootCannonballs(cannonballTexture, GIDM);
        cannonCooldownClock.restart();
        if (inAudioRange) gsm->playSound(SoundId::CannonShot);
    }
}

void EnemyShipInputHandler::handleCannonAim() {
    // Set the firing state to towards target
    sch->setFiringState(FiringState::TowardsTarget);

    // Calculate vector from enemy ship to player ship
    sf::Vector2f directionVector = targetPos - sprite.getPosition();

    // Calculate angle to horizontal in radians
    float angleInDegrees = vm::vectorToAngleDegrees(directionVector);

    // Get the enemy ship's current rotation and adjust it to the same 0-360 degree range
    float shipRotation = vm::normalizeAngle(fmod(sprite.getRotation(), 360.f));

    // Adjust the calculated angle by subtracting the enemy ship's rotation
    float adjustedAngle = angleInDegrees - shipRotation;

    // Use fmod to normalize the adjusted angle to the range [-360, 360)
    adjustedAngle = fmod(adjustedAngle, 360.f);
    adjustedAngle = vm::normalizeAngle(adjustedAngle); // Normalize to [0, 360)

    // Determine side based on the adjusted angle
    if (adjustedAngle > 90.f && adjustedAngle < 270.f) getCannonHandler()->setFiringSide(FiringSide::Port);
    else getCannonHandler()->setFiringSide(FiringSide::Starboard);
}


void EnemyShipInputHandler::handleAnchorDrop() {
	//...
}

void EnemyShipInputHandler::handleSailChange(const sf::Vector2f& windDirection) {
    ssh->moveSailLeftRightAutomatically(windDirection, sprite.getRotation(), json->getGameData().gameConfig.shipData.sailRotationSpeed);
}
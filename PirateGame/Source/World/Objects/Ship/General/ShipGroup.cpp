#include "World/Objects/Ship/General/ShipGroup.h"

using namespace PirateGame;

void ShipGroup::updateGroup(Quadtree<EnemyShip>* shipQuadtree, const sf::Vector2f& windDirection, const float windSpeed) {
	for (size_t i = 0; i < ships.size(); i++) {
		ships[i]->update(windDirection, windSpeed);
		shipQuadtree->updateObjectPosition(ships[i].get());

		// Calculate the alignment, cohesion, and separation vectors and add them to the destination
		sf::Vector2f resultantVector = vm::normalize(calculateAlignment(ships[i]) + calculateCohesion(ships[i]) + calculateSeparation(ships[i]) + calculateGoalVector(ships[i]));

		// If the ship is in combat, set the target position to be the closest enemy ship
		Ship* targetShip = getClosestEnemyShip(ships[i]);
		if (inCombat && targetShip != nullptr) {
			ships[i]->setTargetPosition(targetShip->getSprite().getPosition());
			ships[i]->getMovementHandler()->setActiveTowardsTarget(true);
			ships[i]->getSpecificShipProperties().baseSpeed = combatSpeedMultiplier * groupSpeed;
		}
		else {
			ships[i]->getMovementHandler()->setActiveTowardsTarget(false);
			ships[i]->getSpecificShipProperties().baseSpeed = groupSpeed;
		}

		// If the health of the ship is almost 0, remove the ship from the group
		if (ships[i]->getHealth() < 0.001f) {
			ships[i]->setDead(true);
			removeShip(ships[i], shipQuadtree);
		}

		// If any ships in the target ships vector is null or has health less than 0.001f, remove them from the vector
		std::erase_if(targetShips, [](Ship* targetShip) { return targetShip == nullptr || targetShip->getHealth() < 0.001f; });
	}
}

void ShipGroup::drawGroup(bool debug) const {
	for (auto& ship : ships) {
		ship->draw();

		/// For debugging purposes
		if (!debug) continue;

		// Check if the shipgroup is near the view, if so, display the shipgroup information
		if (!(vm::distance(ship->getSprite().getPosition(), Globals::window->getView().getCenter()) < 2000.f)) continue;

		sf::Vector2f pos = sf::Vector2f(ship->getSprite().getPosition().x + 150.f, ship->getSprite().getPosition().y);
		TextQueue::displayText("GID: " + std::to_string(ID->id) + " SID: " + std::to_string(ship->getID()->id), pos, sf::Color::White, 10);
		TextQueue::displayText("Ship group size: " + std::to_string(ships.size()), pos + sf::Vector2f(0, static_cast<float>(TextQueue::textSize)), sf::Color::White, 10);
		TextQueue::displayText("Heading: " + std::to_string(heading.x) + ", " + std::to_string(heading.y), pos + sf::Vector2f(0, 2 * static_cast<float>(TextQueue::textSize)), sf::Color::White, 10);
		TextQueue::displayText("Num of target ships: " + std::to_string(targetShips.size()), pos + sf::Vector2f(0, 3 * static_cast<float>(TextQueue::textSize)), sf::Color::White, 10);
		std::string targetShipIDs = "Target ship IDs: ";
		for (auto& targetShip : targetShips) {
			targetShipIDs += std::to_string(targetShip->getID()->id) + ", ";
		}
		TextQueue::displayText(targetShipIDs, pos + sf::Vector2f(0, 4 * static_cast<float>(TextQueue::textSize)), sf::Color::White, 10);
		std::string groupIDsInteractedWithStr = "Group IDs interacted with: ";
		for (auto& groupID : groupIDsInteractedWith) {
			groupIDsInteractedWithStr += std::to_string(groupID->id) + ", ";
		}
		TextQueue::displayText(groupIDsInteractedWithStr, pos + sf::Vector2f(0, 5 * static_cast<float>(TextQueue::textSize)), sf::Color::White, 10);
	}
}

Ship* ShipGroup::getClosestEnemyShip(std::shared_ptr<EnemyShip> ship) {
	Ship* closestShip = nullptr;
	float closestDistance = std::numeric_limits<float>::max();

	for (auto& ship : targetShips) {
		float distance = vm::distance(ship->getSprite().getPosition(), ship->getSprite().getPosition());
		if (distance < closestDistance) {
			closestDistance = distance; // Update the closest distance
			closestShip = ship;
		}
		// Check if any of the group ships are erroniously in the target ships vector. Compare the IDs
		// as there is a shared pointer in the group ships vector and a raw pointer in the target ships vector
		if (std::find_if(ships.begin(), ships.end(), [ship](const std::shared_ptr<Ship>& groupShip) { return groupShip->getID() == ship->getID(); }) != ships.end()) {
			std::cout << "Error: Ship [" << ship->getID() << "] is in the target ships vector but is also in the group ships vector! Removing from target ships vector. Wtf are you doing, change the code you idiot." << std::endl;
			targetShips.erase(std::remove(targetShips.begin(), targetShips.end(), ship), targetShips.end());
		}
	}
	return closestShip;
}

sf::Vector2f ShipGroup::calculateAlignment(const std::shared_ptr<EnemyShip>& ship) {
	sf::Vector2f alignment = sf::Vector2f(0, 0);
	int count = 0;

	for (auto& otherShip : ships) {
		if (ship != otherShip) {
			float distance = vm::distance(ship->getSprite().getPosition(), otherShip->getSprite().getPosition());
			if (distance < minDistance) {
				alignment += otherShip->getMovementHandler()->getVelocity();
				count++;
			}
		}
	}

	if (count > 0) {
		alignment /= static_cast<float>(count);
		alignment = vm::normalize(alignment);
		alignment *= alignmentWeight;
	}

	return alignment;
}

sf::Vector2f ShipGroup::calculateCohesion(const std::shared_ptr<EnemyShip>& ship) {
	sf::Vector2f cohesion = sf::Vector2f(0, 0);
	int count = 0;

	for (auto& otherShip : ships) {
		if (ship != otherShip) {
			float distance = vm::distance(ship->getSprite().getPosition(), otherShip->getSprite().getPosition());
			if (distance < minDistance) {
				cohesion += otherShip->getSprite().getPosition();
				count++;
			}
		}
	}

	if (count > 0) {
		cohesion /= static_cast<float>(count);
		cohesion -= ship->getSprite().getPosition();
		cohesion = vm::normalize(cohesion);
		cohesion *= cohesionWeight;
	}

	return cohesion;
}

sf::Vector2f ShipGroup::calculateSeparation(const std::shared_ptr<EnemyShip>& ship) {
	sf::Vector2f separation = sf::Vector2f(0, 0);
	int count = 0;

	for (auto& otherShip : ships) {
		if (ship != otherShip) {
			float distance = vm::distance(ship->getSprite().getPosition(), otherShip->getSprite().getPosition());
			if (distance < 100) {
				separation += otherShip->getSprite().getPosition() - ship->getSprite().getPosition();
				count++;
			}
		}
	}

	if (count > 0) {
		separation /= static_cast<float>(count);
		separation = vm::normalize(separation);
		separation *= separationWeight;
	}

	return separation;
}

sf::Vector2f ShipGroup::calculateGoalVector(const std::shared_ptr<EnemyShip>& ship) const {
	// Calculate the goal vector from the average position of all the ships
	// and the position of the heading
	sf::Vector2f goalVector = destination - ship->getSprite().getPosition();
	goalVector = vm::normalize(goalVector);
	goalVector *= goalWeight;

	return goalVector;
}

#pragma once

/// ShipGroup class is used to represent the group of ships in the game.

#include <SFML/Graphics.hpp>

#include "World/Architecture/QuadtreeTemplate.h"

#include "World/Objects/Ship/General/EnemyShip.h"

namespace PirateGame {
	class ShipGroup {
	public:
		ShipGroup(Context& context) : context(context), ID(context.gidm->generateID()) {}

		void updateGroup(Quadtree<EnemyShip>* shipQuadtree, const sf::Vector2f& windDirection, float windSpeed);
		void drawGroup(bool debug = false) const;

		void addShip(const std::shared_ptr<EnemyShip>& ship, Quadtree<EnemyShip>* shipQuadtree) {
			// If this is the first ship or if the ship has a lower speed than the group speed, set the group speed to the ship's speed
			if (ships.empty() || ship->getSpecificShipProperties().baseSpeed < groupSpeed) {
				groupSpeed = ship->getSpecificShipProperties().baseSpeed * ship->getMovementHandler()->getEnemySpeedMultiplier();
			}

			ship->getSpecificShipProperties().baseSpeed = groupSpeed;
			ship->setGroupId(ID.get());
			ship->getMovementHandler()->setDestination(destination);

			// Add the ship to the hashmap
			shipQuadtree->addObject(ship.get());


			if (std::ranges::find(targetShips, ship.get()) == targetShips.end()) {
				ships.push_back(ship);
			}
			
			//std::cout << "Ship added to group. Group size: " << ships.size() << std::endl;
		}

		void removeShip(const std::shared_ptr<EnemyShip>& ship, Quadtree<EnemyShip>* shipQuadtree) {
			// Remove the ship from the hashmap
			shipQuadtree->removeObject(ship.get());

			// Check if the ship was the slowest ship in the group
			if (ship->getSpecificShipProperties().baseSpeed == groupSpeed) {
				// If it was, find the next slowest ship and set the group speed to that ship's speed
				float newGroupSpeed = 0.f;
				for (const auto& otherShip : ships) {
					if (otherShip->getSpecificShipProperties().baseSpeed < newGroupSpeed) {
						newGroupSpeed = otherShip->getSpecificShipProperties().baseSpeed * otherShip->getMovementHandler()->getEnemySpeedMultiplier();
					}
				}
				groupSpeed = newGroupSpeed;
			}

			// Remove the ship from the vector
			std::erase(ships, ship);
		}

		// Setters
		void setDestination(sf::Vector2f heading) { 
			destination = heading; 
			for (const auto& ship : ships) {
				ship->getMovementHandler()->setDestination(heading);
			}
		}
		void addTarget(Ship* ship) { 
			if (std::ranges::find(targetShips, ship) != targetShips.end()) {
				return;
			}
			targetShips.push_back(ship); 
		}
		void clearEnemyShips() { ships.clear(); }
		void setTargetVelocity(sf::Vector2f targetVelocity) { this->targetVelocity = targetVelocity; }
		void setInCombat(bool inCombat) { this->inCombat = inCombat; }
		void setIsInteracting(bool isInteracting) { this->isInteracting = isInteracting; }
		void addGroupIDInteractedWithRecently(ID* groupID) { groupIDsInteractedWith.push_back(groupID); }
		void removeGroupIDInteractedWith(ID* groupID) {
			std::erase(groupIDsInteractedWith, groupID);
		}

		// Getters
		std::vector<std::shared_ptr<EnemyShip>>& getEnemyShips() { return ships; }
		std::vector<Ship*> getTargetShips() { return targetShips; }

		ID* getID() const { return ID.get(); }
		bool getInCombat() const { return inCombat; }
		bool getIsInteracting() const { return isInteracting; }
		bool isGroupIDInteractedWithRecently(ID* groupId) {
			if (std::ranges::find(groupIDsInteractedWith, groupId) != groupIDsInteractedWith.end()) {
				return true;
			}
			return false;
		}

		sf::Vector2f getAveragePosition() const {
			auto averagePosition = sf::Vector2f(0, 0);
			for (auto& ship : ships) {
				averagePosition += ship->getSprite().getPosition();
			}
			averagePosition /= static_cast<float>(ships.size());
			return averagePosition;
		}
		sf::Vector2f getHeading() const { return destination; }
		std::vector<ID*> getGroupIDsInteractedWith() { return groupIDsInteractedWith; }

	private:
		// Context
		Context& context;

		/// Functions
		// 3 main methods for flocking behavior
		sf::Vector2f calculateAlignment(const std::shared_ptr<EnemyShip>& ship);
		sf::Vector2f calculateCohesion(const std::shared_ptr<EnemyShip>& ship);
		sf::Vector2f calculateSeparation(const std::shared_ptr<EnemyShip>& ship);
		sf::Vector2f calculateGoalVector(const std::shared_ptr<EnemyShip>& ship) const;

		// Combat methods
		Ship* getClosestEnemyShip(std::shared_ptr<EnemyShip> ship);

		// Variables
		float alignmentWeight = context.jsl->getGameData().gameConfig.shipGroupData.shipGroupAlignmentWeight;
		float cohesionWeight = context.jsl->getGameData().gameConfig.shipGroupData.shipGroupCohesionWeight;
		float separationWeight = context.jsl->getGameData().gameConfig.shipGroupData.shipGroupSeparationWeight;
		float goalWeight = 1.f;

		float minDistance = 100.f;
		float groupSpeed = 0.f;
		float combatSpeedMultiplier = context.jsl->getGameData().gameConfig.shipGroupData.shipGroupCombatSpeedMultiplier;

		bool inCombat = false;
		bool isInteracting = false;

		sf::Vector2f destination; // The destination of the ship group
		sf::Vector2f heading; // The heading of the ship group
		sf::Vector2f targetVelocity; // For combat purposes
		std::vector<Ship*> targetShips; // For combat purposes

		// Game objects
		std::vector<std::shared_ptr<EnemyShip>> ships;
		std::vector<ID*> groupIDsInteractedWith;

		// Unique ID
		std::shared_ptr<ID> ID;
	};
}
#pragma once

#include "World/Architecture/QuadtreeTemplate.h"
#include "World/Handlers/ChunkHandler.h"
#include "World/Objects/Landmass/Island.h"
#include "World/Objects/Landmass/Rock.h"
#include "World/Objects/Landmass/Shipwreck.h"
#include "World/Objects/Ship/General/Cannonball.h"
#include "World/Objects/Ship/General/EnemyShip.h"

namespace PirateGame::QuadtreeHandler {
	// Hashmaps
	inline std::unique_ptr<Quadtree<Landmass>> landmassQuadtree;
	inline std::unique_ptr<Quadtree<Island>> islandQuadtree;
	inline std::unique_ptr<Quadtree<Rock>> rockQuadtree;
	inline std::unique_ptr<Quadtree<Shipwreck>> shipwreckQuadtree;
	inline std::unique_ptr<Quadtree<EnemyShip>> enemyShipQuadtree;
	inline std::unique_ptr<Quadtree<Cannonball>> cannonballQuadtree;

	// Objects
	inline std::vector<std::shared_ptr<Landmass>> landmasses;
	inline std::vector<std::shared_ptr<EnemyShip>> ships;

	inline void updateQuadtrees(const sf::FloatRect updatedBounds) {
		landmassQuadtree->update(updatedBounds);
		enemyShipQuadtree->update(updatedBounds);
		cannonballQuadtree->update(updatedBounds);
	}

	inline void setUpQuadtrees() {
		landmassQuadtree = std::make_unique<Quadtree<Landmass>>(ChunkHandler::getMapBounds());
		islandQuadtree = std::make_unique<Quadtree<Island>>(ChunkHandler::getMapBounds());
		rockQuadtree = std::make_unique<Quadtree<Rock>>(ChunkHandler::getMapBounds());
		shipwreckQuadtree = std::make_unique<Quadtree<Shipwreck>>(ChunkHandler::getMapBounds());
		enemyShipQuadtree = std::make_unique<Quadtree<EnemyShip>>(ChunkHandler::getMapBounds());
		cannonballQuadtree = std::make_unique<Quadtree<Cannonball>>(ChunkHandler::getMapBounds());
	}

	// Setters
	inline void setLandmasses(const std::vector<std::shared_ptr<Landmass>>& newLandmasses) { landmasses = newLandmasses; }
	inline void setShips(const std::vector<std::shared_ptr<EnemyShip>>& newShips) { ships = newShips; }
}
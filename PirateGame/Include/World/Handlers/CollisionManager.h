#pragma once

/// This class handles all the collision detection in the game.

#include <SFML/Graphics.hpp>

#include "Globals/Context.h"
#include "World/Handlers/QuadtreeHandler.h"

#include "World/Objects/Ship/General/EnemyShip.h"
#include "World/Objects/Ship/General/PlayerShip.h"
#include "World/Objects/Landmass/Landmass.h"

namespace PirateGame {
	class CollisionManager {
	public:
		CollisionManager(Context& context) : context(context) {}

		void handleCollisions();

		// Setters
		void setLandMasses(const std::vector<std::shared_ptr<Landmass>>& landMasses) { this->landmasses = landMasses; }
		void setEnemyShips(const std::vector<std::shared_ptr<EnemyShip>>& enemyShips) {this->ships = enemyShips; }
		void setPlayerShip(PlayerShip* playerShip) { this->playerShip = playerShip; }
	
	private:
		// Context
		Context& context;

		std::vector<std::shared_ptr<Landmass>> landmasses;
		std::vector<std::shared_ptr<EnemyShip>> ships;
		PlayerShip* playerShip = nullptr;

		// Values
		float collisionDamagePerFrame = 10.f;
		float killExp = 10.f;

		bool addedExp = false;

		float nearbyDistanceLandmass = 5000.f;
		float nearbyDistanceShip = 2000.f;
		float nearbyDistanceCannonball = 500.f;

		// Helper functions
		bool pixelPerfectTest(Ship* ship, Landmass* landmass, unsigned alphaLimit = 5) const;
		static bool shipCollisionTest(Ship* ship1, Ship* ship2);

		std::vector<sf::Sprite> handleShipCollisions( Ship* ship);
		void handleLandMassCollision(Ship* ship, Landmass* landmass, std::vector<Landmass*>& collidingLandMasses) const;
		void handleShipCollision(Ship* ship1, Ship* ship2, std::vector<Ship*>& collidingShips) const;
		void handleCannonballCollision(Ship* ship, Cannonball* cannonball, std::vector<Cannonball*>& collidingCannonballs);
		static void handleCannonballCollision(Cannonball* c1, Cannonball* c2);
	};
}
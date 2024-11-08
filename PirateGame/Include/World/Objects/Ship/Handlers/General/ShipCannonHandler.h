#pragma	once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

#include "World/Objects/Ship/General/ShipCannon.h"
#include "World/Objects/Ship/General/Cannonball.h"

namespace PirateGame {
	class ShipCannonHandler {
	public:
		ShipCannonHandler(JsonLoader* jsl, sf::Sprite& shipSprite) : shipSprite(shipSprite), jsl(jsl) {}

		void initializeCannons(const sf::Texture& cannonTexture, const sf::Image& shipImage, int numCannons, ID* ID, sf::Vector2f scale);
		void shootCannonballs(const sf::Texture& cannonballTexture, IdManager* GIDM);
		void updateCannons(sf::RenderWindow* window, sf::Time elapsed);
		void drawCannons(sf::RenderWindow* window);

		// Setters
		void setFiringSide(FiringSide side) { this->side = side; };
		void setFiringState(FiringState FS) {
			for (auto& cannon : cannons) {
				cannon.setFiringState(FS);
			}
		};
		void setCannonballQuadtree(Quadtree<Cannonball>* cannonballHashmap) {
			for (auto& cannon : cannons) {
				cannon.setCannonballHashmap(cannonballHashmap);
			}
		};
		void setTargetPos(sf::Vector2f targetPos) {
			for (auto& cannon : cannons) {
				cannon.setTargetPos(targetPos);
			}
		};

		// Getters
		bool getAimTowardsMouse() const { return aimTowardsTarget; };
		FiringSide getFiringSide() const { return side; };
		float getFiringDirectionAngle() const {
			// Average the firing angles of all the cannons on the firing side
			float firingAngle = 0.f;
			for (auto& cannon : cannons) {
				if (cannon.getFiringSide() == side) {
					firingAngle += cannon.getFiringDirectionAngle();
				}
			}
			return firingAngle / cannons.size() / 2.f; // Divide by 2 for only one side
		}
		float getMaxFiringAngle() const { return maxFiringAngle; }
	private:
		JsonLoader* jsl;

		sf::Vector2f cannonballDirection;
		std::vector<ShipCannon> cannons;
		
		const float maxFiringAngle = jsl->getGameData().gameConfig.shipData.maxFiringAngle;

		bool aimTowardsTarget = false;

		sf::Sprite& shipSprite;
		FiringSide side = FiringSide::Port;
	};
};

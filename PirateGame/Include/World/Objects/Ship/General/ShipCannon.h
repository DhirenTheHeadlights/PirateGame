#pragma once
#include <SFML/Graphics.hpp>

#include "World/Architecture/QuadtreeTemplate.h"
#include "Globals/JsonLoader.h"
#include "Cannonball.h"
#include "ShipEnums.h"


namespace PirateGame {
	// Enum for firing state
	enum class FiringState {
		TowardsTarget,
		TowardsMouse,
		Untargeted
	};

	class ShipCannon {
	public:
		ShipCannon(JsonLoader* jsl, const sf::Texture& texture, ID* id, const FiringSide FS, const sf::Vector2f scale) : jsl(jsl), cannonSprite(texture), side(FS), id(id) {
			cannonSprite.setScale(scale);

			if (FS == FiringSide::Port) {
				defaultRotation = 180.f;
				// The origin is not perfectly in the center of the cannon
				// so we need to adjust it slightly (the cannon sprite has
				// an even number of pixels in width and height)
				cannonSprite.setOrigin(7.f, 7.f); 
			}
			else {
				defaultRotation = 0.f;
				cannonSprite.setOrigin(5.f, 5.f);
			}
		};
		~ShipCannon() {}

		void fireCannon(FiringSide FS, const sf::Sprite& shipSprite, const sf::Texture& cannonballTexture, IdManager* GIDM);
		void drawCannonBalls(sf::RenderWindow* window) const;
		void updateCannon(const sf::Sprite& shipSprite, FiringSide FS, const sf::RenderWindow* window, sf::Time elapsed);

		// Setters
		void setCannonballHashmap(Quadtree<Cannonball>* cannonballHashmap) { this->cannonballHashmap = cannonballHashmap; }
		void setOffset(const sf::Vector2f offset) { this->offset = offset; }
		void setFiringState(const FiringState FS) { this->state = FS; }
		void setTargetPos(const sf::Vector2f targetPos) { this->targetPos = targetPos; }
	
		// Getters
		sf::Sprite& getSprite() { return cannonSprite; }
		sf::Vector2f getOffset() const { return offset; }
		float getFiringDirectionAngle() const { return firingDirectionAngle; }
		FiringSide getFiringSide() const { return side; }
	private:
		JsonLoader* jsl;

		// Helpers
		sf::Vector2f calculateDirectionToTarget(const sf::Sprite& shipSprite, sf::Vector2f targetPos) const;
		sf::Vector2f calculatePerpendicularDirection(float rotation) const;
		void rotateTowards(float angle, float step);
		void updateCannonRotation(const sf::Sprite& shipSprite, FiringSide FS, const sf::RenderWindow* window);
		void updateCannonballs(sf::Time elapsed);

		sf::Clock resetRotationClock;

		sf::Sprite cannonSprite;
		std::vector<Cannonball*> cannonballs;
		sf::Vector2f offset;
		sf::Vector2f targetPos;
		sf::Vector2f fireDirection;

		const float approxCannonOffsetToEdgeRatio = 0.85f;
		float defaultRotation = 0.f;
		float firingDirectionAngle = 0.f;
		float aimRotation = 0.f;

		FiringSide side = FiringSide::Starboard;
		FiringState state = FiringState::Untargeted;

		Quadtree<Cannonball>* cannonballHashmap = nullptr;

		ID* id;
	};
}
	
#pragma once

/// Derived player movement handler class

#include "World/Objects/Ship/Handlers/General/ShipMovementHandler.h"

namespace PirateGame {
	class PlayerShipMovementHandler : public ShipMovementHandler {
	public:
		PlayerShipMovementHandler(sf::RenderWindow* window, sf::Sprite& sprite, float& baseSpeed, JsonLoader* json ) : ShipMovementHandler(sprite, baseSpeed, json), window(window) {};
		~PlayerShipMovementHandler() {};

		// Movement functions
		void update(const sf::Vector2f& sailDirection, const sf::Time& dt, const sf::Vector2f& windDirection, const float windSpeed) override;

	private:
		void setSpriteRotation() override;

		sf::RenderWindow* window;
	};
}


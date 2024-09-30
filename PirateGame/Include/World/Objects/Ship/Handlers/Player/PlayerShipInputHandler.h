#pragma once

/// Child class of ShipInputHandler. This class if for player ship input handling.

#include <SFML/Graphics.hpp>

#include "World/Handlers/WindHandler.h"
#include "World/Objects/Ship/Handlers/General/ShipInputHandler.h"

namespace PirateGame {
	class PlayerShipInputHandler : public ShipInputHandler {
	public:
		PlayerShipInputHandler(JsonLoader* json, const sf::Sprite& sprite, SoundManager* gsm) : ShipInputHandler(json, sprite, gsm) {}
		~PlayerShipInputHandler() {};

		void handleCannonFire(const sf::Texture& cannonballTexture, IdManager* gidm) override;
		void handleCannonAim() override;
		void handleAnchorDrop() override;
		void handleSailChange(const sf::Vector2f& windDirection) override;

		sf::Keyboard::Key getFireKey() const { return fireKey; }
		sf::Keyboard::Key getManualAimKey() const { return manualAimKey; }
		sf::Mouse::Button getPortMouseButton() const { return portMouseButton; }
		sf::Mouse::Button getStarboardMouseButton() const { return starboardMouseButton; }
		sf::Keyboard::Key getAnchorDropKey() const { return anchorDropKey; }

	private:

		// Keys
		sf::Keyboard::Key fireKey = sf::Keyboard::Space;
		sf::Keyboard::Key manualAimKey = sf::Keyboard::E;

		sf::Mouse::Button portMouseButton = sf::Mouse::Left;
		sf::Mouse::Button starboardMouseButton = sf::Mouse::Right;

		sf::Keyboard::Key anchorDropKey = sf::Keyboard::Tab;

		sf::Keyboard::Key sailUpKey = sf::Keyboard::I;
		sf::Keyboard::Key sailDownKey = sf::Keyboard::K;
		sf::Keyboard::Key sailLeftKey = sf::Keyboard::A;
		sf::Keyboard::Key sailRightKey = sf::Keyboard::D;
	};
}

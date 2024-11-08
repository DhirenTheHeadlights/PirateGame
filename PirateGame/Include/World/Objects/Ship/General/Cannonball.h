#pragma once
#include <SFML/Graphics.hpp>

#include "World/Handlers/IdManager.h"

namespace PirateGame {
	struct Cannonball {
		Cannonball(IdManager* GIDM, ID* shipID, const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& normalizedVelocity, const float speed, const sf::Vector2f& scale) :
			shipID(shipID), id(GIDM->generateID().get()), sprite(texture), velocity(normalizedVelocity), speed(speed) {
			sprite.setPosition(position);
			sprite.setScale(scale);
		}

		bool operator==(const Cannonball& other) const {
			return this->id == other.id;
		}



		sf::Clock clock;

		sf::Vector2f velocity;
		sf::Sprite sprite;

		float speed = 0;

		ID* shipID;
		ID* id;

		bool isActive = true;
	};
};

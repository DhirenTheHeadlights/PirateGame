#pragma once

///  This class is the base class for all interactable objects in the game.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

#include "Globals/Input.h"
#include "Globals/SoundHandler.h"

namespace PirateGame {
	class Interactable {
	public:
		void createInteractable(sf::Texture& texture, sf::Text& title, sf::Vector2f scale = { 1.f, 1.f });
		virtual void customInteractableSetUp() {};
		virtual void interact(sf::RenderWindow* window, SoundManager* GSM) {}
		virtual void draw(sf::RenderWindow* window);

		// Setters
		virtual void setPosition(sf::Vector2f pos);
		void setTextPosition(const sf::Vector2f pos) { text.setPosition(pos); }
		void setSoundId(const SoundId id) { soundId = id; }

		// Getters
		sf::Text& getText() { return text; }
		sf::Sprite& getSprite() { return sprite; }

	protected:
		// Objects
		sf::Sprite sprite;
		sf::Text text;

		SoundId soundId = SoundId::Select;
	};
}


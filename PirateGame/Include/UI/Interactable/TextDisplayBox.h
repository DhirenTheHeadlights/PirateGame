#pragma once
#include <SFML/Graphics.hpp>

#include "UI/Interactable/Interactable.h"

// This class creates an interactable for a menu to display text only

namespace PirateGame {
	class TextDisplayBox : public Interactable {
	public:
		TextDisplayBox() {};

		// Have to define but it doesn't do anything
		void interact(sf::RenderWindow* window, SoundManager* GSM) override {};
		void customInteractableSetUp() override {};
	};
} 


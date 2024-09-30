#pragma once

/// Interactable textures for the game.

#include "Globals/TextureHandler.h"

namespace PirateGame {
	class InteractableTextureHandler : public TextureHandler {
	public:
		InteractableTextureHandler() {
			blackGrayButton.loadFromFile(RESOURCES_PATH "Sprites/Menu/Interactables/Interactable_basic_gray_black.png");
			sliderThumb.loadFromFile(RESOURCES_PATH "Sprites/Menu/Interactables/slider_thumb.png");
			sliderTrack.loadFromFile(RESOURCES_PATH "Sprites/Menu/Interactables/slider_track.png");
			scrollBarThumb.loadFromFile(RESOURCES_PATH "Sprites/Menu/Interactables/scroll_bar_thumb.png");
			scrollBarTrack.loadFromFile(RESOURCES_PATH "Sprites/Menu/Interactables/scroll_bar_track_extendable.png");
		}

		// Getters
		sf::Texture& getBlackGrayButton() { return blackGrayButton; }
		sf::Texture& getSliderThumb() { return sliderThumb; }
		sf::Texture& getSliderTrack() { return sliderTrack; }
		sf::Texture& getScrollBarThumb() { return scrollBarThumb; }
		sf::Texture& getScrollBarTrack() { return scrollBarTrack; }

	private:
		sf::Texture blackGrayButton;
		sf::Texture sliderThumb;
		sf::Texture sliderTrack;
		sf::Texture scrollBarThumb;
		sf::Texture scrollBarTrack;
	};
}
#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>

namespace PirateGame::Clock {
	inline sf::Clock clock;
	inline sf::Time dt;

	inline sf::Clock autosaveClock;

	inline int frameRate = 0;
	inline int frameCount = 0;
	inline int numFramesToAverage = 40;
	inline sf::Time frameRateUpdateTime = sf::Time::Zero;

	// Call this at the beginning of each frame
	inline void update() {
		dt = clock.restart();

		// Calculate the frame rate
		if (frameCount >= numFramesToAverage) {
			frameRate = frameCount / frameRateUpdateTime.asSeconds();
			frameRateUpdateTime = sf::Time::Zero;
			frameCount = 0;
		}

		++frameCount;
		frameRateUpdateTime += dt;
	}

	// Get the same delta time for all classes
	inline sf::Time getDeltaTime() {
		return std::min(sf::seconds(0.16f), dt);
	}

	inline bool getAutosaveTrigger() {
		if (autosaveClock.getElapsedTime().asSeconds() > 15.f) {
			autosaveClock.restart();
			return true;
		}
		return false;
	}

	inline int getFrameRate() {
		return frameRate;
	}
}

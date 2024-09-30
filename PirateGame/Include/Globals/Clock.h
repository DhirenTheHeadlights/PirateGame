#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>

namespace PirateGame {
	namespace Clock {
		inline sf::Clock clock;
		inline sf::Time dt;

		inline sf::Clock autosaveClock;

		// Call this at the beginning of each frame
		inline void update() {
			dt = clock.restart();
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
	};
}

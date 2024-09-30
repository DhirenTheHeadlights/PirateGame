#pragma once

#include <SFML/Graphics.hpp>

#include "Globals/Context.h"
#include "Globals/JSONSave.h"
#include "Globals/Clock.h"
#include "World/Handlers/ChunkHandler.h"
#include "World/Handlers/CollisionManager.h"
#include "World/Objects/Ship/Handlers/Enemy/EnemyShipHandler.h"
#include "World/Handlers/LandmassHandler.h"
#include "World/Handlers/MenuHandler.h"
#include "World/Objects/Ship/General/PlayerShip.h"
#include "World/Architecture/View.h"
#include "World/World/WaterTiler.h"
#include "World/Architecture/GameState.h"
#include "World/Handlers/WindHandler.h"

namespace PirateGame {
	class World {
	public:
		World(sf::RenderWindow* window) : window(window) {}
		World() = default;
		~World() = default;

		void setUpWorld();
		void gameLoop(sf::Event event);

	protected:
		// Functions
		void setUpWorldElements();
		void setUpPlayerShip();
		void setUpLandMasses();
		void setUpEnemyShips();
		void setUpCollisionManager();
		void setUpMenus();
		void setUpUI();

		void updateGameLoop(sf::Event event);
		void drawGameLoop();
		void updateCoreElements();

		// Global context
		Context context;

		// Game objects
		std::unique_ptr<PlayerShip> playerShip;
		ShipClass playerShipClass = ShipClass::ManOWar;
		View view;

		// Handlers
		LandmassHandler LMH = LandmassHandler(context);
		MenuHandler MH = MenuHandler(context);
		CollisionManager CM = CollisionManager(context);
		EnemyShipHandler ESH = EnemyShipHandler(context);
		WindHandler WH;

		// SFML Objects
		sf::RenderWindow* window = nullptr;

		// Background
		WaterTiler waterTiler;

		// Frame rate variables
		sf::Clock frameRateClock;
		sf::Time frameRateUpdateTime;
		sf::Text frameRateText;
		int frameCount = 0;
		const float numFramesToAverage = 40.f;

		// Game loop clock variables
		sf::Clock gameLoopClock;
		sf::Time gameLoopWaitTime = sf::milliseconds(10);

		// Exp text temp
		sf::Text experience;

		// Object numbers
		int numLandMasses = 5;
		float distanceBetweenLandMasses = 500.f;
		int numEnemyShips = 8;
		float distanceBetweenEnemyShips = 100.f;
	};
}


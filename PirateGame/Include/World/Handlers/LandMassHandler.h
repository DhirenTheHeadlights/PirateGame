#pragma once

/// This class is going to handle the land masses in the game.
/// It will be used to generate the land masses and store them in a vector.

#include <SFML/Graphics.hpp>
#include <vector>

#include "Globals/Context.h"
#include "World/Handlers/QuadtreeHandler.h"

#include "World/Objects/Landmass/Island.h"
#include "World/Objects/Landmass/Rock.h"
#include "World/Objects/Landmass/Shipwreck.h"

namespace PirateGame {
    class LandmassHandler {
    public:
        LandmassHandler(Context& context) : context(context) {};
        ~LandmassHandler();

        void addLandMasses(int numLandMassesPerChunk, float minDistBetweenLandmasses);
        void createIsland(sf::Vector2f position);
        void createRock(sf::Vector2f position);
        void createShipwreck(sf::Vector2f position);
        void drawLandMasses();
        void interactWithLandmasses();

        // Getters
        std::vector<std::shared_ptr<Landmass>>& getLandMasses() { return landmasses; }

        // Setters
        void setPlayerShip(PlayerShip* playerShip) { this->playerShip = playerShip; }
    private:
        Context& context;

        // Helper functions
        void addLandMassesToChunk(const Map& map, int numLandMasses, float minDistBetweenLandmasses);

        std::vector<std::shared_ptr<Landmass>> landmasses;
        std::vector<std::shared_ptr<Island>> islands;
        std::vector<std::shared_ptr<Rock>> rocks;
        std::vector<std::shared_ptr<Shipwreck>> shipwrecks;

        Island* nearestIsland = nullptr;
        PlayerShip* playerShip = nullptr;

        // Values
        float interactionDistance = 1000.f; // Distance for interaction with landmasses
		float lootDistance = 300.f; // Distance for looting landmasses
    };
}
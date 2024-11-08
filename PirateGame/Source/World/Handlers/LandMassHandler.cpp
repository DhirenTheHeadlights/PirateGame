#include "World/Handlers/LandMassHandler.h"

using namespace PirateGame;

LandmassHandler::~LandmassHandler() {
	for (auto& landMass : landmasses) {
		QuadtreeHandler::landmassQuadtree->removeObject(landMass.get());
	}
}

// Add all the land masses to the vector
void LandmassHandler::addLandMasses(const int numLandMassesPerChunk, const float minDistBetweenLandmasses) {
	// Grab all chunks
	for (auto& chunks = ChunkHandler::getAllChunks(); auto& chunk : chunks) {
		addLandMassesToChunk(*chunk.getMap(), numLandMassesPerChunk, minDistBetweenLandmasses);
	}
}

void LandmassHandler::addLandMassesToChunk(const Map& map, const int numLandMasses, const float minDistBetweenLandmasses) {
	// Grab a numLandMasses number of points from the map
	const std::vector<sf::Vector2f> points = map.getRandomPositions(minDistBetweenLandmasses, numLandMasses);

	for (auto& point : points) {
		// Generate a random number between 0 and 2
		const int randNum = vm::randomValue(0, 2);

		// Create a land mass based on the random number
		if (randNum == 0) createIsland(point);
		else if (randNum == 1) createRock(point);
		else createShipwreck(point);
	}
}

void LandmassHandler::createIsland(const sf::Vector2f position) {
	const auto island = std::make_shared<Island>(context);
	island->getSprite().setPosition(position);
	island->createLandMass();
	landmasses.push_back(island);
	islands.push_back(island);
	QuadtreeHandler::landmassQuadtree->addObject(island.get());
	QuadtreeHandler::islandQuadtree->addObject(island.get());
}

void LandmassHandler::createRock(const sf::Vector2f position) {
	const auto rock = std::make_shared<Rock>(context);
	rock->getSprite().setPosition(position);
	rock->createLandMass();
	landmasses.push_back(rock);
	rocks.push_back(rock);
	QuadtreeHandler::landmassQuadtree->addObject(rock.get());
	QuadtreeHandler::rockQuadtree->addObject(rock.get());
}

void LandmassHandler::createShipwreck(const sf::Vector2f position) {
	const auto shipwreck = std::make_shared<Shipwreck>(context);
	shipwreck->getSprite().setPosition(position);
	shipwreck->createLandMass();
	landmasses.push_back(shipwreck);
	shipwrecks.push_back(shipwreck);
	QuadtreeHandler::landmassQuadtree->addObject(shipwreck.get());
	QuadtreeHandler::shipwreckQuadtree->addObject(shipwreck.get());
}

// Draw all the land masses
void LandmassHandler::drawLandMasses() {
	// Remove any inactive land masses
	for (auto& ship : shipwrecks) {
		if (!ship->isActive()) {
			QuadtreeHandler::shipwreckQuadtree->removeObject(ship.get());
			QuadtreeHandler::landmassQuadtree->removeObject(ship.get());
		}
	}
	std::erase_if(shipwrecks, [](const std::shared_ptr<Shipwreck>& ship) { return !ship->isActive(); });
	std::erase_if(landmasses, [](const std::shared_ptr<Landmass>& landmass) { return !landmass->isActive(); });

	// Draw all the land masses and add them to the hashmap
	sf::RenderWindow* window = Globals::window;
	for (const auto& i : landmasses) {
		// Print debug for region types
		TextQueue::displayText(ChunkHandler::getRegionHandler().getRegionValuesAtPosition(i->getSprite().getPosition()).displayString, i->getSprite().getPosition() + sf::Vector2f(0, 50), sf::Color::White);
		i->draw(*window);
	}
}

void LandmassHandler::interactWithLandmasses() {
	std::vector<Island*> nearbyIslands = QuadtreeHandler::islandQuadtree->findObjectsNearObject(playerShip, context.jsl->getGameData().gameConfig.landmassData.landmassInteractionDistance);
	const std::vector<Shipwreck*> nearbyShipwrecks = QuadtreeHandler::shipwreckQuadtree->findObjectsNearObject(playerShip, lootDistance);
	std::vector<Rock*> nearbyRocks = QuadtreeHandler::rockQuadtree->findObjectsNearObject(playerShip, context.jsl->getGameData().gameConfig.landmassData.landmassInteractionDistance);

	if (nearestIsland == nullptr) {
		for (const auto& island : nearbyIslands) {
			const float distance = vm::magnitude(playerShip->getSprite().getPosition() - island->getSprite().getPosition() + island->getSprite().getGlobalBounds().getSize() / 2.f);
			if (distance <= interactionDistance) {
				nearestIsland = island;
				break;
			}
		}

		for (auto& island : islands) {
			if (std::ranges::find(nearbyIslands, island.get()) == nearbyIslands.end()) {
				island->getIslandMenu()->setEnteredIsland(false);
				island->getIslandMenu()->setHasPlayerSaidNo(false);
			}
		}
	}
	// Draw the island menu for the nearest land mass
	else {
		nearestIsland->getIslandMenu()->setShip(*playerShip);
		nearestIsland->getIslandMenu()->draw();
		nearestIsland->getIslandMenu()->update();
	}

	// Handle shipwrecks
	for (const auto& shipwreck : nearbyShipwrecks) {
		const float distance = vm::magnitude(playerShip->getSprite().getPosition() - shipwreck->getSprite().getPosition() + shipwreck->getSprite().getGlobalBounds().getSize() / 2.f);
		if (distance <= lootDistance) {
			// Deactivate the shipwreck
			shipwreck->deactivate();

			// Display the loot
			for (auto& loot : shipwreck->getLoot()) {
				const sf::Text lootText("You have received " + vm::setSignificantFigures(loot.amount, 4) + ' ' + loot.name, Font::globalFont);
				TextQueue::addTextToQueue(lootText, sf::seconds(5.f));
			}

			break;
		}
	}

	// Set the nearest land mass to null if the player is no longer near it
	if (nearestIsland != nullptr) {
		const sf::Vector2f shipPosition = playerShip->getSprite().getPosition(); // Ship position is already the center of the sprite
		const sf::Vector2f islandPosition = nearestIsland->getSprite().getPosition() + nearestIsland->getSprite().getGlobalBounds().getSize() / 2.f; // Land mass position is the top left corner of the sprite
		const float distance = vm::magnitude(shipPosition - islandPosition);

		if (distance > interactionDistance) {
			nearestIsland = nullptr;
		}
	}
}
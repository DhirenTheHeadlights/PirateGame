#pragma once

/// Map for pirate game

#include "World/Architecture/Chunk.h"
#include "World/Handlers/RegionHandler.h"

namespace PirateGame {

	namespace ChunkHandler {

		void initializeMap();

		static void generateRegionCoords(const std::pair<int, int>& chunkCoord) {}

		void updateChunks(sf::RenderWindow* window, const sf::Vector2f position, bool debug = false);
		

		// Setters
		void setRenderDistance(int distance);

		// Getters
		Chunk* getChunkAtPosition(const sf::Vector2f position);
		std::vector<Chunk>& getAllChunks();
		RegionHandler& getRegionHandler();
		sf::FloatRect getMapBounds();

		void generateSurroundingChunks(const std::pair<int, int>& chunkPos);

		void generateChunk(const std::pair<int, int>& chunkCoord);
		
		void deleteChunksOutOfRange(Chunk& currentChunk);

		void deleteChunk(Chunk& chunk);

		void updateMapBounds();


		// Values
		extern RegionHandler regionHandler;
		extern std::vector<Chunk> chunks;
		extern sf::FloatRect mapBounds;
		extern sf::Vector2f chunkSize;

	};
}

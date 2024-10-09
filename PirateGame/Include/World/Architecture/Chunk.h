#pragma once

/// Chunk data

#include "World/Architecture/Map.h"
#include "World/Architecture/Region.h"


namespace PirateGame {
	class Chunk {
	public:
		Chunk(const std::pair<int, int>& chunkCoord, const sf::Vector2f chunkSize, const int cellSize) : chunkCoord(chunkCoord), chunkSize(chunkSize), cellSize(cellSize) {
			map.initialize(static_cast<int>(chunkSize.x), static_cast<int>(chunkSize.y), cellSize, sf::Vector2f(chunkCoord.first * chunkSize.x, chunkCoord.second * chunkSize.y));
		}

		void update() {
			
		}

		// Getters
		Map* getMap() { return &map; }
		std::pair<int, int> getChunkCoord() const { return chunkCoord; }
		Region getRegionType() const { return regionType; }

		// Setters
		void setRegionType(const Region regionType) { this->regionType = regionType; }
	private:
		Map map;
		std::pair<int, int> chunkCoord;
		sf::Vector2f chunkSize;
		int cellSize = 0;
		Region regionType = Region::SandyShores;
	};
}
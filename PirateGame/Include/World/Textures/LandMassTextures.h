#pragma once

#include <vector>
#include <unordered_map>

#include "Globals/TextureHandler.h"
#include "World/Objects/Landmass/LandmassType.h"

namespace PirateGame {
	class LandmassTextureHandler : public TextureHandler {
	public:
		LandmassTextureHandler() {
			loadTextures();
		}
		~LandmassTextureHandler() {}

		TextureResourceManager<IslandType>& getIslandTextures() { return islandTextures; }
		TextureResourceManager<RockType>& getRockTextures() { return rockTextures; }
		TextureResourceManager<ShipwreckType>& getShipwreckTextures() { return shipwreckTextures; }
		TextureResourceManager<MiscType>& getMiscTextures() { return miscTextures; }
	private:
		// Helper functions
		void loadTextures() {
			islandTextures.loadTexture(IslandType::Island1, RESOURCES_PATH "Sprites/Landmass/Island/pg_island_1.png");
			islandTextures.loadTexture(IslandType::Island2, RESOURCES_PATH "Sprites/Landmass/Island/pg_island_2.png");
			
			rockTextures.loadTexture(RockType::Rock1, RESOURCES_PATH "Sprites/Landmass/Rock/pg_rock_1.png");
			rockTextures.loadTexture(RockType::Rock2, RESOURCES_PATH "Sprites/Landmass/Rock/pg_rock_2.png");
			rockTextures.loadTexture(RockType::Rock3, RESOURCES_PATH "Sprites/Landmass/Rock/pg_rock_3.png");
			rockTextures.loadTexture(RockType::Rock4, RESOURCES_PATH "Sprites/Landmass/Rock/pg_rock_4.png");
			rockTextures.loadTexture(RockType::Rock5, RESOURCES_PATH "Sprites/Landmass/Rock/pg_rock_5.png");
			rockTextures.loadTexture(RockType::Rock6, RESOURCES_PATH "Sprites/Landmass/Rock/pg_rock_6.png");
			rockTextures.loadTexture(RockType::Rock7, RESOURCES_PATH "Sprites/Landmass/Rock/pg_rock_7.png");
			rockTextures.loadTexture(RockType::Rock8, RESOURCES_PATH "Sprites/Landmass/Rock/pg_rock_8.png");
			rockTextures.loadTexture(RockType::Rock9, RESOURCES_PATH "Sprites/Landmass/Rock/pg_rock_9.png");

			shipwreckTextures.loadTexture(ShipwreckType::Shipwreck1, RESOURCES_PATH "Sprites/Landmass/Shipwreck/pg_shipwreck_1.png");

			miscTextures.loadTexture(MiscType::Cannonball, RESOURCES_PATH "Sprites/Ship/Cannonball/pg_misc_cannonball.png");
		}
		TextureResourceManager<IslandType> islandTextures;
		TextureResourceManager<RockType> rockTextures;
		TextureResourceManager<ShipwreckType> shipwreckTextures;
		TextureResourceManager<MiscType> miscTextures; // For cannonball only, this needs to change later
	};
}

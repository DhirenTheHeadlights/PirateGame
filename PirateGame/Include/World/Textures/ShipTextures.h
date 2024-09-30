#pragma once

/// This class will handle the textures for the ships in the game.

#include "Globals/TextureHandler.h"
#include "World/Objects/Ship/General/ShipEnums.h"
#include "World/Architecture/Region.h"

namespace PirateGame {
	class ShipTextureHandler : public TextureHandler {
	public:
		ShipTextureHandler() {
			loadTextures();
		};
		~ShipTextureHandler() {};

		TextureResourceManager<ShipClass>& getShipTextureManagerByRegion(const Region region) { return shipTextureManager.at(region); }
		TextureResourceManager<ShipClass>& getCannonTextureManagerByRegion(const Region region) { return cannonTextureManager.at(region); }
		TextureResourceManager<ShipClass>& getSailTextureManagerByRegion(const Region region) { return sailTextureManager.at(region); }
	private:
		// Helper functions
		void  loadTextures() {

			// Load different ship textures for each region
			TextureResourceManager<ShipClass> sandyShoresSTM;
			{
				sandyShoresSTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop.png");
				sandyShoresSTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine.png");
				sandyShoresSTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate.png");
				sandyShoresSTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon.png");
				sandyShoresSTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar.png");
				shipTextureManager.insert(std::make_pair(Region::SandyShores, sandyShoresSTM));
			}
			TextureResourceManager<ShipClass> murkyMarshesSTM;
			{
				murkyMarshesSTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop.png");
				murkyMarshesSTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_2.png");
				murkyMarshesSTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2.png");
				murkyMarshesSTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon.png");
				murkyMarshesSTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar.png");
				shipTextureManager.insert(std::make_pair(Region::MurkyMarshes, murkyMarshesSTM));
			}
			TextureResourceManager<ShipClass> devilsDenSTM;
			{
				devilsDenSTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop.png");
				devilsDenSTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_3.png");
				devilsDenSTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2.png");
				devilsDenSTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon.png");
				devilsDenSTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar.png");
				shipTextureManager.insert(std::make_pair(Region::DevilsDen, devilsDenSTM));
			}
			TextureResourceManager<ShipClass> shipwreckShoalsSTM;
			{
				shipwreckShoalsSTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop.png");
				shipwreckShoalsSTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_4.png");
				shipwreckShoalsSTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2.png");
				shipwreckShoalsSTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon.png");
				shipwreckShoalsSTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar.png");
				shipTextureManager.insert(std::make_pair(Region::ShipwreckShoals, shipwreckShoalsSTM));
			}
			TextureResourceManager<ShipClass> stormySeasSTM;
			{
				stormySeasSTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop.png");
				stormySeasSTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_5.png");
				stormySeasSTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2.png");
				stormySeasSTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon.png");
				stormySeasSTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar.png");
				shipTextureManager.insert(std::make_pair(Region::StormySeas, stormySeasSTM));
			}

			// Load different cannon textures for each region using each ship folder
			TextureResourceManager<ShipClass> sandyShoresCTM;
			{
				sandyShoresCTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_cannon.png");
				sandyShoresCTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_cannon.png");
				sandyShoresCTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_cannon.png");
				sandyShoresCTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_cannon.png");
				sandyShoresCTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_cannon.png");
				cannonTextureManager.insert(std::make_pair(Region::SandyShores, sandyShoresCTM));
			}
			TextureResourceManager<ShipClass> murkyMarshesCTM;
			{
				murkyMarshesCTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_cannon.png");
				murkyMarshesCTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_2_cannon.png");
				murkyMarshesCTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_cannon.png");
				murkyMarshesCTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_cannon.png");
				murkyMarshesCTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_cannon.png");
				cannonTextureManager.insert(std::make_pair(Region::MurkyMarshes, murkyMarshesCTM));
			}
			TextureResourceManager<ShipClass> devilsDenCTM;
			{
				devilsDenCTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_cannon.png");
				devilsDenCTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_3_cannon.png");
				devilsDenCTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_cannon.png");
				devilsDenCTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_cannon.png");
				devilsDenCTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_cannon.png");
				cannonTextureManager.insert(std::make_pair(Region::DevilsDen, devilsDenCTM));
			}
			TextureResourceManager<ShipClass> shipwreckShoalsCTM;
			{
				shipwreckShoalsCTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_cannon.png");
				shipwreckShoalsCTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_4_cannon.png");
				shipwreckShoalsCTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_cannon.png");
				shipwreckShoalsCTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_cannon.png");
				shipwreckShoalsCTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_cannon.png");
				cannonTextureManager.insert(std::make_pair(Region::ShipwreckShoals, shipwreckShoalsCTM));
			}
			TextureResourceManager<ShipClass> stormySeasCTM;
			{
				stormySeasCTM.loadTexture(ShipClass::Sloop, RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_cannon.png");
				stormySeasCTM.loadTexture(ShipClass::Brigantine, RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_5_cannon.png");
				stormySeasCTM.loadTexture(ShipClass::Frigate, RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_cannon.png");
				stormySeasCTM.loadTexture(ShipClass::Galleon, RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_cannon.png");
				stormySeasCTM.loadTexture(ShipClass::ManOWar, RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_cannon.png");
				cannonTextureManager.insert(std::make_pair(Region::StormySeas, stormySeasCTM));
			}

			// Load different sail textures for each region using each ship folder
			TextureResourceManager<ShipClass> sandyShoresSailTM;
			{
				std::vector<std::string> sloopSailTexturesSandyShores = {
					RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_sail.png"
				};
				sandyShoresSailTM.loadTextures(ShipClass::Sloop, sloopSailTexturesSandyShores);
				std::vector<std::string> brigantineSailTexturesSandyShores = {
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_sail_back.png"
				};
				sandyShoresSailTM.loadTextures(ShipClass::Brigantine, brigantineSailTexturesSandyShores);
				std::vector<std::string> frigateSailTexturesSandyShores = {
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_sail_back.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_sail_front.png"
				};
				sandyShoresSailTM.loadTextures(ShipClass::Frigate, frigateSailTexturesSandyShores);
				std::vector<std::string> galleonSailTexturesSandyShores = {
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_back.png"
				};
				sandyShoresSailTM.loadTextures(ShipClass::Galleon, galleonSailTexturesSandyShores);
				std::vector<std::string> manOWarSailTexturesSandyShores = {
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back.png"
				};
				sandyShoresSailTM.loadTextures(ShipClass::ManOWar, manOWarSailTexturesSandyShores);
				sailTextureManager.insert(std::make_pair(Region::SandyShores, sandyShoresSailTM));
			}
			TextureResourceManager<ShipClass> murkyMarshesSailTM;
			{
				std::vector<std::string> sloopSailTexturesMurkyMarshes = {
					RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_sail.png"
				};
				murkyMarshesSailTM.loadTextures(ShipClass::Sloop, sloopSailTexturesMurkyMarshes);
				std::vector<std::string> brigantineSailTexturesMurkyMarshes = {
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_2_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_2_sail_back.png"
				};
				murkyMarshesSailTM.loadTextures(ShipClass::Brigantine, brigantineSailTexturesMurkyMarshes);
				std::vector<std::string> frigateSailTexturesMurkyMarshes = {
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_back.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_front.png"
				};
				murkyMarshesSailTM.loadTextures(ShipClass::Frigate, frigateSailTexturesMurkyMarshes);
				std::vector<std::string> galleonSailTexturesMurkyMarshes = {
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_back.png"
				};
				murkyMarshesSailTM.loadTextures(ShipClass::Galleon, galleonSailTexturesMurkyMarshes);
				std::vector<std::string> manOWarSailTexturesMurkyMarshes = {
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back.png"
				};
				murkyMarshesSailTM.loadTextures(ShipClass::ManOWar, manOWarSailTexturesMurkyMarshes);
				sailTextureManager.insert(std::make_pair(Region::MurkyMarshes, murkyMarshesSailTM));
			}
			TextureResourceManager<ShipClass> devilsDenSailTM;
			{
				std::vector<std::string> sloopSailTexturesDevilsDen = {
					RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_sail.png"
				};
				devilsDenSailTM.loadTextures(ShipClass::Sloop, sloopSailTexturesDevilsDen);
				std::vector<std::string> brigantineSailTexturesDevilsDen = {
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_3_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_3_sail_back.png"
				};
				devilsDenSailTM.loadTextures(ShipClass::Brigantine, brigantineSailTexturesDevilsDen);
				std::vector<std::string> frigateSailTexturesDevilsDen = {
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_back.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_front.png"
				};
				devilsDenSailTM.loadTextures(ShipClass::Frigate, frigateSailTexturesDevilsDen);
				std::vector<std::string> galleonSailTexturesDevilsDen = {
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_back.png"
				};
				devilsDenSailTM.loadTextures(ShipClass::Galleon, galleonSailTexturesDevilsDen);
				std::vector<std::string> manOWarSailTexturesDevilsDen = {
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back.png"
				};
				devilsDenSailTM.loadTextures(ShipClass::ManOWar, manOWarSailTexturesDevilsDen);
				sailTextureManager.insert(std::make_pair(Region::DevilsDen, devilsDenSailTM));
			}
			TextureResourceManager<ShipClass> shipwreckShoalsSailTM;
			{
				std::vector<std::string> sloopSailTexturesShipwreckShoals = {
					RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_sail.png"
				};
				shipwreckShoalsSailTM.loadTextures(ShipClass::Sloop, sloopSailTexturesShipwreckShoals);
				std::vector<std::string> brigantineSailTexturesShipwreckShoals = {
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_4_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_4_sail_back.png"
				};
				shipwreckShoalsSailTM.loadTextures(ShipClass::Brigantine, brigantineSailTexturesShipwreckShoals);
				std::vector<std::string> frigateSailTexturesShipwreckShoals = {
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_back.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_front.png"
				};
				shipwreckShoalsSailTM.loadTextures(ShipClass::Frigate, frigateSailTexturesShipwreckShoals);
				std::vector<std::string> galleonSailTexturesShipwreckShoals = {
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_back.png"
				};
				shipwreckShoalsSailTM.loadTextures(ShipClass::Galleon, galleonSailTexturesShipwreckShoals);
				std::vector<std::string> manOWarSailTexturesShipwreckShoals = {
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back.png"
				};
				shipwreckShoalsSailTM.loadTextures(ShipClass::ManOWar, manOWarSailTexturesShipwreckShoals);
				sailTextureManager.insert(std::make_pair(Region::ShipwreckShoals, shipwreckShoalsSailTM));
			}
			TextureResourceManager<ShipClass> stormySeasSailTM;
			{
				std::vector<std::string> sloopSailTexturesStormySeas = {
					RESOURCES_PATH "Sprites/Ship/Sloop/pg_ship_sloop_sail.png"
				};
				stormySeasSailTM.loadTextures(ShipClass::Sloop, sloopSailTexturesStormySeas);
				std::vector<std::string> brigantineSailTexturesStormySeas = {
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_5_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Brigantine/pg_ship_brigantine_5_sail_back.png"
				};
				stormySeasSailTM.loadTextures(ShipClass::Brigantine, brigantineSailTexturesStormySeas);
				std::vector<std::string> frigateSailTexturesStormySeas = {
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_back.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Frigate/pg_ship_frigate_2_sail_front.png"
				};
				stormySeasSailTM.loadTextures(ShipClass::Frigate, frigateSailTexturesStormySeas);
				std::vector<std::string> galleonSailTexturesStormySeas = {
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_middle.png",
					RESOURCES_PATH "Sprites/Ship/Galleon/pg_ship_galleon_sail_back.png"
				};
				stormySeasSailTM.loadTextures(ShipClass::Galleon, galleonSailTexturesStormySeas);
				std::vector<std::string> manOWarSailTexturesStormySeas = {
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_front_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back_middle.png",
					RESOURCES_PATH "Sprites/Ship/Manowar/pg_ship_manowar_sail_back.png"
				};
				stormySeasSailTM.loadTextures(ShipClass::ManOWar, manOWarSailTexturesStormySeas);
				sailTextureManager.insert(std::make_pair(Region::StormySeas, stormySeasSailTM));
			}
		}

		// Texture manager
		std::unordered_map<Region, TextureResourceManager<ShipClass>> shipTextureManager;
		std::unordered_map<Region, TextureResourceManager<ShipClass>> cannonTextureManager;
		std::unordered_map<Region, TextureResourceManager<ShipClass>> sailTextureManager;
	};
}

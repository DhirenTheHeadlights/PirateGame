#pragma once

#include "World/Textures/InteractableTextures.h"
#include "World/Textures/LandmassTextures.h"
#include "World/Textures/HUDTextures.h"
#include "World/Textures/OptionsMenuTextures.h"
#include "World/Textures/MarketTextures.h"
#include "World/Textures/ShipTextures.h"
#include "World/Textures/InventoryTextures.h"

namespace PirateGame::Textures {
	inline InteractableTextureHandler interactableTextures;
	inline LandmassTextureHandler landmassTextures;
	inline HUDTextureHandler HUDTextures;
	inline OptionsMenuTextureHandler optionsMenuTextures;
	inline MarketTextureHandler marketTextures;
	inline ShipTextureHandler shipTextures;
	inline InventoryTextureHandler inventoryTextures;
}
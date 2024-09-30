#include "World/Objects/Landmass/Island.h"

using namespace PirateGame;

void Island::createLandMass() {
	LandMassTypeGenerator<IslandType> typeGen;
	type = typeGen.getType();
	sprite.setTexture(Textures::landmassTextures.getIslandTextures().getTexture(type));
	sprite.setScale(context.jsl->getGameData().gameConfig.landmassData.islandScaling, context.jsl->getGameData().gameConfig.landmassData.islandScaling);

	market = createLootPool(context.jsl->getGameData().gameConfig.landmassData.islandMarketSizeLimit, context.jsl->getGameData().gameConfig.landmassData.islandMarketPriceLimit, context.jsl->getGameData().gameConfig.landmassData.islandMarketSizeLimit);
	islandMenu = std::make_unique<IslandMenu>(context, market);
	islandMenu->setUpMenu();
}
#include "World/Objects/Landmass/Shipwreck.h"

using namespace PirateGame;

void Shipwreck::createLandMass() {
	LandMassTypeGenerator<ShipwreckType> typeGen;
	type = typeGen.getType();
	sprite.setTexture(Textures::landmassTextures.getShipwreckTextures().getTexture(type));
	sprite.setScale(context.jsl->getGameData().gameConfig.landmassData.shipwreckScaling, context.jsl->getGameData().gameConfig.landmassData.shipwreckScaling);

	loot = createLootPool(context.jsl->getGameData().gameConfig.landmassData.shipwreckLootPoolSize, 1, context.jsl->getGameData().gameConfig.landmassData.shipwreckLootPoolSize);
}
#include "World/Objects/Landmass/Rock.h"

using namespace PirateGame;

void Rock::createLandMass() {
	LandMassTypeGenerator<RockType> typeGen;
	type = typeGen.getType();
	sprite.setTexture(Textures::landmassTextures.getRockTextures().getTexture(type));
	sprite.setScale(context.jsl->getGameData().gameConfig.landmassData.rockScaling, context.jsl->getGameData().gameConfig.landmassData.rockScaling);
}
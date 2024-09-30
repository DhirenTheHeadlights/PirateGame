#pragma once

#include "JsonLoader.h"
#include "SoundHandler.h"
#include "World/Handlers/IdManager.h"

namespace PirateGame {
	struct Context {
		std::unique_ptr<SoundManager> gsm = std::make_unique<SoundManager>();
		std::unique_ptr<IdManager> gidm = std::make_unique<IdManager>();
		std::unique_ptr<JsonLoader> jsl = std::make_unique<JsonLoader>();
	};
}

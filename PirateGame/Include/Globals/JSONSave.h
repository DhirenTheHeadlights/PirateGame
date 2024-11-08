#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <tuple>
#include <Lib/json.hpp>

#include "World/Objects/General/ShopItem.h"
#include "World/Objects/Ship/General/PlayerShip.h"

namespace PirateGame::JSONSave {
	using json = nlohmann::json;
	static void saveData(const std::string& filename, PlayerShip* playerShip) {
		json save;
		save["playerExperience"] = playerShip->getExp();
		save["playerExperienceToLevelUp"] = playerShip->getExpToLevelUp();
		save["playerLevel"] = playerShip->getPlayerLevel();
		save["playerGold"] = playerShip->getInventoryHandler()->getGold();
		std::vector<std::tuple<std::string, float, int>> playerInventoryVector;
		for (auto& item : playerShip->getInventoryHandler()->getInventory()) {
			playerInventoryVector.push_back(std::make_tuple(item.name, item.price, item.amount));
		}
		save["playerInventory"] = playerInventoryVector;
		save["playerShipClass"] = static_cast<int>(playerShip->getShipClass());
		save["playerPosition"] = { playerShip->getSprite().getPosition().x, playerShip->getSprite().getPosition().y };
		std::ofstream savefile(filename);
		savefile << save.dump(4);
		savefile.close();
	}

}

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>

namespace PirateGame {
    struct ID {
        int id;

        ID() : id(-1) {}

        bool operator==(const ID& other) const {
			if (id == -1 || other.id == -1) {
				std::cerr << "Comparing invalid IDs\n";
				return false;
			}
            return id == other.id;
        }
    private:
        explicit ID(const int id) : id(id) {}

        friend class IdManager;
    };

    class IdManager {
    public:
        std::shared_ptr<ID> generateID() {
	        const int newId = static_cast<int>(ids.size());
            auto idPtr = std::shared_ptr<ID>(new ID(newId)); // Create shared_ptr directly
            ids.push_back(idPtr);
            return idPtr;
        }

        void registerObject(const std::shared_ptr<ID>& obj) {
            idMap[obj->id] = obj;
        }

        bool isObjectAlive(const int id) {
	        if (const auto it = idMap.find(id); it != idMap.end()) {
                if (!it->second.expired()) {
                    return true;
                }
                else {
                    idMap.erase(it);
                }
            }
            return false;
        }

    private:
        std::vector<std::shared_ptr<ID>> ids;
        std::unordered_map<int, std::weak_ptr<ID>> idMap;
    };
}

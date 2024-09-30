#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <concepts>

#include "Lib/VectorMath.h"
#include "World/Handlers/IdManager.h"
#include "World/Architecture/TextQueue.h"

namespace PirateGame {

    /// Concept to check if a class has a method getID that returns an ID*
    template <class T>
    concept HasGetID = requires(T t) {
        { t.getID() } -> std::convertible_to<ID*>;
    };

    /// Concept to check if a class has a method getSprite that returns an sf::Sprite&
    template <class T>
    concept HasGetSprite = requires(T t) {
        { t.getSprite() } -> std::convertible_to<sf::Sprite&>;
    };

    /// Concept to check if a class has a public member variable named id
    template <class T>
    concept HasPublicID = requires(T t) {
        { t.id } -> std::convertible_to<ID*>;
    };

    /// Concept to check if a class has a public member variable named sprite
    template <class T>
    concept HasPublicSprite = requires(T t) {
        { t.sprite } -> std::convertible_to<sf::Sprite&>;
    };

    /// Concept to check if a class has either getID() or a public member variable id
    template <class T>
    concept SupportsID = HasGetID<T> || HasPublicID<T>;

    /// Concept to check if a class has either getSprite() or a public member variable sprite
    template <class T>
    concept SupportsSprite = HasGetSprite<T> || HasPublicSprite<T>;

    class Node;  // Forward declaration of Node to be used in QuadtreeObject

    class QuadtreeObject {
    public:
        ID* id;                                     // ID of the object
        sf::Sprite& sprite;                         // Sprite of the object
        std::unordered_set<Node*> registeredNodes;  // Nodes that this object is registered with

        QuadtreeObject(ID* id, sf::Sprite& sprite) : id(id), sprite(sprite) {}

        void registerNode(Node* node) {
            registeredNodes.insert(node);
        }

        void unregisterNode(Node* node) {
            registeredNodes.erase(node);
        }
    };

    class Node {
    public:
        sf::FloatRect boundary;
        std::vector<std::shared_ptr<QuadtreeObject>> objects;  // Changed to shared_ptr
        std::vector<std::unique_ptr<Node>> children;
        bool divided;

        Node(const sf::FloatRect& bounds, const int maxObjects)
            : boundary(bounds), divided(false) {
            objects.reserve(maxObjects);
        }

        void update(const int maxObjects) {
            if (divided) {
                for (const auto& child : children) {
                    child->update(maxObjects);
                }

                int totalObjects = 0;
                bool anyChildDivided = false;
                for (const auto& child : children) {
                    totalObjects += static_cast<int>(child->objects.size());
                    if (child->divided) {
                        anyChildDivided = true;
                    }
                }

                // If total objects in children are less than maxObjects and no child is divided, merge them
                if (totalObjects < maxObjects && !anyChildDivided) {
                    merge();
                }

                // Collect objects to remove
                std::vector<std::shared_ptr<QuadtreeObject>> objectsToReinsert;
                for (const auto& obj : objects) {
                    if (!boundary.intersects(obj->sprite.getGlobalBounds())) {
                        objectsToReinsert.push_back(obj);
                    }
                }

                // Remove and re-add objects after iteration
                for (const auto& obj : objectsToReinsert) {
                    removeObject(obj);
                    addObject(obj, maxObjects);
                }
            }
        }

        void subdivide(const int maxObjects) {
            const float x = boundary.left;
            const float y = boundary.top;
            const float width = boundary.width / 2;
            const float height = boundary.height / 2;

            children.push_back(std::make_unique<Node>(sf::FloatRect(x, y, width, height), maxObjects));
            children.push_back(std::make_unique<Node>(sf::FloatRect(x + width, y, width, height), maxObjects));
            children.push_back(std::make_unique<Node>(sf::FloatRect(x, y + height, width, height), maxObjects));
            children.push_back(std::make_unique<Node>(sf::FloatRect(x + width, y + height, width, height), maxObjects));

            divided = true;

            // Redistribute objects to new children using addObject
            for (const auto& obj : objects) {
                for (const auto& child : children) {
                    if (child->addObject(obj, maxObjects)) {
                        break;
                    }
                }
            }

            objects.clear();  // Clear the objects in the current node as they are now in the children
        }

        bool addObject(const std::shared_ptr<QuadtreeObject>& qtObject, const int maxObjects) {
            if (!boundary.intersects(qtObject->sprite.getGlobalBounds())) {
                return false;
            }

            if (divided) {
                return std::ranges::any_of(children, [&](const auto& child) {
                    return child->addObject(qtObject, maxObjects);
                    });
            }

            if (objects.size() >= maxObjects) {
                subdivide(maxObjects);
                return addObject(qtObject, maxObjects);
            }

            objects.push_back(qtObject);
            qtObject->registerNode(this);  // Tag the node
            return true;
        }

        bool removeObject(const std::shared_ptr<QuadtreeObject>& qtObject) {
            const auto it = std::remove(objects.begin(), objects.end(), qtObject);
            if (it != objects.end()) {
                objects.erase(it, objects.end());
                qtObject->unregisterNode(this);  // Update the node registration
                return true;
            }

            // Check children if not found in the current node
            if (divided) {
                for (const auto& child : children) {
                    if (child->removeObject(qtObject)) {
                        return true;
                    }
                }
            }

            return false;
        }

        void merge() {
            if (divided) {
                for (const auto& child : children) {
                    child->merge();
                    for (const auto& obj : child->objects) {
                        objects.push_back(obj);
                        obj->unregisterNode(child.get());
                        obj->registerNode(this);
                    }
                }
                children.clear();
                divided = false;
            }
        }

        void findObjectsInRange(const sf::FloatRect& range, std::vector<std::shared_ptr<QuadtreeObject>>& found) const {
            if (!boundary.intersects(range)) {
                return;
            }

            // Check objects in the current node
            for (const auto& object : objects) {
                if (object->sprite.getGlobalBounds().intersects(range)) {
                    found.push_back(object);
                }
            }

            // Recur into children if the node is divided
            if (divided) {
                for (const auto& child : children) {
                    child->findObjectsInRange(range, found);
                }
            }
        }
    };

    // Quadtree class remains largely the same with updates to use shared_ptr
    template <typename T> requires SupportsSprite<T>&& SupportsID<T>
    class Quadtree {
    public:
        template <typename V> requires SupportsSprite<V>
        static sf::Sprite& getObjectSprite(V* object) {
            if constexpr (HasGetSprite<V>) {
                return object->getSprite();
            }
            else {
                return object->sprite;
            }
        }

        template <typename V> requires SupportsID<V>
        static ID* getObjectId(V* object) {
            if constexpr (HasGetID<V>) {
                return object->getID();
            }
            else {
                return object->id;
            }
        }

        const int maxObjects = 4;
        std::unique_ptr<Node> root;
        std::unordered_map<T*, std::shared_ptr<QuadtreeObject>> objectMap;
        std::unordered_map<QuadtreeObject*, T*> reverseObjectMap;

        explicit Quadtree(const sf::FloatRect& initialBounds) {
            std::cout << "Initial boundary: " << initialBounds.left << ", " << initialBounds.top << ", "
                << initialBounds.width << ", " << initialBounds.height << '\n';

            root = std::make_unique<Node>(initialBounds, maxObjects);
        }

        void update(const sf::FloatRect& currentBoundary) {
            constexpr float threshold = 0.1f;
            if (std::fabs(currentBoundary.left - root->boundary.left) > threshold ||
                std::fabs(currentBoundary.top - root->boundary.top) > threshold ||
                std::fabs(currentBoundary.width - root->boundary.width) > threshold ||
                std::fabs(currentBoundary.height - root->boundary.height) > threshold) {
                // The new boundary is different from the current root boundary
                extend(currentBoundary);
            }
            root->update(maxObjects);
        }

        bool addObject(T* object) {
            if (!root->boundary.intersects(getObjectSprite(object).getGlobalBounds())) {
                std::cerr << "Error: Object is out of quadtree bounds. Cannot add." << '\n';
                return false;
            }

            auto qtObject = std::make_shared<QuadtreeObject>(getObjectId(object), getObjectSprite(object));
            if (root->addObject(qtObject, maxObjects)) {
                objectMap.insert({ object, qtObject });
                reverseObjectMap.insert({ qtObject.get(), object });
                return true;
            }

            std::cerr << "Error: Object addition failed." << '\n';
            return false;
        }

        bool removeObject(T* object) {
            auto it = objectMap.find(object);

            if (it == objectMap.end()) {
                std::cerr << "Error: Failed to remove object from quadtree." << '\n';
                return false;
            }

            const std::shared_ptr<QuadtreeObject> qtObject = it->second;

            // Remove the object from all registered nodes
            for (const auto node : qtObject->registeredNodes) {
                if (!node->removeObject(qtObject))
                    std::cerr << "Error: Failed to remove object from node." << '\n';
            }
            qtObject->registeredNodes.clear();

            reverseObjectMap.erase(qtObject.get());
            objectMap.erase(it);
            return true;
        }

        template <SupportsSprite U>
        std::vector<T*> findObjectsNearObject(U* queryObject, const float distance) {
            sf::FloatRect queryBounds = getObjectSprite(queryObject).getGlobalBounds();

            // Expand the bounds by the distance
            queryBounds.left -= distance;
            queryBounds.top -= distance;
            queryBounds.width += 2 * distance;
            queryBounds.height += 2 * distance;

            std::vector<std::shared_ptr<QuadtreeObject>> nearbyObjects;
            root->findObjectsInRange(queryBounds, nearbyObjects);

            std::vector<T*> found;
            for (const auto& qtobject : nearbyObjects) {
                found.push_back(reverseObjectMap.at(qtobject.get()));
            }
            return found;
        }

        // Extend function to enlarge the quadtree boundary
        void extend(const sf::FloatRect& requiredBoundary) {
            sf::FloatRect newBoundary = root->boundary;

            // Expand the boundary to include the required boundary
            const float left = std::min(newBoundary.left, requiredBoundary.left);
            const float top = std::min(newBoundary.top, requiredBoundary.top);
            const float right = std::max(newBoundary.left + newBoundary.width, requiredBoundary.left + requiredBoundary.width);
            const float bottom = std::max(newBoundary.top + newBoundary.height, requiredBoundary.top + requiredBoundary.height);

            newBoundary.left = left;
            newBoundary.top = top;
            newBoundary.width = right - left;
            newBoundary.height = bottom - top;

            // Create a new root node with the expanded boundary
            auto newRoot = std::make_unique<Node>(newBoundary, maxObjects);

            // Reinsert all objects
            for (auto& [_, qtObject] : objectMap) {
                qtObject->registeredNodes.clear();
                newRoot->addObject(qtObject, maxObjects);
            }

            // Replace the root
            root = std::move(newRoot);
        }

        void updateObjectPosition(T* object) {
            // Not needed in this implementation
        }

        void draw() const {
            drawNode(root.get());
        }

        static void drawNode(const Node* node) {
            if (!node) return;

            if (!node->divided) {
                TextQueue::displayText("Num obj: " + std::to_string(node->objects.size()),
                    sf::Vector2f(node->boundary.left + node->boundary.width / 2 - 10.f,
                        node->boundary.top + node->boundary.height / 2 - 5.f),
                    sf::Color::White);
            }

            if (node->divided) {
                for (const auto& child : node->children) {
                    drawNode(child.get());
                }
            }

            sf::RectangleShape rectangle(sf::Vector2f(node->boundary.width, node->boundary.height));
            rectangle.setPosition(node->boundary.left, node->boundary.top);
            rectangle.setFillColor(sf::Color::Transparent);
            rectangle.setOutlineThickness(1.f);
            rectangle.setOutlineColor(sf::Color::Blue);  // Node boundary

            Globals::window->draw(rectangle);

            // Draw the objects' positions
            for (const auto& object : node->objects) {
                sf::CircleShape marker(2);  // Small circle marker
                sf::Vector2f pos = object->sprite.getPosition();
                marker.setPosition(pos.x, pos.y);
                marker.setFillColor(sf::Color::Magenta);  // Object position
                Globals::window->draw(marker);
            }
        }

        std::vector<T*> getObjects() const {
            std::vector<T*> objects;
            for (const auto& pair : objectMap) {
                objects.push_back(pair.first);
            }
            return objects;
        }
    };

}
#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <ranges>
#include <string>

namespace PirateGame {
    // Define the enum class for sound identifiers
    enum class SoundId {
        Bonk,
        Select,
        CannonShot,
        CannonImpact,
        // Add more identifiers as needed
    };

    class SoundManager {
    public:
        SoundManager() {
            // Set up the sound paths
            setSoundFilePath(SoundId::Bonk, RESOURCES_PATH "Sounds/bonk.wav");
            setSoundFilePath(SoundId::Select, RESOURCES_PATH "Sounds/select.wav");
            setSoundFilePath(SoundId::CannonShot, RESOURCES_PATH "Sounds/cannon_shot.wav");
            setSoundFilePath(SoundId::CannonImpact, RESOURCES_PATH "Sounds/cannon_impact.wav");

            // Load the sound buffers
            for (const auto& key : soundFilePaths | std::views::keys) {
                loadSound(key);
            }
        }

        // Loads and plays sounds by their identifiers
        void playSound(SoundId soundId);

        // Setters
        void setSoundVolume(const float volume) { soundVolume = volume; }

    private:
        // Helper methods
        sf::Sound& findAvailableSound();
        void loadSound(SoundId soundId);
        void setSoundFilePath(SoundId soundId, const std::string& filePath);

        // Sound data containers
        std::map<SoundId, std::string> soundFilePaths;
        std::map<SoundId, sf::SoundBuffer> soundBuffers;
        std::vector<sf::Sound> sounds;

        // Values
        float soundVolume = 50;
    };

}

#include <iostream>

#include "Globals/SoundHandler.h"

using namespace PirateGame;

void SoundManager::setSoundFilePath(const SoundId soundId, const std::string& filePath) {
    soundFilePaths[soundId] = filePath;
}

void SoundManager::loadSound(const SoundId soundId) {
    if (const auto filePathIt = std::ranges::find(soundFilePaths, soundId, &std::pair<const SoundId, std::string>::first);
        filePathIt != soundFilePaths.end()) {
	    if (sf::SoundBuffer buffer; buffer.loadFromFile(filePathIt->second)) {
            soundBuffers[soundId] = buffer;
        }
        else {
            std::cerr << "Failed to load sound buffer: " << filePathIt->second << '\n';
        }
    }
    else {
        std::cerr << "Sound ID not found in file path map." << '\n';
    }
}


void SoundManager::playSound(SoundId soundId) {
    auto bufferIt = soundBuffers.find(soundId);
    if (bufferIt != soundBuffers.end()) {
        sf::Sound& sound = findAvailableSound();
        sound.setBuffer(bufferIt->second);
        sound.setVolume(soundVolume);
        sound.play();
    }
    else {
        std::cerr << "Sound ID not found in loaded buffers. Did you forget to load it in the Global class?" << '\n';
    }
}

sf::Sound& SoundManager::findAvailableSound() {
    for (auto& sound : sounds) {
        if (sound.getStatus() != sf::Sound::Playing) {
            return sound;
        }
    }

    sounds.emplace_back();
    return sounds.back();
}

#include "audio_manager.h"
#include <filesystem>
#include <iostream>
#include <random>

AudioManager& AudioManager::get_instance() {
    static AudioManager instance;
    return instance;
}

void AudioManager::init() {
    loadSoundsFromDirectory("res/sound/");
    masterVolume = 100.0f;
    musicVolume = 100.0f;
    fadingMusic = false;
}

void AudioManager::playSound(const std::string& name) {
    std::random_device rd;
    std::mt19937 rng(rd());
    auto itGroup = soundGroups.find(name);
    if (itGroup != soundGroups.end()) {
        std::uniform_int_distribution<size_t> dist(0, itGroup->second.size() - 1);
        auto& soundName = itGroup->second[dist(rng)];
        auto itSound = sounds.find(soundName);
        if (itSound != sounds.end()) {
            itSound->second.setVolume(masterVolume);
            itSound->second.play();
        }
    } else {
        auto it = sounds.find(name);
        if (it != sounds.end()) {
            it->second.setVolume(masterVolume);
            it->second.play();
        }
    }
}

void AudioManager::playMusic(const std::string& name, bool loop, float fadeInDuration) {
    if (currentMusic.openFromFile("res/sound/" + name)) {
        currentMusic.setVolume(0.0f); // Start volume at 0 for fade in
        currentMusic.setLoop(loop);
        currentMusic.play();

        if (fadeInDuration > 0.0f) {
            fadingIn = true;
            fadeDuration = fadeInDuration;
            fadeTimer = 0.0f;
            fadingMusic = true;
        } else {
            currentMusic.setVolume(musicVolume);
        }
    }
}

void AudioManager::stopMusic(float fadeOutDuration) {
    if (fadeOutDuration > 0.0f && currentMusic.getStatus() == sf::Music::Playing) {
        fadingIn = false;
        fadeDuration = fadeOutDuration;
        fadeTimer = 0.0f;
        fadingMusic = true;
    } else {
        currentMusic.stop();
    }
}

void AudioManager::setMasterVolume(float volume) {
    masterVolume = volume;
    for (auto& sound : sounds) {
        sound.second.setVolume(volume);
    }
    musicVolume = volume; // Optionally separate music volume control
    currentMusic.setVolume(volume);
}

void AudioManager::update(float dt) {
    if (fadingMusic) {
        fadeTimer += dt;
        float volume = fadingIn ? (fadeTimer / fadeDuration) * musicVolume : (1.0f - fadeTimer / fadeDuration) * musicVolume;
        currentMusic.setVolume(volume);
        if (fadeTimer >= fadeDuration) {
            fadingMusic = false;
            if (!fadingIn) {
                currentMusic.stop();
            }
        }
    }
}

void AudioManager::loadSoundsFromDirectory(const std::string& directory) {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            auto ext = entry.path().extension().string();
            if (ext == ".ogg" || ext == ".wav") {
                std::string filename = entry.path().string();
                sf::SoundBuffer buffer;
                if (buffer.loadFromFile(filename)) {
                    std::string soundName = entry.path().stem().string();
                    soundBuffers[soundName] = buffer;
                    sounds[soundName].setBuffer(soundBuffers[soundName]);
                    std::cout << "Loaded sound: " << soundName << std::endl;

                    // Check for sound group (naming convention: groupname_number)
                    auto underscorePos = soundName.find('_');
                    if (underscorePos != std::string::npos) {
                        std::string groupName = soundName.substr(0, underscorePos);
                        soundGroups[groupName].push_back(soundName);
                    }
                }
            }
        }
    }
}


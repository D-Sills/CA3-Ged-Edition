#include "audio_manager.h"
#include "engine/system_resources.h"

AudioManager& AudioManager::get_instance() {
    static AudioManager instance;
    return instance;
}

AudioManager::AudioManager() : musicVolume(100.0f), globalSoundVolume(100.0f) {}

bool AudioManager::loadMusic(const std::string& filename) {
    auto m = Resources::load<sf::Music>(filename);
    if (m) {
        music->setVolume(musicVolume);
    }
    return true;
}

void AudioManager::playMusic(const std::string& filename) {
    music = Resources::load<sf::Music>(filename);
    if (music) {
        music->play();
        music->setVolume(musicVolume);
    }
}

void AudioManager::pauseMusic() {
    music->pause();
}

void AudioManager::stopMusic() {
    music->stop();
}

void AudioManager::setMusicVolume(float new_volume) {
    musicVolume = new_volume;
    music->setVolume(musicVolume);
}

float AudioManager::getMusicVolume() const {
    return musicVolume;
}

bool AudioManager::isMusicPlaying() const {
    return music->getStatus() == sf::Music::Playing;
}

void AudioManager::loadSoundEffect(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (buffer.loadFromFile(filename)) {
        soundBuffers[name] = buffer;
        sounds[name].setBuffer(soundBuffers[name]);
        sounds[name].setVolume(globalSoundVolume);
    }
}

void AudioManager::playSoundEffect(const std::string& name) {
    auto found = sounds.find(name);
    if (found != sounds.end()) {
        found->second.play();
    }
}

void AudioManager::setSoundEffectVolume(const std::string& name, float volume) {
    auto found = sounds.find(name);
    if (found != sounds.end()) {
        found->second.setVolume(volume);
    }
}

void AudioManager::setGlobalSoundEffectVolume(float volume) {
    globalSoundVolume = volume;
    for (auto& sound : sounds) {
        sound.second.setVolume(globalSoundVolume);
    }
}


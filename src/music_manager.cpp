#include "music_player.h"

musicManager::musicManager() : volume(100.0f) {
    // Default volume is set to 100%
}

musicManager& musicManager::get_instance() {
    static music_player instance;
    return instance;
}

bool musicManager::load(const std::string& filename) {
    bool success = music.openFromFile(filename);
    if (success) {
        music.setVolume(volume);
    }
    return success;
}

void musicManager::play() {
    music.play();
}

void musicManager::pause() {
    music.pause();
}

void musicManager::stop() {
    music.stop();
}

void musicManager::set_volume(float new_volume) {
    volume = new_volume;
    music.setVolume(volume);
}

float musicManager::get_volume() const {
    return volume;
}

bool musicManager::is_playing() const {
    return music.getStatus() == sf::Music::Playing;
}

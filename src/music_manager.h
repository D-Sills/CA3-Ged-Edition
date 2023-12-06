#pragma once
#include <SFML/Audio.hpp>
#include <string>

class musicManager {
public:
    static musicManager& get_instance();

    musicManager(const musicManager&) = delete;
    musicManager& operator=(const musicManager&) = delete;

    bool load(const std::string& filename);
    void play();
    void pause();
    void stop();
    void set_volume(float volume);
    float get_volume() const;
    bool is_playing() const;

private:
    musicManager();
    sf::Music music;
    float volume;

};
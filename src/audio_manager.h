#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <map>

class AudioManager {
private:
    std::map<std::string, sf::SoundBuffer> soundBuffers;
    std::map<std::string, sf::Sound> sounds;
    std::map<std::string, std::vector<std::string>> soundGroups;
    sf::Music currentMusic;
    float masterVolume;
    float musicVolume;
    bool fadingMusic;
    bool fadingIn;
    float fadeDuration;
    float fadeTimer;

    void loadSoundsFromDirectory(const std::string& directory);

public:
    static AudioManager& get_instance();
    void init();
    void playSound(const std::string& name);
    void playMusic(const std::string& name, bool loop = false, float fadeInDuration = 0.0f);
    void stopMusic(float fadeOutDuration = 0.0f);
    void setMasterVolume(float volume);
    void update(float dt);
};


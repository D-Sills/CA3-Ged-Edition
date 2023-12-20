#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class AudioManager {
public:
    static AudioManager& get_instance();

    void init(); // Modified initialization method
    void playSound(const std::string& name);
    void playMusic(const std::string& name, bool loop = false, float fadeInDuration = 0.0f);
    void stopMusic(float fadeOutDuration = 0.0f);
    void setMasterVolume(float volume);
    void update(float dt); // For handling fade in/out

private:
    AudioManager() = default;
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::unordered_map<std::string, sf::Sound> sounds;
    sf::Music currentMusic;
    float masterVolume;
    float musicVolume; // Separate control for music volume
    bool fadingMusic;
    float fadeDuration;
    float fadeTimer;
    bool fadingIn;

    void loadSoundsFromDirectory(const std::string& directory);
};


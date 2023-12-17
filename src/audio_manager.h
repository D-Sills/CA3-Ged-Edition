#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class AudioManager {
public:
    static AudioManager& get_instance();

    bool loadMusic(const std::string& filename);
    void playMusic();
    void pauseMusic();
    void stopMusic();
    void setMusicVolume(float new_volume);
    float getMusicVolume() const;
    bool isMusicPlaying() const;

    void loadSoundEffect(const std::string& name, const std::string& filename);
    void playSoundEffect(const std::string& name);
    void setSoundEffectVolume(const std::string& name, float volume);
    void setGlobalSoundEffectVolume(float volume);

private:
    AudioManager();
    sf::Music music;
    float musicVolume;
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::unordered_map<std::string, sf::Sound> sounds;
    float globalSoundVolume;
};

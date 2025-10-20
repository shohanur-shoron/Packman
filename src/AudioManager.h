#pragma once

#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "miniaudio.h"
#include <string>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void playMusic(const std::string& filePath, bool loop = true);
    void stopMusic();
    void playSound(const std::string& filePath);
    bool isMusicPlaying() const;
    void playLoopingSound(const std::string& filePath);
    void stopLoopingSound();
    bool isLoopingSoundPlaying() const;
    void playPowerPelletSound(const std::string& filePath);
    void stopPowerPelletSound();
    bool isPowerPelletSoundPlaying() const;

private:
    ma_engine engine;
    ma_sound music;
    bool musicPlaying;
    ma_sound loopingSound;
    bool loopingSoundPlaying;
    ma_sound powerPelletSound;
    bool powerPelletSoundPlaying;
};

#endif // AUDIO_MANAGER_H
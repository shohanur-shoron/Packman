#define MINIAUDIO_IMPLEMENTATION
#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager() : musicPlaying(false), loopingSoundPlaying(false), powerPelletSoundPlaying(false) {
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine." << std::endl;
    }
}

AudioManager::~AudioManager() {
    if (musicPlaying) {
        ma_sound_uninit(&music);
    }
    if (loopingSoundPlaying) {
        ma_sound_uninit(&loopingSound);
    }
    if (powerPelletSoundPlaying) {
        ma_sound_uninit(&powerPelletSound);
    }
    ma_engine_uninit(&engine);
}

void AudioManager::playMusic(const std::string& filePath, bool loop) {
    if (musicPlaying) {
        stopMusic();
    }

    if (ma_sound_init_from_file(&engine, filePath.c_str(), 0, NULL, NULL, &music) != MA_SUCCESS) {
        std::cerr << "Failed to load music file: " << filePath << std::endl;
        return;
    }

    ma_sound_set_looping(&music, loop);
    ma_sound_start(&music);
    musicPlaying = true;
}

void AudioManager::stopMusic() {
    if (musicPlaying) {
        ma_sound_stop(&music);
        ma_sound_uninit(&music);
        musicPlaying = false;
    }
}

void AudioManager::playSound(const std::string& filePath) {
    ma_engine_play_sound(&engine, filePath.c_str(), NULL);
}

bool AudioManager::isMusicPlaying() const {
    return musicPlaying;
}

void AudioManager::playLoopingSound(const std::string& filePath) {
    if (loopingSoundPlaying) {
        stopLoopingSound();
    }

    if (ma_sound_init_from_file(&engine, filePath.c_str(), 0, NULL, NULL, &loopingSound) != MA_SUCCESS) {
        std::cerr << "Failed to load sound file: " << filePath << std::endl;
        return;
    }

    ma_sound_set_looping(&loopingSound, true);
    ma_sound_start(&loopingSound);
    loopingSoundPlaying = true;
}

void AudioManager::stopLoopingSound() {
    if (loopingSoundPlaying) {
        ma_sound_stop(&loopingSound);
        ma_sound_uninit(&loopingSound);
        loopingSoundPlaying = false;
    }
}

bool AudioManager::isLoopingSoundPlaying() const {
    return loopingSoundPlaying;
}

void AudioManager::playPowerPelletSound(const std::string& filePath) {
    if (powerPelletSoundPlaying) {
        stopPowerPelletSound();
    }

    if (ma_sound_init_from_file(&engine, filePath.c_str(), 0, NULL, NULL, &powerPelletSound) != MA_SUCCESS) {
        std::cerr << "Failed to load sound file: " << filePath << std::endl;
        return;
    }

    ma_sound_set_looping(&powerPelletSound, true);
    ma_sound_start(&powerPelletSound);
    powerPelletSoundPlaying = true;
}

void AudioManager::stopPowerPelletSound() {
    if (powerPelletSoundPlaying) {
        ma_sound_stop(&powerPelletSound);
        ma_sound_uninit(&powerPelletSound);
        powerPelletSoundPlaying = false;
    }
}

bool AudioManager::isPowerPelletSoundPlaying() const {
    return powerPelletSoundPlaying;
}
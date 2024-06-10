#include "./ModelH/Option.h"
#include <iostream>

// Initialisation de l'instance singleton à nullptr
Option* Option::instance = nullptr;

// Method to get the singleton instance of Option
Option* Option::getInstance() {
    if (instance == nullptr) {
        instance = new Option();
    }
    return instance;
}

// Constructor
Option::Option() :
    audioDevice(0),
    obtainedSpec(),
    musicBuffer(nullptr),
    musicLength(0),
    musicPaused(false) {
    // Initialize SDL audio
    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec desiredSpec;
    SDL_zero(desiredSpec);
    desiredSpec.freq = 44100;
    desiredSpec.format = AUDIO_F32;
    desiredSpec.channels = 2;
    desiredSpec.samples = 4096;
    desiredSpec.callback = nullptr;

    // Open audio device
    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desiredSpec, &obtainedSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (audioDevice == 0) {
        cerr << "Failed to open audio device: " << SDL_GetError();
    } else {
        SDL_PauseAudioDevice(audioDevice, 0);
    }
}

// Destructor
Option::~Option() {
    // Free audio buffers
    for (auto& pair : audioBuffers) {
        SDL_FreeWAV(pair.second);
    }
    // Free music buffer
    if (musicBuffer) {
        SDL_FreeWAV(musicBuffer);
    }
    // Close audio device and quit SDL audio
    SDL_CloseAudioDevice(audioDevice);
    SDL_Quit();
}

// Method to load music from file
void Option::loadMusic(const std::string& music) {
    if (musicBuffer) {
        SDL_FreeWAV(musicBuffer);
        musicBuffer = nullptr;
    }
    if (SDL_LoadWAV(music.c_str(), &obtainedSpec, &musicBuffer, &musicLength) == nullptr) {
        cerr << "Failed to load music: " << SDL_GetError();
    }
}

// Method to play loaded music
void Option::playMusic() {
    if (musicBuffer) {
        SDL_QueueAudio(audioDevice, musicBuffer, musicLength);
    } else {
        cerr << "Music not loaded";
    }
}

// Method to decrease volume
void Option::decreaseVolume() {
    if (currentVolume > 0) {
        if (currentVolume < 132 / 10) {
            currentVolume = 0;
        } else {
            currentVolume -= 132 / 10;
            SDL_ClearQueuedAudio(audioDevice);
            SDL_MixAudioFormat(nullptr, musicBuffer, obtainedSpec.format, musicLength, currentVolume);
            playMusic();
        }
    }
}

// Method to increase volume
void Option::increaseVolume() {
    if (currentVolume < 132) {
        currentVolume += 132 / 10;
        SDL_ClearQueuedAudio(audioDevice);
        SDL_MixAudioFormat(nullptr, musicBuffer, obtainedSpec.format, musicLength, currentVolume);
        playMusic();
    }
}

// Method to get the current volume level
int Option::getVolume() {
    return currentVolume;
}

// Method to get the current difficulty level
int Option::getDifficulty() {
    return difficulty;
}

// Method to set the difficulty level
void Option::setDifficulty(int newDifficulty) {
    difficulty = newDifficulty;
}

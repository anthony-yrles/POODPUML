#include "./ModelH/Option.h"
#include <iostream>

// Initialisation de l'instance singleton à nullptr
Option* Option::instance = nullptr;

Option* Option::getInstance() {
    if (instance == nullptr) {
        instance = new Option();
    }
    return instance;
}

Option::Option() :
    currentVolume(SDL_MIX_MAXVOLUME),
    musicBuffer(nullptr),
    musicLength(0),
    musicPaused(false),
    audioDevice(0),
    obtainedSpec() {
    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec desiredSpec;
    SDL_zero(desiredSpec);
    desiredSpec.freq = 44100;
    desiredSpec.format = AUDIO_F32;
    desiredSpec.channels = 2;
    desiredSpec.samples = 4096;
    desiredSpec.callback = nullptr;

    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desiredSpec, &obtainedSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if (audioDevice == 0) {
        cerr << "Failed to open audio device: " << SDL_GetError();
    } else {
        SDL_PauseAudioDevice(audioDevice, 0);
    }
}

Option::~Option() {
    for (auto& pair : audioBuffers) {
        SDL_FreeWAV(pair.second);
    }
    if (musicBuffer) {
        SDL_FreeWAV(musicBuffer);
    }
    SDL_CloseAudioDevice(audioDevice);
    SDL_Quit();
}

void Option::loadOptionEffect(const std::string& soundEffect) {
    SDL_AudioSpec spec;
    Uint8* buffer;
    Uint32 length;
    if (SDL_LoadWAV(soundEffect.c_str(), &spec, &buffer, &length) == nullptr) {
        cerr << "Failed to load sound effect: " << SDL_GetError();
        return;
    }
    soundEffects[soundEffect] = spec;
    audioBuffers[soundEffect] = buffer;
    audioLengths[soundEffect] = length;
}

void Option::playOptionEffect(const std::string& soundEffect) {
    auto it = audioBuffers.find(soundEffect);
    if (it != audioBuffers.end()) {
        SDL_QueueAudio(audioDevice, it->second, audioLengths[soundEffect]);
    } else {
        cerr << "Option effect not found: " << soundEffect;
    }
}

void Option::loadMusic(const std::string& music) {
    if (musicBuffer) {
        SDL_FreeWAV(musicBuffer);
        musicBuffer = nullptr;
    }
    if (SDL_LoadWAV(music.c_str(), &obtainedSpec, &musicBuffer, &musicLength) == nullptr) {
        cerr << "Failed to load music: " << SDL_GetError();
    }
}

void Option::playMusic() {
    if (musicBuffer) {
        SDL_QueueAudio(audioDevice, musicBuffer, musicLength);
    } else {
        cerr << "Music not loaded";
    }
}

void Option::decreaseVolume() {
    if (currentVolume > 0) {
        currentVolume -= SDL_MIX_MAXVOLUME / 10;
        SDL_ClearQueuedAudio(audioDevice);
        SDL_MixAudioFormat(nullptr, musicBuffer, obtainedSpec.format, musicLength, currentVolume);
        playMusic();
    }
}

void Option::increaseVolume() {
    if (currentVolume < SDL_MIX_MAXVOLUME) {
        currentVolume += SDL_MIX_MAXVOLUME / 10;
        SDL_ClearQueuedAudio(audioDevice);
        SDL_MixAudioFormat(nullptr, musicBuffer, obtainedSpec.format, musicLength, currentVolume);
        playMusic();
    }
}

int Option::getVolume() {
    cout << "Volume: " << currentVolume << endl;
    return currentVolume;
}

int Option::getDifficulty() {
    return difficulty;
}

void Option::setDifficulty(int newDifficulty) {
    difficulty = newDifficulty;
}
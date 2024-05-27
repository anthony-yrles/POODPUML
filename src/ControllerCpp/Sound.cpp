#include "./ControllerH/Sound.h"

// Initialisation of the singleton instance to nullptr
Sound* Sound::instance = nullptr;

// Private constructor to prevent instancing, initialisation of the audio device and the audio mixer
Sound::Sound() : currentVolume(MIX_MAX_VOLUME) {
    // Initialize the SDL_AudioSpec structure and set the desired audio parameters
    SDL_AudioSpec desiredSpec;
    desiredSpec.freq = 44100;
    desiredSpec.format = AUDIO_S16SYS; // 16 bits audio format
    desiredSpec.channels = 2; // Stéréo
    desiredSpec.samples = 2048; // Size of the audio buffer
    desiredSpec.callback = NULL;
    desiredSpec.userdata = NULL;

    // Open audio peripheric with the desired audio parameters
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &desiredSpec, NULL, 0);
    if (deviceId == 0) {
        printf("SDL could not open audio device! SDL Error: %s\n", SDL_GetError());
        return;
    }

    // Open the audio mixer with the desired audio parameters
    if (Mix_OpenAudio(deviceId, &desiredSpec) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
}

// Destructor to free the memory
Sound::~Sound() {
    for (auto& pair : musics) {
        Mix_FreeMusic(pair.second);
    }
    for (auto& pair : sounds) {
        Mix_FreeChunk(pair.second);
    }
    Mix_CloseAudio();
}

// Méthode to obtain the unique instance of the singleton
Sound* Sound::getInstance() {
    if (instance == nullptr) {
        instance = new Sound();
    }
    return instance;
}

// Loading of a music from the "./assets/music/" folder
void Sound::loadMusic(const string& key, const string& musicPath) {
    string fullPath = "./assets/music/" + musicPath;
    Mix_Music* music = Mix_LoadMUS(fullPath.c_str());
    if (music == nullptr) {
        cout << "Error loading music: " << fullPath << endl;
        return;
    }
    musics[key] = music;
}

// Loadind of a sound from the "./assets/sound/" folder
void Sound::loadSound(const string& key, const string& soundPath) {
    string fullPath = "./assets/sound/" + soundPath;
    Mix_Chunk* sound = Mix_LoadWAV(fullPath.c_str());
    if (sound == nullptr) {
        cout << "Error loading sound: " << fullPath << endl;
        return;
    }
    sounds[key] = sound;
}

// Playing of a music
void Sound::playMusic(const string& key) {
    auto it = musics.find(key);
    if (it != musics.end()) {
        Mix_PlayMusic(it->second, -1);
    } else {
        cout << "Music not found: " << key << endl;
    }
}

// Playing of a sound
void Sound::playSound(const string& key) {
    auto it = sounds.find(key);
    if (it != sounds.end()) {
        Mix_PlayChannel(-1, it->second, 0);
    } else {
        cout << "Sound not found: " << key << endl;
    }
}

// Stop music
void Sound::stopMusic() {
    Mix_HaltMusic();
}

// Stop sound
void Sound::stopSound() {
    Mix_HaltChannel(-1);
}

// Decrease volume
void Sound::volumeDown() {
    if (currentVolume > 0) {
        currentVolume--;
        Mix_VolumeMusic(currentVolume);
    }
}

// Augment volume
void Sound::volumeUp() {
    if (currentVolume < MIX_MAX_VOLUME) {
        currentVolume++;
        Mix_VolumeMusic(currentVolume);
    }
}
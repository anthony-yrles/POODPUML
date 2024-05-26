#include "Sound.h"

// Initialisation of the singleton instance to nullptr
Sound* Sound::instance = nullptr;

// Private constructor
Sound::Sound() : currentVolume(MIX_MAX_VOLUME) {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
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
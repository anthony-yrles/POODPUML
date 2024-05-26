#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <map>
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

class Sound {
private:
    static Sound* instance;
    map<string, Mix_Music*> musics;
    map<string, Mix_Chunk*> sounds;
    int currentVolume;

    Sound(); //  Private constructor to prevent instancing

public:
    static Sound* getInstance(); // Static access method
    void loadMusic(const string& key, const string& musicPath);
    void loadSound(const string& key, const string& soundPath);
    void playMusic(const string& key);
    void playSound(const string& key);
    void stopMusic();
    void stopSound();
    void volumeDown();
    void volumeUp();
    ~Sound();  // Destructor
};

#endif

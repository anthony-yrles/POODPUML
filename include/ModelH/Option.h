#pragma once
#include "VueH/Draw.h"

#include <map>

class Option {
public:
    static Option* getInstance();
    
    void loadMusic(const string& music);
    void playMusic();
    void decreaseVolume();
    void increaseVolume();
    int getVolume();
    int getDifficulty();
    void setDifficulty(int newDifficulty);

    ~Option(); 

private:
    static Option* instance;
    map<string, SDL_AudioSpec> soundEffects;
    map<string, Uint8*> audioBuffers;
    map<string, Uint32> audioLengths;
    SDL_AudioDeviceID audioDevice;
    SDL_AudioSpec obtainedSpec;
    Uint8* musicBuffer;
    Uint32 musicLength;
    int currentVolume;
    int difficulty;
    bool musicPaused;

    Option();
};

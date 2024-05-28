#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <string>

using namespace std;

class Sound {
public:
    static Sound* getInstance();
    
    void loadSoundEffect(const string& soundEffect);
    void playSoundEffect(const string& soundEffect);
    void loadMusic(const string& music);
    void playMusic();
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void decreaseVolume();
    void increaseVolume();
    void getVolume();

    ~Sound();

private:
    static Sound* instance;
    map<string, SDL_AudioSpec> soundEffects;
    map<string, Uint8*> audioBuffers;
    map<string, Uint32> audioLengths;
    SDL_AudioDeviceID audioDevice;
    SDL_AudioSpec obtainedSpec;
    Uint8* musicBuffer;
    Uint32 musicLength;
    int currentVolume;
    bool musicPaused;

    Sound();
};

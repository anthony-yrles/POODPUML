#pragma once

#include "VueH/Draw.h" // Including necessary header file(s)

#include <map>

// Option class declaration
class Option {
public:
    // Method to get the singleton instance of Option
    static Option* getInstance();
    
    // Method to load music from file
    void loadMusic(const string& music);
    
    // Method to play loaded music
    void playMusic();
    
    // Method to decrease volume
    void decreaseVolume();
    
    // Method to increase volume
    void increaseVolume();
    
    // Method to get the current volume level
    int getVolume();
    
    // Method to get the current difficulty level
    int getDifficulty();
    
    // Method to set the difficulty level
    void setDifficulty(int newDifficulty);

    // Destructor
    ~Option(); 

private:
    static Option* instance; // Static member to hold the singleton instance
    map<string, SDL_AudioSpec> soundEffects; // Map to hold sound effect data
    map<string, Uint8*> audioBuffers; // Map to hold audio buffers
    map<string, Uint32> audioLengths; // Map to hold audio lengths
    SDL_AudioDeviceID audioDevice; // SDL audio device ID
    SDL_AudioSpec obtainedSpec; // SDL audio specification
    Uint8* musicBuffer; // Buffer for music data
    Uint32 musicLength; // Length of music data
    int currentVolume = 132; // Current volume level
    int difficulty = 5; // Current difficulty level
    bool musicPaused; // Flag to indicate whether music is paused

    // Private constructor to prevent instantiation
    Option();
};

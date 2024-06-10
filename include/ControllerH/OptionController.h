#pragma once

#include "./ModelH/Option.h"

class OptionController {
public:
    // Constructor
    OptionController();
    // Destructor
    ~OptionController();
    
    // Load music file
    void loadMusic(const string& music);
    // Play loaded music
    void playMusic();
    // Decrease volume
    void decreaseVolume();
    // Increase volume
    void increaseVolume();
    // Get current volume level
    int getVolume();
    // Get current difficulty level
    int getDifficulty();
    // Set new difficulty level
    void setDifficulty(int newDifficulty);

private:
    Option* options; // Pointer to Option object
};
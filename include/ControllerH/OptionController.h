#pragma once

#include "./ModelH/Option.h"

class OptionController {
public:
    OptionController();
    ~OptionController();
    
    void loadMusic(const string& music);
    void playMusic();
    void decreaseVolume();
    void increaseVolume();
    int getVolume();
    int getDifficulty();
    void setDifficulty(int newDifficulty);

private:
    Option* options;
};
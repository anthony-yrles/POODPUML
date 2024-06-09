#pragma once

#include "./ModelH/Option.h"

class OptionController {
public:
    OptionController();
    ~OptionController();
    
    void loadOptionEffect(const string& soundEffect);
    void playOptionEffect(const string& soundEffect);
    void loadMusic(const string& music);
    void playMusic();
    void stopMusic();
    void decreaseVolume();
    void increaseVolume();
    int getVolume();
    int getDifficulty();
    void setDifficulty(int newDifficulty);

private:
    Option* options;
};
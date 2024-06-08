#pragma once

#include "./ModelH/HallOfFame.h"

class HofController {
public:
    HofController();
    ~HofController();

    void readTxtFile();
    void writeTxtFile();
    void sortDataByDifficulty(int levelReceived);
private:
    HallOfFame hallOfFame;
};
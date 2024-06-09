#pragma once
#include "./ModelH/Observable.h"
#include "./ModelH/Observer.h"

#include "./ModelH/HallOfFame.h"

class HofController : public Observable, public Observer{
public:
    HofController();
    ~HofController();

    void readTxtFile();
    void writeTxtFile(const string& newName, const string& newDifficulty, const string& newLevel);
    void sortDataByDifficulty(int difficultyReceived);
    void topThreeSortedData(int difficultyReceived);
    vector<Data> getSortedDataFoh() const;
    void update() override;

private:
    HallOfFame hallOfFame;
};
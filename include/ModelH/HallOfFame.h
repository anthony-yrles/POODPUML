#pragma once
#include "./ModelH/Observable.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Data {
    string name;
    string difficulty;
    string level;
};

class HallOfFame : public Observable{
public:
    HallOfFame();
    ~HallOfFame();

    void readTxtFile();
    void writeTxtFile(const string& newName, const string& newDifficulty, const string& newLevel);
    void addData(const string& name, const string& difficulty, const string& level);
    void sortDataByDifficulty(int difficultyReceived);
    void topThreeSortedData(int difficultyReceived);
    vector<Data> getSortedData() const;
    

private:
    vector<Data> data;
    vector<Data> sortedData;
};
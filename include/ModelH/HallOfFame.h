#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class HallOfFame {
public:
    HallOfFame();
    ~HallOfFame();

    void readTxtFile();
    void writeTxtFile();
    void addData(const string& name, const string& difficulty, const string& level);
    void sortDataByDifficulty(int levelReceived);
    

private:
    struct Data {
        string name;
        string difficulty;
        string level;
    };
    vector<Data> data;
    vector<Data> sortedData;
};
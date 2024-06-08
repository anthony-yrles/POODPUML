#include "./ModelH/HallOfFame.h"

HallOfFame::HallOfFame() {}

HallOfFame::~HallOfFame() {}

void HallOfFame::readTxtFile() {
    ifstream file("HallOfFame.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name, difficulty, level;
        iss >> name >> difficulty >> level;
        addData(name, difficulty, level);
    }
    file.close();
}

void HallOfFame::writeTxtFile() {
    ofstream file("HallOfFame.txt");
    for (const auto& d : data) {
        file << d.name << " " << d.difficulty << " " << d.level << endl;
    }
    file.close();
}

void HallOfFame::addData(const string& name, const string& difficulty, const string& level) {
    data.push_back({name, difficulty, level});
}

void HallOfFame::sortDataByDifficulty(int difficultyReceived) {

    string difficultyStr = to_string(difficultyReceived);
    sortedData.clear();

    for (const auto& d : data) {
        if (d.difficulty == difficultyStr) {
            sortedData.push_back(d);
        }
    }
}
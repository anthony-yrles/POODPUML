#include "./ModelH/HallOfFame.h"

HallOfFame::HallOfFame() {}

HallOfFame::~HallOfFame() {}

void HallOfFame::readTxtFile() {
    ifstream file("HallOfFame.txt");
    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier HallOfFame.txt";
        return;
    }
    string line;
    while (std::getline(file, line)) {
        istringstream iss(line);
        string name, difficulty, level;
        if (!(iss >> name >> difficulty >> level)) {
            cerr << "Erreur de format dans le fichier HallOfFame.txt";
            continue;
        }
        addData(name, difficulty, level);
    }
    file.close();
}

void HallOfFame::writeTxtFile(const string& newName, const string& newDifficulty, const string& newLevel) {
    ofstream file("HallOfFame.txt", std::ios::app);

    if (!file.is_open()) {
        cerr << "Erreur : impossible d'ouvrir le fichier HallOfFame.txt pour l'écriture";
        return;
    }

    file << newName << " " << newDifficulty << " " << newLevel << endl;
    file.close();

    notifyObservers();
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

void HallOfFame::topThreeSortedData(int difficultyReceived) {
    sortDataByDifficulty(difficultyReceived);
    sort(sortedData.begin(), sortedData.end(), [](const Data& a, const Data& b) {
        return stoi(a.level) > stoi(b.level);
    });

    if (sortedData.size() > 3) {
        sortedData.resize(3);
    }
}

vector<Data> HallOfFame::getSortedData() const {
    return sortedData;
}
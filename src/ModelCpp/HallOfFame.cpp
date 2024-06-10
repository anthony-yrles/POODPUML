#include "./ModelH/HallOfFame.h"

/**
 * @brief Constructs a HallOfFame object.
 */
HallOfFame::HallOfFame() {}

/**
 * @brief Destructor for the HallOfFame class.
 */
HallOfFame::~HallOfFame() {}

/**
 * @brief Reads data from the HallOfFame.txt file.
 *
 * This function reads the content of HallOfFame.txt and adds each entry to the data vector.
 */
void HallOfFame::readTxtFile() {
    ifstream file("HallOfFame.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open HallOfFame.txt";
        return;
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name, difficulty, level;
        if (!(iss >> name >> difficulty >> level)) {
            cerr << "Format error in HallOfFame.txt";
            continue;
        }
        addData(name, difficulty, level);
    }
    file.close();
}

/**
 * @brief Writes a new entry to the HallOfFame.txt file.
 * @param newName Name of the player.
 * @param newDifficulty Difficulty level of the game.
 * @param newLevel Level of the player.
 *
 * This function appends a new entry to the HallOfFame.txt file and notifies observers.
 */
void HallOfFame::writeTxtFile(const string& newName, const string& newDifficulty, const string& newLevel) {
    ofstream file("HallOfFame.txt", ios::app);

    if (!file.is_open()) {
        cerr << "Error: Unable to open HallOfFame.txt for writing";
        return;
    }

    file << newName << " " << newDifficulty << " " << newLevel << endl;
    file.close();

    notifyObservers();
}

/**
 * @brief Adds a new entry to the data vector.
 * @param name Name of the player.
 * @param difficulty Difficulty level of the game.
 * @param level Level of the player.
 */
void HallOfFame::addData(const string& name, const string& difficulty, const string& level) {
    data.push_back({name, difficulty, level});
}

/**
 * @brief Sorts data by the specified difficulty.
 * @param difficultyReceived Difficulty level to filter data by.
 *
 * This function filters entries by the specified difficulty and stores the result in sortedData.
 */
void HallOfFame::sortDataByDifficulty(int difficultyReceived) {
    string difficultyStr = to_string(difficultyReceived);
    sortedData.clear();

    for (const auto& d : data) {
        if (d.difficulty == difficultyStr) {
            sortedData.push_back(d);
        }
    }
}

/**
 * @brief Retrieves the top three entries sorted by level for a specified difficulty.
 * @param difficultyReceived Difficulty level to filter data by.
 *
 * This function sorts entries by the specified difficulty and retrieves the top three entries.
 */
void HallOfFame::topThreeSortedData(int difficultyReceived) {
    sortDataByDifficulty(difficultyReceived);
    sort(sortedData.begin(), sortedData.end(), [](const Data& a, const Data& b) {
        return stoi(a.level) > stoi(b.level);
    });

    if (sortedData.size() > 3) {
        sortedData.resize(3);
    }
}

/**
 * @brief Gets the sorted data.
 * @return Vector of sorted Data.
 */
vector<Data> HallOfFame::getSortedData() const {
    return sortedData;
}

#pragma once
#include "./ModelH/Observable.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * @struct Data
 * @brief Represents an entry in the Hall of Fame.
 *
 * The Data structure holds the name, difficulty, and level of a player.
 */
struct Data {
    string name;       ///< Player's name.
    string difficulty; ///< Difficulty level of the game.
    string level;      ///< Player's level.
};

/**
 * @class HallOfFame
 * @brief Manages the Hall of Fame for the game.
 *
 * The HallOfFame class provides functionalities to read from and write to a
 * text file, add new entries, sort data by difficulty, and retrieve the top
 * three entries for a specific difficulty.
 */
class HallOfFame : public Observable {
public:
    /**
     * @brief Constructs a HallOfFame object.
     */
    HallOfFame();

    /**
     * @brief Destructor for the HallOfFame class.
     */
    ~HallOfFame();

    /**
     * @brief Reads data from the HallOfFame.txt file.
     *
     * This function reads the content of HallOfFame.txt and adds each entry to the data vector.
     */
    void readTxtFile();

    /**
     * @brief Writes a new entry to the HallOfFame.txt file.
     * @param newName Name of the player.
     * @param newDifficulty Difficulty level of the game.
     * @param newLevel Level of the player.
     *
     * This function appends a new entry to the HallOfFame.txt file and notifies observers.
     */
    void writeTxtFile(const string& newName, const string& newDifficulty, const string& newLevel);

    /**
     * @brief Adds a new entry to the data vector.
     * @param name Name of the player.
     * @param difficulty Difficulty level of the game.
     * @param level Level of the player.
     */
    void addData(const string& name, const string& difficulty, const string& level);

    /**
     * @brief Sorts data by the specified difficulty.
     * @param difficultyReceived Difficulty level to filter data by.
     *
     * This function filters entries by the specified difficulty and stores the result in sortedData.
     */
    void sortDataByDifficulty(int difficultyReceived);

    /**
     * @brief Retrieves the top three entries sorted by level for a specified difficulty.
     * @param difficultyReceived Difficulty level to filter data by.
     *
     * This function sorts entries by the specified difficulty and retrieves the top three entries.
     */
    void topThreeSortedData(int difficultyReceived);

    /**
     * @brief Gets the sorted data.
     * @return Vector of sorted Data.
     */
    vector<Data> getSortedData() const;

private:
    vector<Data> data;       ///< Vector holding all data entries.
    vector<Data> sortedData; ///< Vector holding sorted data entries.
};
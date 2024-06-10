#include "./ControllerH/HofController.h"

// Constructor
HofController::HofController() {
    hallOfFame.addObserver(this); // Add this instance as an observer to the HallOfFame
}

// Destructor
HofController::~HofController() {
    hallOfFame.removeObserver(this); // Remove this instance as an observer from the HallOfFame
}

// Method to read data from a text file
void HofController::readTxtFile() {
    hallOfFame.readTxtFile();
}

// Method to write data to a text file
void HofController::writeTxtFile(const string& newName, const string& newDifficulty, const string& newLevel) {
    hallOfFame.writeTxtFile(newName, newDifficulty, newLevel);
}

// Method to sort data by difficulty level
void HofController::sortDataByDifficulty(int difficultyReceived) {
    hallOfFame.sortDataByDifficulty(difficultyReceived);
}

// Method to get the top three sorted data
void HofController::topThreeSortedData(int difficultyReceived) {
    hallOfFame.topThreeSortedData(difficultyReceived);
}

// Method to get sorted data from HallOfFame
vector<Data> HofController::getSortedDataFoh() const {
    return hallOfFame.getSortedData();
}

// Observer update method
void HofController::update() {
    notifyObservers(); // Notify observers when there's an update
}
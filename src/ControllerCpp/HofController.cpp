#include "./ControllerH/HofController.h"

HofController::HofController() {
    hallOfFame.addObserver(this);
}

HofController::~HofController() {
    hallOfFame.removeObserver(this);
}

void HofController::readTxtFile() {
    hallOfFame.readTxtFile();
}
void HofController::writeTxtFile(const string& newName, const string& newDifficulty, const string& newLevel) {
    cout << "HofController::writeTxtFile" << endl;
    hallOfFame.writeTxtFile(newName, newDifficulty, newLevel);
}
void HofController::sortDataByDifficulty(int difficultyReceived) {
    hallOfFame.sortDataByDifficulty(difficultyReceived);
}
vector<Data> HofController::getSortedDataFoh() const {
    return hallOfFame.getSortedData();
}
void HofController::update() {
    notifyObservers();
}
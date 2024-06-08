#include "./ControllerH/HofController.h"

HofController::HofController() {}

HofController::~HofController() {}

void HofController::readTxtFile() {
    hallOfFame.readTxtFile();
}
void HofController::writeTxtFile() {
    hallOfFame.writeTxtFile();
}
void HofController::sortDataByDifficulty(int levelReceived) {
    hallOfFame.sortDataByDifficulty(levelReceived);
}
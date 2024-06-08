#include "./ControllerH/HofController.h"

HofController::HofController() {}

HofController::~HofController() {}

void HofController::readTxtFile() {
    HallOfFame hallOfFame;
    hallOfFame.readTxtFile();
}
void HofController::writeTxtFile() {
    HallOfFame hallOfFame;
    hallOfFame.writeTxtFile();
}
void HofController::sortDataByDifficulty(int levelReceived) {
    HallOfFame hallOfFame;
    hallOfFame.sortDataByDifficulty(levelReceived);
}
#include "./ControllerH/OptionController.h"
#include <iostream>

OptionController::OptionController() {
    options = Option::getInstance();
}

OptionController::~OptionController() {}

void OptionController::loadMusic(const std::string& music) {
    options->loadMusic(music);
}
void OptionController::playMusic() {
    options->playMusic();
}
void OptionController::decreaseVolume() {
    options->decreaseVolume();
}
void OptionController::increaseVolume() {
    options->increaseVolume();
}
int OptionController::getVolume() {
    return options->getVolume();
}
int OptionController::getDifficulty() {
    return options->getDifficulty();
}
void OptionController::setDifficulty(int newDifficulty) {
    options->setDifficulty(newDifficulty);
}
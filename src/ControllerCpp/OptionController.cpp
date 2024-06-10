#include "./ControllerH/OptionController.h"
#include <iostream>

// Constructor
OptionController::OptionController() {
    options = Option::getInstance(); // Get instance of Option object
}

// Destructor
OptionController::~OptionController() {}

// Load music file
void OptionController::loadMusic(const std::string& music) {
    options->loadMusic(music);
}

// Play loaded music
void OptionController::playMusic() {
    options->playMusic();
}

// Decrease volume
void OptionController::decreaseVolume() {
    options->decreaseVolume();
}

// Increase volume
void OptionController::increaseVolume() {
    options->increaseVolume();
}

// Get current volume level
int OptionController::getVolume() {
    return options->getVolume();
}

// Get current difficulty level
int OptionController::getDifficulty() {
    return options->getDifficulty();
}

// Set new difficulty level
void OptionController::setDifficulty(int newDifficulty) {
    options->setDifficulty(newDifficulty);
}
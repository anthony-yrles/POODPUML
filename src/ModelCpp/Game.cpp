#include "./ModelH/Game.h"

Game::Game(int level, int difficulty) : level(level), difficulty(difficulty) {}

Game::~Game() {}

int Game::getLevel() const {
    return level;
}
void Game::setLevel(int level) {
    this->level = level;
}

int Game::getDifficulty() const {
    return difficulty;
}
void Game::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
}

int Game::getTotalEnemies() const {
    return totalEnemies;
}
void Game::setTotalEnemies(int totalEnemies) {
    this->totalEnemies = totalEnemies;
}

int Game::getGold() const {
    return gold;
}
void Game::setGold(int gold) {
    this->gold = gold;
}

int Game::getCost() const {
    return cost;
}
void Game::setCost(int cost) {
    this->cost = cost;
}

int Game::getGameLifePoints() const {
    return gameLifePoints;
}
void Game::setGameLifePoints(int gameLifePoints) {
    this->gameLifePoints = gameLifePoints;
}

int Game::getEnemyGoldEarned() const {
    return enemyGoldEarned;
}
void Game::setEnemyGoldEarned(int enemyGoldEarned) {
    this->enemyGoldEarned = enemyGoldEarned;
}

void Game::attributesChangedByLevelAndDifficulty() {
    gameLifePoints -= difficulty;

    float multipliers[] = {0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4};

    if (difficulty >= 1 && difficulty <= 9) {
        float multiplier = multipliers[difficulty - 1];
        float inverseMultiplier = 1 / multiplier;
        
        totalEnemies *= multiplier * (level / 10 + 1);
        gold = gold * inverseMultiplier + 200;
        cost *= multiplier;
        enemyGoldEarned *= multiplier;
    }
}

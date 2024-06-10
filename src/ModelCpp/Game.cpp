#include "./ModelH/Game.h"

/**
 * @brief Constructs a Game object with the specified level.
 * @param level Initial level of the game.
 */
Game::Game(int level) : level(level) {}

/**
 * @brief Destructor for the Game class.
 */
Game::~Game() {}

/**
 * @brief Gets the current level of the game.
 * @return Current level of the game.
 */
int Game::getLevel() const {
    return level;
}

/**
 * @brief Sets the level of the game.
 * @param level New level of the game.
 */
void Game::setLevel(int level) {
    this->level = level;
}

/**
 * @brief Gets the total number of enemies.
 * @return Total number of enemies.
 */
int Game::getTotalEnemies() const {
    return totalEnemies;
}

/**
 * @brief Sets the total number of enemies.
 * @param totalEnemies New total number of enemies.
 */
void Game::setTotalEnemies(int totalEnemies) {
    this->totalEnemies = totalEnemies;
}

/**
 * @brief Gets the current amount of gold.
 * @return Current amount of gold.
 */
int Game::getGold() const {
    return gold;
}

/**
 * @brief Sets the amount of gold.
 * @param gold New amount of gold.
 */
void Game::setGold(int gold) {
    this->gold = gold;
}

/**
 * @brief Gets the cost of something in the game.
 * @return Cost of something in the game.
 */
int Game::getCost() const {
    return cost;
}

/**
 * @brief Sets the cost of something in the game.
 * @param cost New cost of something in the game.
 */
void Game::setCost(int cost) {
    this->cost = cost;
}

/**
 * @brief Gets the game's life points.
 * @return Game's life points.
 */
int Game::getGameLifePoints() const {
    return gameLifePoints;
}

/**
 * @brief Sets the game's life points.
 * @param gameLifePoints New game life points.
 */
void Game::setGameLifePoints(int gameLifePoints) {
    this->gameLifePoints = gameLifePoints;
}

/**
 * @brief Gets the amount of gold earned per enemy.
 * @return Amount of gold earned per enemy.
 */
int Game::getEnemyGoldEarned() const {
    return enemyGoldEarned;
}

/**
 * @brief Sets the amount of gold earned per enemy.
 * @param enemyGoldEarned New amount of gold earned per enemy.
 */
void Game::setEnemyGoldEarned(int enemyGoldEarned) {
    this->enemyGoldEarned = enemyGoldEarned;
}

/**
 * @brief Adjusts game attributes based on the level and difficulty.
 * @param difficulty Difficulty level affecting the game attributes.
 */
void Game::attributesChangedByLevelAndDifficulty(int difficulty) {
    gameLifePoints -= difficulty;

    float multipliers[] = {0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4};

    if (difficulty >= 1 && difficulty <= 9) {
        float multiplier = multipliers[difficulty - 1];
        float inverseMultiplier = 1 / multiplier;
        
        totalEnemies *= multiplier * (level / 10 + 1);
        gold *= inverseMultiplier;
        cost *= multiplier;
        enemyGoldEarned *= inverseMultiplier;
        if (gold < cost) {
            gold = cost;
        }
    }
}

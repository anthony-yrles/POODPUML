#pragma once
#include <iostream>

using namespace std;

/**
 * @class Game
 * @brief Represents the game state and its attributes.
 *
 * The Game class manages the level, total enemies, gold, cost, life points,
 * and the gold earned per enemy. It provides methods to adjust these attributes
 * based on the level and difficulty of the game.
 */
class Game {
public:
    /**
     * @brief Constructs a Game object with the specified level.
     * @param level Initial level of the game.
     */
    Game(int level);

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

    /**
     * @brief Gets the current level of the game.
     * @return Current level of the game.
     */
    int getLevel() const;

    /**
     * @brief Sets the level of the game.
     * @param level New level of the game.
     */
    void setLevel(int level);

    /**
     * @brief Gets the total number of enemies.
     * @return Total number of enemies.
     */
    int getTotalEnemies() const;

    /**
     * @brief Sets the total number of enemies.
     * @param totalEnemies New total number of enemies.
     */
    void setTotalEnemies(int totalEnemies);

    /**
     * @brief Gets the current amount of gold.
     * @return Current amount of gold.
     */
    int getGold() const;

    /**
     * @brief Sets the amount of gold.
     * @param gold New amount of gold.
     */
    void setGold(int gold);

    /**
     * @brief Gets the cost of something in the game.
     * @return Cost of something in the game.
     */
    int getCost() const;

    /**
     * @brief Sets the cost of something in the game.
     * @param cost New cost of something in the game.
     */
    void setCost(int cost);

    /**
     * @brief Gets the game's life points.
     * @return Game's life points.
     */
    int getGameLifePoints() const;

    /**
     * @brief Sets the game's life points.
     * @param gameLifePoints New game life points.
     */
    void setGameLifePoints(int gameLifePoints);

    /**
     * @brief Gets the amount of gold earned per enemy.
     * @return Amount of gold earned per enemy.
     */
    int getEnemyGoldEarned() const;

    /**
     * @brief Sets the amount of gold earned per enemy.
     * @param enemyGoldEarned New amount of gold earned per enemy.
     */
    void setEnemyGoldEarned(int enemyGoldEarned);

    /**
     * @brief Adjusts game attributes based on the level and difficulty.
     * @param difficulty Difficulty level affecting the game attributes.
     */
    void attributesChangedByLevelAndDifficulty(int difficulty);

private:
    int level; ///< Current level of the game.
    int totalEnemies = 20; ///< Total number of enemies.
    int gold = 500; ///< Current amount of gold.
    int cost = 350; ///< Cost of something in the game.
    int gameLifePoints = 10; ///< Game's life points.
    int enemyGoldEarned = 50; ///< Amount of gold earned per enemy.
};

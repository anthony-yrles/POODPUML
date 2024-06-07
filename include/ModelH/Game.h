#pragma once
#include <iostream>

using namespace std;

class Game {
public:
    Game(int level, int difficulty);
    ~Game();

    int getLevel() const;
    void setLevel(int level);

    int getDifficulty() const;
    void setDifficulty(int difficulty);

    int getTotalEnemies() const;
    void setTotalEnemies(int totalEnemies);

    int getGold() const;
    void setGold(int gold);

    int getCost() const;
    void setCost(int cost);


    int getGameLifePoints() const;
    void setGameLifePoints(int gameLifePoints);

    int getEnemyGoldEarned() const;
    void setEnemyGoldEarned(int enemyGoldEarned);

    void attributesChangedByLevelAndDifficulty();

private:
    int level;
    int difficulty;
    int totalEnemies = 20;
    int gold = 500;
    int cost = 350;
    int gameLifePoints = 10;
    int enemyGoldEarned = 50;
};
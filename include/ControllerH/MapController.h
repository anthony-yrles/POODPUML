#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include "./ModelH/Observable.h"
#include "./ModelH/Map.h"
#include "./ModelH/Enemy.h"
#include "./ModelH/Tower.h"
#include "./ModelH/Game.h"
#include "./VueH/Draw.h"
#include "./ControllerH/OptionController.h"

using namespace std::chrono;

class MapController {
public:
    MapController();
    ~MapController();

    int getBeginX() const {
        return beginX;
    }
    void setBeginX(int beginX) {
        this->beginX = beginX;
    }
    int getBeginY() const {
        return beginY;
    }
    void setBeginY(int beginY) {
        this->beginY = beginY;
    }

    int getTileWidth() const {
        return tileWidth;
    }
    void setTileWidth(int tileWidth) {
        this->tileWidth = tileWidth;
    }
    int getTileHeight() const {
        return tileHeight;
    }
    void setTileHeight(int tileHeight) {
        this->tileHeight = tileHeight;
    }

    vector<vector<Tile>> createAndReturnMap(const string& filename, Map* map);
    void tileSize(int WIDTH, int HEIGHT, int filewidth, int fileheight);
    bool spawnTime();
    bool fireTime();
    vector<pair<int, int>> searchForWayPoints(Map* map);
    void spawnAndMoveEnemy(Map *map, const string& filename, int width, int height, int life, int maxLife, int speed, SDL_Renderer* renderer, const char* image, Draw* draw);
    void spawnTower(int damage, int range, int fireSpeed, int numberOfFire, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image, Draw* draw);
    void fireTowers(vector<Enemy*> enemies);
    vector<Tower*> getTowers() const;
    void clearTowers();
    vector<Enemy*> getEnemies() const;
    void clearEnemies();
    void setGamesAttributes(int level, int difficulty);
    int getLevelGame() const;
    void setLevelGame(int levelGame);
    int getTotalEnemiesGame() const;
    void setTotalEnemiesGame(int totalEnemiesGame);
    int getTotalEnemiesKilled() const;
    void setTotalEnemiesKilled(int totalEnemiesKilled);
    int getGoldGames() const;
    void setGoldGames(int goldGames);
    int getCostGames() const;
    void setCostGames(int costGames);
    int getGameLifePointsGames() const;
    void setGameLifePointsGames(int gameLifePointsGames);
    int getEnemyGoldEarnedGames() const;
    void setEnemyGoldEarnedGames(int enemyGoldEarnedGames);
    int getEnemyCreated() const;
    void setEnemyCreated(int enemyCreated);
    bool getOptionValidate() const;
    void setOptionValidate(bool optionValidate);

private:
    vector<Enemy*> enemies;
    vector<Tower*> towers;
    int beginX, beginY;
    int tileWidth, tileHeight;
    int enemyCreated = 0;
    int levelGame = 1; 
    int difficultyGame = 5; 
    int totalEnemiesGame, totalEnemiesKilled, goldGames, costGames, gameLifePointsGames, enemyGoldEarnedGames;
    bool allEnemiesCreated = false;
    bool optionValidate = false;
    long long int lastSpawnTime = 0;
    long long int spawnInterval = 3000;
    long long int lastFireTime = 0;
    long long int fireInterval = 3000;
};

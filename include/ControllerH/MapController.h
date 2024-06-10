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

// MapController class declaration
class MapController {
public:
    // Constructor and destructor
    MapController();
    ~MapController();

    // Getter and setter for beginX
    int getBeginX() const {
        return beginX;
    }
    void setBeginX(int beginX) {
        this->beginX = beginX;
    }

    // Getter and setter for beginY
    int getBeginY() const {
        return beginY;
    }
    void setBeginY(int beginY) {
        this->beginY = beginY;
    }

    // Getter and setter for tileWidth
    int getTileWidth() const {
        return tileWidth;
    }
    void setTileWidth(int tileWidth) {
        this->tileWidth = tileWidth;
    }

    // Getter and setter for tileHeight
    int getTileHeight() const {
        return tileHeight;
    }
    void setTileHeight(int tileHeight) {
        this->tileHeight = tileHeight;
    }

    // Method to create and return a map
    vector<vector<Tile>> createAndReturnMap(const string& filename, Map* map);

    // Method to set tile size
    void tileSize(int WIDTH, int HEIGHT, int filewidth, int fileheight);

    // Method to determine if it's time to spawn enemies
    bool spawnTime();

    // Method to determine if it's time to fire towers
    bool fireTime();

    // Method to search for waypoints on the map
    vector<pair<int, int>> searchForWayPoints(Map* map);

    // Method to spawn and move enemies
    void spawnAndMoveEnemy(Map *map, const string& filename, int width, int height, int life, int maxLife, int speed, SDL_Renderer* renderer, const char* image, Draw* draw);

    // Method to spawn a tower
    void spawnTower(int damage, int range, int fireSpeed, int numberOfFire, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image, Draw* draw);

    // Method to fire towers at enemies
    void fireTowers(vector<Enemy*> enemies);

    // Getter for towers
    vector<Tower*> getTowers() const;

    // Method to clear towers
    void clearTowers();

    // Getter for enemies
    vector<Enemy*> getEnemies() const;

    // Method to clear enemies
    void clearEnemies();

    // Methods to set and get game attributes
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
    vector<Enemy*> enemies; // Vector to store enemies
    vector<Tower*> towers; // Vector to store towers
    int beginX, beginY; // Coordinates of the starting point
    int tileWidth, tileHeight; // Size of tiles
    int enemyCreated = 0; // Number of enemies created
    int levelGame = 2; // Level of the game
    int difficultyGame = 5; // Difficulty level of the game
    int totalEnemiesGame, totalEnemiesKilled, goldGames, costGames, gameLifePointsGames, enemyGoldEarnedGames; // Game attributes
    bool allEnemiesCreated = false; // Flag indicating if all enemies have been created
    bool optionValidate = false; // Flag indicating if game options are validated
    long long int lastSpawnTime = 0; // Time of last enemy spawn
    long long int spawnInterval = 3000; // Time interval between enemy spawns
    long long int lastFireTime = 0; // Time of last tower fire
    long long int fireInterval = 3000; // Time interval between tower fires
};
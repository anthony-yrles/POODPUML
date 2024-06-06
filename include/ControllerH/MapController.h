#pragma once
#include <chrono>
#include <thread>
#include <vector>
#include "./ModelH/Observable.h"
#include "./ModelH/Map.h"
#include "./ModelH/Enemy.h"

using namespace std::chrono;

class MapController : public Observable {
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

    bool spawnTime();
    void spawnAndMoveEnemy(Map *map, const string& filename, int width, int height, int numberEnemy, int life, int speed, SDL_Renderer* renderer, const char* image, Draw* draw);
    vector<vector<Tile>> createAndReturnMap(const string& filename, Map* map);
    void tileSize(int WIDTH, int HEIGHT, int filewidth, int fileheight);
    vector<pair<int, int>> searchForWayPoints(Map* map);

private:
    vector<Enemy*> enemies;
    int beginX, beginY;
    int tileWidth, tileHeight;
    bool allEnemiesCreated = false;
    long long int lastSpawnTime = 0;
    long long int spawnInterval = 10000;
};

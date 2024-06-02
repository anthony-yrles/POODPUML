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

    void createEnemy(int life, int speed, int startX, int startY, int numberEnemy, SDL_Renderer* renderer, int x, int y, int width, int height, const char* image);
    Enemy *getEnemy(size_t index);
    bool spawnTime();
    void enemiesMovement(const string& filename, Map* map, int beginX, int beginY, int tileWidth, int tileHeight);
    vector<vector<Tile>> createAndReturnMap(const std::string& filename, Map* map);

private:
    vector<Enemy*> enemies;
    bool allEnemiesCreated = false;
    long long int lastSpawnTime = 0;
    long long int spawnInterval = 2000;
};

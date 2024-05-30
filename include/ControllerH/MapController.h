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

    void createEnemy(int life, int speed, int startX, int startY, int numberEnemy);
    bool spawnTime();
    vector<vector<Tile>> createAndReturnMap(const std::string& filename, Map* map);

private:
    vector<Enemy*> enemies;
    long long int lastSpawnTime = 0;
    long long int spawnInterval = 2000;
    bool allEnemiesCreated = false;
};

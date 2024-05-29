#pragma once
#include <chrono>
#include "./ModelH/Observable.h"
#include "./ModelH/Map.h"
#include "./ModelH/Enemy.h"

class MapController : Observable {
public:
    MapController();
    ~MapController();

    void createEnemy(int life, int speed, int startX, int startY);
    void addEnemyToList(Enemy* enemy, int enemyNumber, int life, int speed, int startX, int startY);
    void enemySpawn(Map* map, long long int spawnCountDown, vector<Enemy*> enemies);
    vector<vector<Tile>> createAndReturnMap(const std::string& filename, Map* map);

private:
    vector<Enemy*> enemies;
};

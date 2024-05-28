#pragma once
#include "./ModelH/Observer.h"
#include "./ModelH/Map.h"
#include "./ModelH/Enemy.h"
#include "./ModelH/Tower.h"
#include "./ModelH/Castle.h"

class MapController : Observer {
public:
    MapController(long int spawnTime, int spawnNumber, vector<Enemy*> enemies, vector<Tower*> towers);
    ~MapController();

    void startGame();
    void initializeMap();
    void createEnemy();
    void enemySpawn();
    void destroyEnemy();
    void createTower();
    void upgradeTower();
    void towerAttack();
    void victory();
    void defeat();

private:
};
#include "./ControllerH/MapController.h"

MapController::MapController() {}

MapController::~MapController() {}

void MapController::createEnemy(int life, int speed, int startX, int startY) {
    Enemy enemy(life, speed, startX, startY);
}

void MapController::addEnemyToList(Enemy* enemy, int enemyNumber, int life, int speed, int startX, int startY) {
    for (int i = 0; i < enemyNumber; i++) {
        createEnemy(life, speed, startX, startY);
        enemies.push_back(enemy);
    }
}

void MapController::enemySpawn(Map* map, long long int spawnCountDown, vector<Enemy*> enemies) {
    int timer = 0;
    int enemySpawned = 0;
    while (enemies.size() > 0) {
        if (timer == spawnCountDown) {
            enemies.pop_back();
            timer = 0;
        }
        timer++;
    }
}

vector<vector<Tile>> MapController::createAndReturnMap(const std::string& filename, Map* map) {

    map->createMap(filename);

    // Retournez toutes les tuiles de la carte
    vector<vector<Tile>> tiles = map->getTiles();

    return tiles;
}

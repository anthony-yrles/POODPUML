#include "./ControllerH/MapController.h"

MapController::MapController() {}

MapController::~MapController() {
    for (auto enemy : enemies) {
        delete enemy;
    }
}

void MapController::createEnemy(int life, int speed, int startX, int startY, int numberEnemy) {
    if (!allEnemiesCreated) {
        for (int i = 0; i < numberEnemy; ++i) {
            Enemy* enemy = new Enemy(life, speed, startX, startY);
            enemies.push_back(enemy);
        }
        allEnemiesCreated = true;
    }
}

bool MapController::spawnTime() {
    long long int currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    if (currentTime - lastSpawnTime >= spawnInterval) {
        lastSpawnTime = currentTime;
        return true;
    }
    return false;
}

vector<vector<Tile>> MapController::createAndReturnMap(const string& filename, Map* map) {
    map->createMap(filename);
    return map->getTiles();
}

#include "./ControllerH/MapController.h"

MapController::MapController() : allEnemiesCreated(false), lastSpawnTime(0), spawnInterval(1000) {}

MapController::~MapController() {
    for (auto enemy : enemies) {
        delete enemy;
    }
}

void MapController::createEnemy(int life, int speed, int numberEnemy, SDL_Renderer* renderer, int x, int y, int width, int height, const char* image) {
    if (!allEnemiesCreated) {
        for (int i = 0; i < numberEnemy; ++i) {
            Enemy* enemy = new Enemy(life, speed, renderer, x, y, width, height, image);
            enemies.push_back(enemy);
        }
        allEnemiesCreated = true;
    }
}

Enemy* MapController::getEnemy(size_t index) {
    if (index < enemies.size()) {
        return enemies[index];
    }
    return nullptr;
}

bool MapController::spawnTime() {
    using namespace chrono;
    long long currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
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

void MapController::searchForWayPoints(Map* map) {
    map->searchForWayPoints();
}

void MapController::moveEnemies(vector<pair<int, int>> wayPoints, int tileWidth, int tileHeight) {
    for (auto enemy : enemies) {
        enemy->updatePosition(tileWidth, tileHeight, wayPoints);
    }
}
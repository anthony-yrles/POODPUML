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

void MapController::enemiesMovement(const string& filename, Map* map, int beginX, int beginY, int tileWidth, int tileHeight) {
    
    vector<vector<Tile>> tiles = createAndReturnMap(filename, map);
    for (size_t i = 0; i < tiles.size(); i++) {
        for (size_t j = 0; j < tiles[i].size(); j++) {
            for (auto enemy : enemies) {
                if (enemy->getPosition()[0] + enemy->getSpeed() == beginX + (j + 1) * tileWidth || enemy->getPosition()[1] + enemy->getSpeed() == beginY + (i + 1) * tileHeight) {
                    if (tiles[i][j].isTurnRight) {
                        if (enemy->getMovement() == make_pair(0, 1)) {
                            enemy->move(1, 0);
                        } else if (enemy->getMovement() == make_pair(-1, 0)) {
                            enemy->move(0, 1);
                        } else if (enemy->getMovement() == make_pair(0, -1)) {
                            enemy->move(-1, 0);
                        } else if (enemy->getMovement() == make_pair(1, 0)) {
                            enemy->move(0, -1);
                        }
                    } else if (tiles[i][j].isTurnLeft) {
                        if (enemy->getMovement() == make_pair(0, 1)) {
                            enemy->move(-1, 0);
                        } else if (enemy->getMovement() == make_pair(-1, 0)) {
                            enemy->move(0, -1);
                        } else if (enemy->getMovement() == make_pair(0, -1)) {
                            enemy->move(1, 0);
                        } else if (enemy->getMovement() == make_pair(1, 0)) {
                            enemy->move(0, 1);
                        }
                    } else {
                        enemy->move(enemy->getMovement().first, enemy->getMovement().second);
                    }
                }
            }
        }
    }
}

vector<vector<Tile>> MapController::createAndReturnMap(const string& filename, Map* map) {
    map->createMap(filename);
    return map->getTiles();
}

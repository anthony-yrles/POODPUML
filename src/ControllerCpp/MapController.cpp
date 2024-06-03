#include "./ControllerH/MapController.h"

MapController::MapController() : allEnemiesCreated(false), lastSpawnTime(0), spawnInterval(1000) {}

MapController::~MapController() {
    for (auto enemy : enemies) {
        delete enemy;
    }
}

void MapController::createEnemy(int life, int speed, int startX, int startY, int numberEnemy, SDL_Renderer* renderer, int x, int y, int width, int height, const char* image) {
    if (!allEnemiesCreated) {
        for (int i = 0; i < numberEnemy; ++i) {
            Enemy* enemy = new Enemy(life, speed, startX, startY, renderer, x, y, width, height, image);
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

void MapController::enemiesMovement(const string& filename, Map* map, Draw* draw, int beginX, int beginY, int tileWidth, int tileHeight) {
    cout << "enemiesMovement" << endl;
    auto tiles = createAndReturnMap(filename, map);
    for (int i = 0; i < tiles.size(); ++i) {
        for (int j = 0; j < tiles[i].size(); ++j) {
            for (auto enemy : enemies) {
                auto enemyPosition = enemy->getPosition();
                auto enemySpeed = enemy->getSpeed();
                enemy->setMovement(0, 1);
                cout << "enemyPosition.first: " << enemyPosition.first << endl;
                cout << "enemyPosition.second: " << enemyPosition.second << endl;
                if (enemyPosition.first + enemySpeed == beginX + (j + 1) * tileWidth || 
                    enemyPosition.second + enemySpeed == beginY + (i + 1) * tileHeight) {
                    
                    auto movement = enemy->getMovement();
                    if (tiles[i][j].isTurnRight) {
                        if (movement == make_pair(0, 1)) {
                            enemy->move(1, 0);
                        } else if (movement == make_pair(-1, 0)) {
                            enemy->move(0, 1);
                        } else if (movement == make_pair(0, -1)) {
                            enemy->move(-1, 0);
                        } else if (movement == make_pair(1, 0)) {
                            enemy->move(0, -1);
                        }
                    } else if (tiles[i][j].isTurnLeft) {
                        if (movement == std::make_pair(0, 1)) {
                            enemy->move(-1, 0);
                        } else if (movement == make_pair(-1, 0)) {
                            enemy->move(0, -1);
                        } else if (movement == make_pair(0, -1)) {
                            enemy->move(1, 0);
                        } else if (movement == make_pair(1, 0)) {
                            enemy->move(0, 1);
                        }
                    } else {
                        enemy->move(movement.first, movement.second);
                    }
                    enemy->drawEntity(draw);
                }
            }
        }
    }
}

vector<vector<Tile>> MapController::createAndReturnMap(const string& filename, Map* map) {
    map->createMap(filename);
    return map->getTiles();
}

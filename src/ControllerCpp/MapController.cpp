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


void MapController::setEnemiesPositions(Map* map, const string& filename, int enemyNumber, int width, int height) {
    vector<vector<Tile>> tiles = createAndReturnMap(filename, map);
    tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    for (size_t i = 0; i < tiles.size(); ++i) {
        for (size_t j = 0; j < tiles[i].size(); ++j) {
            if (tiles[i][j].isMonsterBegin) {
                for (int k = 0; k < enemyNumber; ++k) {
                    auto enemy = getEnemy(k);
                    if (enemy) {
                        enemy->setEntityX(beginX + j * tileWidth);
                        enemy->setEntityY(beginY + i * tileHeight);
                        enemy->setEntityWidth(tileWidth);
                        enemy->setEntityHeight(tileHeight);
                    }
                }
            }
        }
    }
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

void MapController::tileSize(int WIDTH, int HEIGHT, int filewidth, int fileheight) {
    if (filewidth > fileheight) {
        tileWidth = WIDTH / filewidth;
        tileHeight = tileWidth;
        beginY = (HEIGHT - (tileHeight * fileheight)) / 2;
    } else {
        tileHeight = HEIGHT / fileheight;
        tileWidth = tileHeight;
        beginX = (WIDTH - (tileWidth * filewidth)) / 2;
    }
}

vector<pair<int, int>> MapController::searchForWayPoints(Map* map) {
    return map->searchForWayPoints();
}

void MapController::moveEnemies(vector<pair<int, int>> wayPoints, int tileWidth, int tileHeight) {
    for (auto enemy : enemies) {
        enemy->updatePosition(tileWidth, tileHeight, wayPoints);
    }
}
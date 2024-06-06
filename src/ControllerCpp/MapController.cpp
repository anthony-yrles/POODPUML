#include "./ControllerH/MapController.h"

MapController::MapController() {}

MapController::~MapController() {
    for (auto enemy : enemies) {
        delete enemy;
    }
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
        beginX = 300;
    } else {
        tileHeight = HEIGHT / fileheight;
        tileWidth = tileHeight;
        beginX = (WIDTH - (tileWidth * filewidth)) / 2;
        beginY = 0;
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

vector<pair<int, int>> MapController::searchForWayPoints(Map* map) {
    return map->searchForWayPoints();
}

void MapController::spawnAndMoveEnemy(Map *map, const string& filename, int width, int height, int numberEnemy, int life, int speed, SDL_Renderer* renderer, const char* image, Draw* draw) {

    vector<vector<Tile>> tiles = createAndReturnMap(filename, map);
    tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    int enemyCreated = 0;

    if (!allEnemiesCreated && enemyCreated < numberEnemy) {
        if (spawnTime()) { 
            for (size_t i = 0; i < tiles.size(); ++i) {
                for (size_t j = 0; j < tiles[i].size(); ++j) {
                    if (tiles[i][j].isMonsterBegin) {
                        Enemy* enemy = new Enemy(life, speed, renderer, beginX + j * tileWidth, beginY + i * tileHeight, tileWidth, tileHeight, image);
                        enemyCreated++;
                        enemies.push_back(enemy);
                        enemy->drawEntity(draw);
                    }
                }
            }
        }
    }
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        Enemy* enemy = *it;
        enemy->updatePosition(tileWidth, tileHeight, searchForWayPoints(map), beginX, beginY);
        enemy->drawEntity(draw);
        enemy->lifePointsRect(renderer, enemy->getEntityX(), enemy->getEntityY() - 10, enemy->getEntityWidth(), 5, enemy->getLifePoints(), draw);

        if (enemy->hasReachedEnd()) {
            it = enemies.erase(it);
            delete enemy;
        } else {
            ++it;
        }
    }
}
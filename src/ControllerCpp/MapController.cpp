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

        if (enemy->hasReachedEnd() || enemy->getLifePoints() <= 0){
            it = enemies.erase(it);
            delete enemy;
        } else {
            ++it;
        }
    }
}

vector<Enemy*> MapController::getEnemies() const {
    return enemies;
}

void MapController::spawnTower(int damage, int range, int fireSpeed, int numberOfFire, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image, Draw* draw) {
    Tower* tower = new Tower(damage, range, fireSpeed, numberOfFire, renderer, x, y, width, height, image);
    towers.push_back(tower);
    tower->drawEntity(draw);
}

void MapController::fireTowers(vector<Enemy*> enemies) {
    for (auto tower : towers) {
        tower->fire(enemies);
    }
}

vector<Tower*> MapController::getTowers() const {
    return towers;
}

void MapController::setGamesAttributes() {
    Game game;
    game.attributesChangedByLevelAndDifficulty();
    totalEnemiesGame = game.getTotalEnemies();
    goldGames = game.getGold();
    costGames = game.getCost();
    gameLifePointsGames = game.getGameLifePoints();
    enemyGoldEarnedGames = game.getEnemyGoldEarned();
}

int MapController::getLevelGame() const {
    return levelGame;
}
void MapController::setLevelGame(int levelGame) {
    this->levelGame = levelGame;
}
int MapController::getDifficultyGame() const {
    return difficultyGame;
}
void MapController::setDifficultyGame(int difficultyGame) {
    this->difficultyGame = difficultyGame;
}
int MapController::getTotalEnemiesGame() const {
    return totalEnemiesGame;
}
void MapController::setTotalEnemiesGame(int totalEnemiesGame) {
    this->totalEnemiesGame = totalEnemiesGame;
}
int MapController::getGoldGames() const {
    return goldGames;
}
void MapController::setGoldGames(int goldGames) {
    this->goldGames = goldGames;
}
int MapController::getCostGames() const {
    return costGames;
}
void MapController::setCostGames(int costGames) {
    this->costGames = costGames;
}
int MapController::getGameLifePointsGames() const {
    return gameLifePointsGames;
}
void MapController::setGameLifePointsGames(int gameLifePointsGames) {
    this->gameLifePointsGames = gameLifePointsGames;
}
int MapController::getEnemyGoldEarnedGames() const {
    return enemyGoldEarnedGames;
}
void MapController::setEnemyGoldEarnedGames(int enemyGoldEarnedGames) {
    this->enemyGoldEarnedGames = enemyGoldEarnedGames;
}
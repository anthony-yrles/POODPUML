#include "./ControllerH/MapController.h"

// Constructor
MapController::MapController() {}

// Destructor
MapController::~MapController() {
    // Free memory for each enemy
    for (auto enemy : enemies) {
        delete enemy;
    }
}

// Create and return map tiles
vector<vector<Tile>> MapController::createAndReturnMap(const string& filename, Map* map) {
    map->createMap(filename);
    return map->getTiles();
}

// Calculate tile size based on screen and map dimensions
void MapController::tileSize(int WIDTH, int HEIGHT, int filewidth, int fileheight) {
    tileWidth = WIDTH / filewidth;
    tileHeight = HEIGHT / fileheight;
    beginY = (HEIGHT - (tileHeight * fileheight)) / 2;
    beginX = 300 + ((WIDTH - (tileWidth * filewidth)) / 2);
}

// Check if it's time to spawn a new enemy
bool MapController::spawnTime() {
    using namespace chrono;
    long long currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    if (currentTime - lastSpawnTime >= spawnInterval) {
        lastSpawnTime = currentTime;
        return true;
    }
    return false;
}

// Check if it's time for towers to fire
bool MapController::fireTime() {
    using namespace chrono;
    long long currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    if (currentTime - lastFireTime >= fireInterval) {
        lastFireTime = currentTime;
        return true;
    }
    return false;
}

// Search for waypoints on the map
vector<pair<int, int>> MapController::searchForWayPoints(Map* map) {
    return map->searchForWayPoints();
}

// Spawn and move enemies on the map
void MapController::spawnAndMoveEnemy(Map *map, const string& filename, int width, int height, int life, int maxlife, int speed, SDL_Renderer* renderer, const char* image, Draw* draw) {
    // Create and return map tiles
    vector<vector<Tile>> tiles = createAndReturnMap(filename, map);
    // Calculate tile size
    tileSize(width, height, map->getFileWidth(), map->getFileHeight());

    // Spawn enemies if conditions are met
    if (!allEnemiesCreated && enemyCreated < totalEnemiesGame) {
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

    // Move and update enemies
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        Enemy* enemy = *it;
        enemy->updatePosition(tileWidth, tileHeight, searchForWayPoints(map), beginX, beginY);
        enemy->drawEntity(draw);
        enemy->lifePointsRect(renderer, enemy->getEntityX(), enemy->getEntityY() - 10, enemy->getEntityWidth(), 5, enemy->getLifePoints(), maxlife, draw);

        // Remove enemy if it has reached the end or has no life points left
        if (enemy->hasReachedEnd() || enemy->getLifePoints() <= 0){
            if (enemy->getLifePoints() <= 0) {
                totalEnemiesKilled++;
                goldGames += enemyGoldEarnedGames;
            } else {
                gameLifePointsGames--;
            }
            it = enemies.erase(it);
            delete enemy;
        } else {
            ++it;
        }
    }
}

// Getters and setters for game attributes
vector<Enemy*> MapController::getEnemies() const {
    return enemies;
}

void MapController::clearEnemies() {
    // Free memory for each enemy and clear the vector
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

// Spawn a tower on the map
void MapController::spawnTower(int damage, int range, int fireSpeed, int numberOfFire, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image, Draw* draw) {
    Tower* tower = new Tower(damage, range, fireSpeed, numberOfFire, renderer, x, y, width, height, image);
    towers.push_back(tower);
    tower->drawEntity(draw);
}

// Fire towers at enemies
void MapController::fireTowers(vector<Enemy*> enemies) {
    if(fireTime()) {
        for (auto tower : towers) {
            tower->fire(enemies);
        }
    }
}

// Getters and setters for towers
vector<Tower*> MapController::getTowers() const {
    return towers;
}

void MapController::clearTowers() {
    // Free memory for each tower and clear the vector
    for (auto tower : towers) {
        delete tower;
    }
    towers.clear();
}

// Set game attributes based on level and difficulty
void MapController::setGamesAttributes(int level, int difficulty) {
    Game game(level);
    game.attributesChangedByLevelAndDifficulty(difficulty);
    totalEnemiesGame = game.getTotalEnemies();
    totalEnemiesKilled = 0;
    goldGames = game.getGold();
    costGames = game.getCost();
    gameLifePointsGames = game.getGameLifePoints();
    enemyGoldEarnedGames = game.getEnemyGoldEarned();
}

// Getters and setters for game attributes
int MapController::getLevelGame() const {
    return levelGame;
}
void MapController::setLevelGame(int levelGame) {
    this->levelGame = levelGame;
}
int MapController::getTotalEnemiesGame() const {
    return totalEnemiesGame;
}
void MapController::setTotalEnemiesGame(int totalEnemiesGame) {
    this->totalEnemiesGame = totalEnemiesGame;
}
int MapController::getTotalEnemiesKilled() const {
    return totalEnemiesKilled;
}
void MapController::setTotalEnemiesKilled(int totalEnemiesKilled) {
    this->totalEnemiesKilled = totalEnemiesKilled;
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
int MapController::getEnemyCreated() const {
    return enemyCreated;
}
void MapController::setEnemyCreated(int enemyCreated) {
    this->enemyCreated = enemyCreated;
}

bool MapController::getOptionValidate() const {
    return optionValidate;
}
void MapController::setOptionValidate(bool optionValidate) {
    this->optionValidate = optionValidate;
}
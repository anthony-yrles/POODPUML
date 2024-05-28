#include "./ControllerH/MapController.h"

MapController::MapController(long int spawnTime, int spawnNumber, vector<Enemy*> enemies, vector<Tower*> towers) 
    : spawnTime(spawnTime), spawnNumber(spawnNumber), enemies(enemies), tower(towers) {}

MapController::~MapController() {
    delete map;
    delete castle;
    for (auto enemy : enemies) {
        delete enemy;
    }
    for (auto tower : towers) {
        delete tower;
    }
}

void MapController::startGame() {
    initializeMap();
    enemySpawn();
    while (!gameEnd) {
        createTower();
        upgradeTower();
        createCastle();
        victory();
        defeat();
    }
}

void MapController::initializeMap() {
    map = new Map(width, height);
    castle = new Castle(lifePoints, castlePositionX, castlePositionY);
    createEnemy();
    gameEnd = false;
    gameWin = false;
}

void MapController::createEnemy() {
    if (enemyCount < spawnNumber) {
        Enemy* enemy = new Enemy(enemyLifePoints, enemySpeed, enemyPositionX, enemyPositionY);
        enemies.push_back(enemy);
        enemyCount++;
    }  
}

void MapController::enemySpawn() {
    if (clock() - spawnTime >= 0) {
        spawnTime = clock() + spawnInterval;
        notifyObservers();
        spawnNumber--;
    }
}

void MapController::destroyEnemy() {
    for (auto enemy : enemies) {
        if (enemy->getLifePoints() <= 0) {
            money += enemy->getReward();
            delete enemy;
            enemies.erase(enemy);
        }
    }
}

void MapController::createTower() {
    Tower* tower = new Tower(towerLifePoints, towerDamage, towerRange, towerPositionX, towerPositionY);
    towers.push_back(tower);
}

void MapController::upgradeTower() {
    for (auto tower : towers) {
        if (tower->getUpgradeCost() <= money) {
            tower->upgrade();
            money -= tower->getUpgradeCost();
        }
    }
}

void MapController::towerAttack() {
    for (auto tower : towers) {
        tower->fire(enemies);
        destroyEnemy();
    }
}

void MapController::victory() {
    if (enemies.empty() && spwanNumber == 0) {
        gameEnd = true;
        gameWin = true;
    }
}

void MapController::defeat() {
    if (castle->getLifePoints() <= 0) {
        gameEnd = true;
        gameWin = false;
    }
}

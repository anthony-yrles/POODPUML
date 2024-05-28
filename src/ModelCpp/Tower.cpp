#include "./ModelH/Tower.h"

Tower::Tower(int damage, int range, int firespeed, int numberOfFire, int positionX, int positionY) 
    : damage(damage), range(range), fireSpeed(firespeed), numberOfFire(numberOfFire), position(positionX,positionY) {}

int Tower::getDamage() const {
    return damage;
}
void Tower::setDamage(int damage) {
    this->damage = damage;
}

int Tower::getRange() const {
    return range;
}
void Tower::setRange(int range) {
    this->range = range;
}

int Tower::getFireSpeed() const {
    return fireSpeed;
}
void Tower::setFireSpeed(int firespeed) {
    this->fireSpeed = firespeed;
}

int Tower::getNumberofFire() const {
    return numberOfFire;
}
void Tower::setNumberofFire(int numberOfFire) {
    this->numberOfFire = numberOfFire;
}

vector<int> Tower::getPosition() const {
    return position;
}
void Tower::setPosition(int x, int y) {
    position = {x, y};
}

int Tower::fire(vector<Enemy>& enemies) {
    for (size_t i = 0; i < enemies.size(); i++) {
        vector<int> enemyPosition = enemies[i].getPosition();
        int distance = abs(enemyPosition[0] - position[0]) + abs(enemyPosition[1] - position[1]);
        if (distance <= range) {
            enemies[i].takeDamage(damage);
            ++numberOfFire;
            if (numberOfFire == 5) {
                fireCount(enemies);
                notifyObservers();
            }
        }
    }  
}

void Tower::upgrade() {
    damage += 10;
    range += 10;
    fireSpeed += 10;
}

void Tower::fireCount(vector<Enemy>& enemies) {
    for (size_t i = 0; i < enemies.size(); ++i) {
        std::vector<int> enemyPosition = enemies[i].getPosition();
        int distance = std::abs(enemyPosition[0] - position[0]) + std::abs(enemyPosition[1] - position[1]);
        if (distance <= range) {
            enemies[i].takeDamage(damage);
        }
    }
    numberOfFire = 0;
}
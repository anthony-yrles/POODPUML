#include "./ModelH/Tower.h"

Tower::Tower(int damage, int range, int fireSpeed, int numberOfFire, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image) :
    Entity(renderer, x, y, width, height, image), damage(damage), range(range), fireSpeed(fireSpeed), numberOfFire(numberOfFire), position{x, y} {}

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

pair<float, float> Tower::getPosition() const {
    return position;
}
void Tower::setPosition(float newX, float newY) {
    position = {x, y};
}

void Tower::fire(vector<Enemy*> enemies) {
    for (auto enemy : enemies) {
        pair<float, float> enemyPosition = make_pair(enemy->getEntityX(), enemy->getEntityY());
        float distance = abs(enemyPosition.first - position.first) + abs(enemyPosition.second - position.second);
        if (distance <= range) {
            enemy->setLifePoints(enemy->getLifePoints() - damage);
            ++numberOfFire;
        }
    }  
}

void Tower::upgrade() {
    damage += 10;
    range += 10;
    fireSpeed += 10;
}

// void Tower::fireCount(vector<Enemy>& enemies) {
//     for (size_t i = 0; i < enemies.size(); ++i) {
//         pair<int, int> enemyPosition = enemies[i].getPosition();
//         int distance = abs(enemyPosition.first - position.first) + abs(enemyPosition.second - position.second);
//         if (distance <= range) {
//             enemies[i].takeDamage(damage);
//         }
//     }
//     numberOfFire = 0;
// }
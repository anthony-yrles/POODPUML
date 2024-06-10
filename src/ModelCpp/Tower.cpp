#include "./ModelH/Tower.h"

// Constructor
Tower::Tower(int damage, int range, int fireSpeed, int numberOfFire, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image) :
    Entity(renderer, x, y, width, height, image), damage(damage), range(range), fireSpeed(fireSpeed), numberOfFire(numberOfFire), position{x, y} {}

// Getter and setter for damage
int Tower::getDamage() const {
    return damage;
}
void Tower::setDamage(int damage) {
    this->damage = damage;
}

// Getter and setter for range
int Tower::getRange() const {
    return range;
}
void Tower::setRange(int range) {
    this->range = range;
}

// Getter and setter for fire speed
int Tower::getFireSpeed() const {
    return fireSpeed;
}
void Tower::setFireSpeed(int firespeed) {
    this->fireSpeed = firespeed;
}

// Getter and setter for number of fire
int Tower::getNumberofFire() const {
    return numberOfFire;
}
void Tower::setNumberofFire(int numberOfFire) {
    this->numberOfFire = numberOfFire;
}

// Getter for position
pair<float, float> Tower::getPosition() const {
    return position;
}

// Setter for position
void Tower::setPosition(float newX, float newY) {
    position = {newX, newY};
}

// Method to fire at enemies
void Tower::fire(vector<Enemy*> enemies) {
    if (enemies.empty()) return;
    
    vector<pair<float, Enemy*>> distances;

    // Calculate distances between tower and enemies
    for (auto enemy : enemies) {
        float enemyX = enemy->getEntityX();
        float enemyY = enemy->getEntityY();
        float distance = abs(enemyX - position.first) + abs(enemyY - position.second);
        if (distance <= range) {
            distances.push_back(make_pair(distance, enemy));
        }
    }

    // Find target and attack
    if (!distances.empty()) {
        sort(distances.begin(), distances.end());
        Enemy* target = distances.front().second;
        float targetDistance = distances.front().first;

        if (targetDistance <= range) {
            if (target->getLifePoints() - damage <= 0) {
                target->setLifePoints(0);
            } else {
                target->setLifePoints(target->getLifePoints() - damage);
                numberOfFire++;
            }
        }
    }
}

// Method to upgrade the tower
void Tower::upgrade() {
    damage += 10;
    range += 10;
    fireSpeed += 10;
}

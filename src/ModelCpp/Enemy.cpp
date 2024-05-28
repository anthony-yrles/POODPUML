#include "./ModelH/Enemy.h"

Enemy::Enemy(int life, int speed, int startX, int startY) : lifePoints(life), speed(speed), position(startX, startY) {}

int Enemy::getLifePoints() const {
    return lifePoints;
}

void Enemy::setLifePoints(int lp) {
    lifePoints = lp;
}

int Enemy::getSpeed() const {
    return speed;
}

void Enemy::setSpeed(int spd) {
    speed = spd;
}

vector<int> Enemy::getPosition() const {
    return position;
}

void Enemy::setPosition(int x, int y) {
    position = {x, y};
}

void Enemy::takeDamage(int damage) {
    int previousLifePoints = lifePoints;
    lifePoints -= damage;
    if (previousLifePoints != lifePoints) {
        setLifePoints(lifePoints);
        notifyObservers();
    }
}

void Enemy::move(int deltaX, int deltaY) {
    int newX = position[0] + deltaX * speed;
    int newY = position[1] + deltaY * speed;
    setPosition(newX, newY);
}

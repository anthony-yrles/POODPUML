#include "./ModelH/Enemy.h"

Enemy::Enemy(int life, int speed, int startX, int startY, SDL_Renderer* renderer, int x, int y, int width, int height, const char* image) :
    Entity(renderer, x, y, width, height, image) , lifePoints(life), speed(speed), startX(startX), startY(startY), 
    movement(0, 0), position(x, y) {}

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

pair<int, int> Enemy::getPosition() const {
    return position;
}

void Enemy::setPosition(int x, int y) {
    position = {x, y};
}

pair<int, int> Enemy::getMovement() const {
    return movement;
}

void Enemy::setMovement(int x, int y) {
    movement = {x, y};
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
    int newX = position.first + deltaX * speed;
    int newY = position.second + deltaY * speed;
    setPosition(newX, newY);
    setMovement(deltaX, deltaY);
}

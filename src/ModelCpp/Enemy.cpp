#include "./ModelH/Enemy.h"

Enemy::Enemy(int life, int speed, SDL_Renderer* renderer, int x, int y, int width, int height, const char* image) :
    Entity(renderer, x, y, width, height, image) , lifePoints(life), speed(speed) {}

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

void Enemy::updatePosition(int tileWidth, int tileHeight, const vector<pair<int, int>>& wayPoints) {
    if (currentWaypoint >= wayPoints.size()) return;

    int targetX = wayPoints[currentWaypoint].first * tileWidth;
    int targetY = wayPoints[currentWaypoint].second * tileHeight;

    int dx = targetX - x;
    int dy = targetY - y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance < speed) {
        x = targetX;
        y = targetY;
        currentWaypoint++;
    } else {
        float directionX = dx / distance;
        float directionY = dy / distance;
        x += speed * directionX;
        y += speed * directionY;
    }
}

void Enemy::takeDamage(int damage) {
    int previousLifePoints = lifePoints;
    lifePoints -= damage;
    if (previousLifePoints != lifePoints) {
        setLifePoints(lifePoints);
        notifyObservers();
    }
}
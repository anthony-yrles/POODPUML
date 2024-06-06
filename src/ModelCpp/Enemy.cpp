#include "./ModelH/Enemy.h"

Enemy::Enemy(int life, int speed, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image) :
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

void Enemy::updatePosition(int tileWidth, int tileHeight, const vector<pair<int, int>>& wayPoints, int beginX, int beginY) {
    if (currentWaypoint >= wayPoints.size()) return;

    float targetX = beginX + wayPoints[currentWaypoint].first * tileWidth;
    float targetY = beginY + wayPoints[currentWaypoint].second * tileHeight;

    float dx = targetX - x;
    float dy = targetY - y;
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

void Enemy::lifePointsRect(SDL_Renderer* renderer, int x, int y, int width, int height, int life, Draw* draw) {
    draw->drawRect(renderer, x, y, width, height, 0, 0, 0, 255);

    float lifePercentage = static_cast<float>(life) / 100.0f;
    int red = static_cast<int>((1.0f - lifePercentage) * 255);
    int green = static_cast<int>(lifePercentage * 255);

    draw->drawRect(renderer, x, y, static_cast<int>(width * lifePercentage), height, red, green, 0, 255);
}
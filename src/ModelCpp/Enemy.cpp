#include "./ModelH/Enemy.h"

/**
 * @brief Constructs an Enemy object with the specified parameters.
 * @param life Initial life points of the enemy.
 * @param speed Speed of the enemy.
 * @param renderer Pointer to the SDL renderer used to draw the enemy.
 * @param x Initial x position of the enemy.
 * @param y Initial y position of the enemy.
 * @param width Width of the enemy.
 * @param height Height of the enemy.
 * @param image Path to the enemy's texture image.
 */
Enemy::Enemy(int life, int speed, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image) :
    Entity(renderer, x, y, width, height, image), lifePoints(life), speed(speed) {}

/**
 * @brief Gets the current life points of the enemy.
 * @return Current life points of the enemy.
 */
int Enemy::getLifePoints() const {
    return lifePoints;
}

/**
 * @brief Sets the life points of the enemy.
 * @param lp New life points of the enemy.
 */
void Enemy::setLifePoints(int lp) {
    lifePoints = lp;
}

/**
 * @brief Gets the current speed of the enemy.
 * @return Current speed of the enemy.
 */
int Enemy::getSpeed() const {
    return speed;
}

/**
 * @brief Sets the speed of the enemy.
 * @param spd New speed of the enemy.
 */
void Enemy::setSpeed(int spd) {
    speed = spd;
}

/**
 * @brief Updates the position of the enemy based on waypoints.
 * @param tileWidth Width of each tile.
 * @param tileHeight Height of each tile.
 * @param wayPoints Vector of waypoints to follow.
 * @param beginX Starting x coordinate.
 * @param beginY Starting y coordinate.
 */
void Enemy::updatePosition(int tileWidth, int tileHeight, const std::vector<std::pair<int, int>>& wayPoints, int beginX, int beginY) {
    if (currentWaypoint >= wayPoints.size()) {
        reachedEnd = true;
        return;
    }

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

/**
 * @brief Draws a life points rectangle above the enemy.
 * @param renderer Pointer to the SDL renderer.
 * @param x X coordinate of the rectangle.
 * @param y Y coordinate of the rectangle.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param life Current life points.
 * @param maxLife Maximum life points.
 * @param draw Pointer to the Draw utility class.
 */
void Enemy::lifePointsRect(SDL_Renderer* renderer, int x, int y, int width, int height, int life, int maxLife, Draw* draw) {
    draw->drawRect(renderer, x, y, width, height, 0, 0, 0, 255);

    float lifePercentage = static_cast<float>(life) / static_cast<float>(maxLife);
    int red = static_cast<int>((1.0f - lifePercentage) * 255);
    int green = static_cast<int>(lifePercentage * 255);

    draw->drawRect(renderer, x, y, static_cast<int>(width * lifePercentage), height, red, green, 0, 255);
}

/**
 * @brief Checks if the enemy has reached the end of the path.
 * @return True if the enemy has reached the end, false otherwise.
 */
bool Enemy::hasReachedEnd() const {
    return reachedEnd;
}

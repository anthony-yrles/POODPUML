#pragma once
#include <vector>
#include "./ModelH/Observable.h"
#include "./ModelH/Entity.h"

/**
 * @class Enemy
 * @brief Represents an enemy in the game.
 *
 * The Enemy class inherits from Entity and adds specific functionalities to manage
 * the enemy's life points, speed, and movement through waypoints.
 */
class Enemy : public Entity {
public:
    /**
     * @brief Constructs an Enemy object.
     * @param life Initial life points of the enemy.
     * @param speed Speed of the enemy.
     * @param renderer Pointer to the SDL renderer used to draw the enemy.
     * @param x Initial x position of the enemy.
     * @param y Initial y position of the enemy.
     * @param width Width of the enemy.
     * @param height Height of the enemy.
     * @param image Path to the enemy's texture image.
     */
    Enemy(int life, int speed, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image);

    /**
     * @brief Gets the current life points of the enemy.
     * @return Current life points of the enemy.
     */
    int getLifePoints() const;

    /**
     * @brief Sets the life points of the enemy.
     * @param lp New life points of the enemy.
     */
    void setLifePoints(int lp);

    /**
     * @brief Gets the current speed of the enemy.
     * @return Current speed of the enemy.
     */
    int getSpeed() const;

    /**
     * @brief Sets the speed of the enemy.
     * @param spd New speed of the enemy.
     */
    void setSpeed(int spd);

    /**
     * @brief Updates the position of the enemy based on waypoints.
     * @param tileWidth Width of each tile.
     * @param tileHeight Height of each tile.
     * @param wayPoints Vector of waypoints to follow.
     * @param beginX Starting x coordinate.
     * @param beginY Starting y coordinate.
     */
    void updatePosition(int tileWidth, int tileHeight, const std::vector<std::pair<int, int>>& wayPoints, int beginX, int beginY);

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
    void lifePointsRect(SDL_Renderer* renderer, int x, int y, int width, int height, int life, int maxLife, Draw* draw);

    /**
     * @brief Checks if the enemy has reached the end of the path.
     * @return True if the enemy has reached the end, false otherwise.
     */
    bool hasReachedEnd() const;

private:
    int lifePoints; ///< Current life points of the enemy.
    int speed; ///< Speed of the enemy.
    std::vector<std::pair<int, int>> waypoints; ///< List of waypoints for the enemy to follow.
    int currentWaypoint = 0; ///< Index of the current waypoint.
    bool reachedEnd = false; ///< Indicates if the enemy has reached the end of the path.
};

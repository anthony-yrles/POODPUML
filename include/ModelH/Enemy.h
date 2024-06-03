#pragma once
#include <vector>
#include "./ModelH/Observable.h"
#include "./ModelH/Entity.h"

class Enemy : public Observable, public Entity {
public:
    Enemy(int life, int speed, SDL_Renderer* renderer, int x, int y, int width, int height, const char* image);

    int getLifePoints() const;
    void setLifePoints(int lp);

    int getSpeed() const;
    void setSpeed(int spd);

    void takeDamage(int damage);

    void updatePosition(int tileWidth, int tileHeight, const vector<pair<int, int>>& wayPoints);
    
    pair<int, int> getEnemyTile(int tileWidth, int tileHeight);

private:
    int lifePoints;
    int speed;
    vector<pair<int, int>> waypoints;
    int currentWaypoint;
};

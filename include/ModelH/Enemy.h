#pragma once
#include <vector>
#include "./ModelH/Observable.h"
#include "./ModelH/Entity.h"

class Enemy : public Entity {
public:
    Enemy(int life, int speed, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image);

    int getLifePoints() const;
    void setLifePoints(int lp);

    int getSpeed() const;
    void setSpeed(int spd);

    void updatePosition(int tileWidth, int tileHeight, const vector<pair<int, int>>& wayPoints, int beginX, int beginY);
    void lifePointsRect(SDL_Renderer* renderer, int x, int y, int width, int height, int life, Draw* draw);


private:
    int lifePoints;
    int speed;
    vector<pair<int, int>> waypoints;
    int currentWaypoint = 0;
};

#pragma once
#include <vector>
#include "./ModelH/Observable.h"
#include "./ModelH/Entity.h"

class Enemy : public Observable, Entity {

public:
    Enemy(int life, int speed, int startX, int startY, SDL_Renderer* renderer, int x, int y, int width, int height, const char* image);

    int getLifePoints() const;
    void setLifePoints(int lp);

    int getSpeed() const;
    void setSpeed(int spd);

    pair<int, int> getPosition() const;
    void setPosition(int x, int y);

    pair<int, int> getMovement() const;
    void setMovement(int x, int y);

    void takeDamage(int damage);
    void move(int x, int y);
    
private:
    int lifePoints;
    int speed;
    int startX;
    int startY;
    pair<int, int> movement;
    pair<int, int> position;
};
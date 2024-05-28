#ifndef ENEMY_H
#define ENEMY_H

#pragma once
#include <vector>
#include "./ModelH/Observable.h"

class Enemy : public Observable {

public:
    Enemy(int life, int speed, int startX, int startY);

    int getLifePoints() const;
    void setLifePoints(int lp);

    int getSpeed() const;
    void setSpeed(int spd);

    vector<int> getPosition() const;
    void setPosition(int x, int y);

    void takeDamage(int damage);
    void move(int x, int y);
    
private:
    int lifePoints;
    int speed;
    vector<int> position;
};

#endif // ENEMY_H
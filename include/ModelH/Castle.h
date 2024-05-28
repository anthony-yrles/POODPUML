#pragma once
#include <vector>
#include "./ModelH/Observable.h"

using namespace std;

class Castle : public Observable {
public:
    Castle(int life, int positionX, int positionY);

    int getLifePoints() const;
    void setLifePoints(int lp);

    vector<int> getPosition() const;
    void setPosition(int positionX, int positionY);

    void takeDamage(int damage);

private:
    int lifePoints;
    vector<int> position;
};
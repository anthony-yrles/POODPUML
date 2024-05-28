#pragma once
#include "./ModelH/Observable.h"
#include "./ModelH/Enemy.h"

class Tower : public Observable {
public:
    Tower(int damage, int range, int firespeed, int numberOfFire, int positionX, int positionY);

    int getDamage() const;
    void setDamage(int damage);

    int getRange() const;
    void setRange(int range);

    int getFireSpeed() const;
    void setFireSpeed(int firespeed);

    int getNumberofFire() const;
    void setNumberofFire(int numberOfFire);

    vector<int> getPosition() const;
    void setPosition(int x, int y);

    void fire(vector<Enemy>& enemies);
    void upgrade();
    void fireCount(vector<Enemy>& enemies);

private:
    int damage;
    int range;
    int fireSpeed;
    int numberOfFire;
    vector<int> position;

};
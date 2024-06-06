#pragma once
#include "./ModelH/Observable.h"
#include "./ModelH/Enemy.h"
#include "./ModelH/Entity.h"

class Tower : public Entity {
public:
    Tower(int damage, int range, int fireSpeed, int numberOfFire, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image);

    int getDamage() const;
    void setDamage(int damage);

    int getRange() const;
    void setRange(int range);

    int getFireSpeed() const;
    void setFireSpeed(int firespeed);

    int getNumberofFire() const;
    void setNumberofFire(int numberOfFire);

    pair<float, float> getPosition() const;
    void setPosition(float newX, float newY);

    void fire(vector<Enemy*> enemies);
    void upgrade();

private:
    int damage;
    int range;
    int fireSpeed;
    int numberOfFire;
    pair<int, int> position;

};
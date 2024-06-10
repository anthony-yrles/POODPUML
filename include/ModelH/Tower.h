#pragma once

#include "./ModelH/Observable.h" // Include necessary header files
#include "./ModelH/Enemy.h"
#include "./ModelH/Entity.h"

// Tower class declaration, inheriting from Entity class
class Tower : public Entity {
public:
    // Constructor
    Tower(int damage, int range, int fireSpeed, int numberOfFire, SDL_Renderer* renderer, float x, float y, int width, int height, const char* image);

    // Getter and setter for damage
    int getDamage() const;
    void setDamage(int damage);

    // Getter and setter for range
    int getRange() const;
    void setRange(int range);

    // Getter and setter for fire speed
    int getFireSpeed() const;
    void setFireSpeed(int fireSpeed);

    // Getter and setter for number of fire
    int getNumberofFire() const;
    void setNumberofFire(int numberOfFire);

    // Getter for position
    pair<float, float> getPosition() const;

    // Setter for position
    void setPosition(float newX, float newY);

    // Method to fire at enemies
    void fire(vector<Enemy*> enemies);

    // Method to upgrade the tower
    void upgrade();

private:
    int damage; // Damage inflicted by the tower
    int range; // Range of the tower
    int fireSpeed; // Fire speed of the tower
    int numberOfFire; // Number of projectiles fired
    pair<int, int> position; // Position of the tower
};

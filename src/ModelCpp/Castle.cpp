#include "./ModelH/Castle.h"

Castle::Castle(int life, int positionX, int positionY) {
    this->lifePoints = life;
    this->position.push_back(positionX);
    this->position.push_back(positionY);
}

int Castle::getLifePoints() const {
    return this->lifePoints;
}
void Castle::setLifePoints(int lp) {
    this->lifePoints = lp;
}

vector<int> Castle::getPosition() const {
    return this->position;
}
void Castle::setPosition(int positionX, int positionY) {
    this->position.clear();
    this->position.push_back(positionX);
    this->position.push_back(positionY);
}

void Castle::takeDamage(int damage) {
    int previousLifePoints = lifePoints;
    lifePoints -= damage;
    if (previousLifePoints != lifePoints) {
        setLifePoints(lifePoints);
        notifyObservers();
    }
}
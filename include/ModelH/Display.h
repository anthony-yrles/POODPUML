#pragma once
#include "./ModelH/Observer.h"
#include "./ModelH/Enemy.h"
#include "./ModelH/Tower.h"

class Display : public Observer {
private:
    Enemy* enemy;
    Tower* tower;

public:
    Display(Enemy* en);
    Display(Tower* tw);

    void update() override;
};
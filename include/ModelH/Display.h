#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#pragma once
#include "./ModelH/Observer.h"
#include "./ModelH/Enemy.h"

class Display : public Observer {
private:
    Enemy* enemy;

public:
    Display(Enemy* en);

    void update() override;
};

#endif // __DISPLAY_H__
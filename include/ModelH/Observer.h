#ifndef OBSERVER_H
#define OBSERVER_H

#pragma once

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() {}
};

#endif // OBSERVER_H
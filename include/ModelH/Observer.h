#pragma once

// Interface for Observers
class Observer {
public:
    // Pure virtual function to update the observer
    virtual void update() = 0;

    // Virtual destructor
    virtual ~Observer() {}
};

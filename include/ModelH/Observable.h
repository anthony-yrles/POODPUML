#pragma once
#include <vector>
#include "./ModelH/Observer.h"
#include <algorithm>

using namespace std;

class Observable {
private:
    vector<Observer*> observers; // Vector to store pointers to observers

public:
    // Add an observer to the list
    void addObserver(Observer* observer);

    // Remove an observer from the list
    void removeObserver(Observer* observer);

    // Notify all observers
    void notifyObservers();
};

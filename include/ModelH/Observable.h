#pragma once
#include <vector>
#include "./ModelH/Observer.h"
#include <algorithm>

using namespace std;

class Observable {
private:
    vector<Observer*> observers;

public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObservers();
};
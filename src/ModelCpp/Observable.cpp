#include "./ModelH/Observable.h"

// Add an observer to the list
void Observable::addObserver(Observer* observer) {
    observers.push_back(observer);
}

// Remove an observer from the list
void Observable::removeObserver(Observer* observer) {
    // Search and remove the observer
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

// Notify all observers
void Observable::notifyObservers() {
    // Notify all observers
    for (Observer* observer : observers) {
        observer->update();
    }
}

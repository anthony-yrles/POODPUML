#include "./ModelH/Observable.h"

void Observable::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Observable::removeObserver(Observer* observer) {
    // Recherche et suppression de l'observateur
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Observable::notifyObservers() {
    // Notification de tous les observateurs
    for (Observer* observer : observers) {
        observer->update();
    }
}

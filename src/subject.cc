#include "subject.h"
#include <algorithm>

void Subject::attach(Observer *observer) {
    observers.emplace_back(observer);
}

void Subject::detach(Observer *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notifyObservers() {
    for (auto *observer : observers) {
        observer->notify();
    }
}

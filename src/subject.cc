#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach(Observer *o) {
    observers.push_back(o);
}

void Subject::detach(Observer *o) {
    // Manually remove the observer by finding and erasing it
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::notifyObservers() {
    for (auto *observer : observers) {
        observer->notify();
    }
}


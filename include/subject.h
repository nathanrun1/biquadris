#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject {
private:
    std::vector<Observer *> observers;

public:
    virtual ~Subject() = default;

    // Attach an observer to the subject
    void attach(Observer *observer) {
        observers.emplace_back(observer);
    }

    // Detach an observer from the subject
    void detach(Observer *observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    // Notify all attached observers
    void notifyObservers() {
        for (auto *observer : observers) {
            observer->notify();
        }
    }
};

#endif // SUBJECT_H

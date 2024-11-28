#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject {
private:
    std::vector<Observer *> observers;

public:
    virtual ~Subject() = default;

    void attach(Observer *observer);
    void detach(Observer *observer);
    void notifyObservers();
};

#endif // SUBJECT_H

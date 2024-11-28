#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject {
private:
    std::vector<Observer *> observers;

public:
    void attach(Observer *observer);
    void detach(Observer *observer);
    void notifyObservers();
    virtual ~Subject() = default;
};

#endif // SUBJECT_H

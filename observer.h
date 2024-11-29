#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual ~Observer() = default;

    // The notify method will be implemented by concrete observers
    virtual void notify() = 0;
};

#endif // OBSERVER_H

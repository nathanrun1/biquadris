#ifndef TEXT_OBSERVER_H
#define TEXT_OBSERVER_H

#include "observer.h"
#include "board.h"
#include <iostream>
#include <memory>

class TextObserver : public Observer {
    std::shared_ptr<Board> board; // Reference to the observed board

public:
    // Constructor
    explicit TextObserver(std::shared_ptr<Board> board);

    // Destructor
    ~TextObserver() override = default;

    // Notify method to update the board's textual representation
    void notify() override;
};

#endif // TEXT_OBSERVER_H

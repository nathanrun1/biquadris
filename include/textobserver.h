#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "observer.h"
#include "board.h"
#include <iostream>

class TextObserver : public Observer {
private:
    Board *board;

public:
    explicit TextObserver(Board *board);
    void notify() override;
    ~TextObserver() override;
};

#endif // TEXTOBSERVER_H

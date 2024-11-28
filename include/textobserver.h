#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "observer.h"
#include "board.h"
#include <memory>
#include <iostream>

class TextObserver : public Observer {
private:
    std::shared_ptr<Board> board;

public:
    explicit TextObserver(std::shared_ptr<Board> board);
    void notify() override;
    ~TextObserver() override;
};

#endif // TEXTOBSERVER_H

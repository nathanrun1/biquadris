#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "observer.h"
#include "board.h"
#include <memory>
#include <iostream>

class TextObserver : public Observer {
private:
    std::ostream& output;
    std::shared_ptr<Board> player1;
    std::shared_ptr<Board> player2;

public:
    explicit TextObserver(std::ostream& output, std::shared_ptr<Board> player1, std::shared_ptr<Board> player2);
    void notify() override;
    ~TextObserver() override;
};

#endif // TEXTOBSERVER_H

#include "textobserver.h"
#include "level.h"

TextObserver::TextObserver(Board *board) : board(board) {
    board->attach(this);
    std::cout << "attaching" << std::endl;
}

void TextObserver::notify() {
    std::cout << "Level: " << board->getLevel()->getLevelNum()
                << "    Score: " << board->getScore() << std::endl;
    std::cout << "-----------" << std::endl;

    for (int row = 0; row < board->getRowAmnt(); ++row) {
        for (int col = 0; col < board->getColAmnt(); ++col) {
            std::cout << board->getColorAtRC(row, col);
        }
        std::cout << std::endl;
    }
    std::cout << "-----------" << std::endl;
}

TextObserver::~TextObserver() {
    board->detach(this);
}

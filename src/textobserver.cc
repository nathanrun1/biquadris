#include "textobserver.h"

TextObserver::TextObserver(Board *board) : board(board) {
    board->attach(this);
}

void TextObserver::notify() {
    std::cout << "Level: " << board->getLevel() 
                << "    Score: " << board->getScore() << std::endl;
    std::cout << "-----------" << std::endl;

    const auto &grid = board->getBoard();
    for (const auto &row : grid) {
        for (const auto &cell : row) {
            std::cout << (cell.owner ? cell.owner->getColor() : ' ');
        }
        std::cout << std::endl;
    }
    std::cout << "-----------" << std::endl;
}

TextObserver::~TextObserver() {
    board->detach(this);
}

// textobserver.cc
#include "TextObserver.h"
#include "board.h"
#include <iostream>
#include <iomanip>

TextObserver::TextObserver(std::shared_ptr<Board> board) : board{board} {
    board->attach(this);
}

void TextObserver::notify() {
    render();
}

void TextObserver::render() {
    const int rows = board->getHeight();
    const int cols = board->getWidth();

    // Display the level and score
    std::cout << "Level: " << board->getLevel() << std::endl;
    std::cout << "Score: " << board->getScore() << std::endl;
    std::cout << std::string(cols, '-') << std::endl;

    // Display the board grid
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            char cell = board->getColorAt(x, y);
            std::cout << (cell ? cell : ' ');
        }
        std::cout << std::endl;
    }

    std::cout << std::string(cols, '-') << std::endl;

    // Display the next block
    std::cout << "Next: " << std::endl;
    auto nextBlock = board->getNextBlockShape();
    if (nextBlock) {
        for (const auto &coord : nextBlock->getShape()) {
            for (int x = 0; x < cols; ++x) {
                std::cout << (coord.first == x ? nextBlock->getColor() : ' ');
            }
            std::cout << std::endl;
        }
    }
}

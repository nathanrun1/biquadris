#include "textobserver.h"
#include "level.h"

TextObserver::TextObserver(std::ostream& output, std::shared_ptr<Board> board): output(output), board(board) {
    board->attach(this);
    output << "attaching" << std::endl;
}

void TextObserver::notify() {
    output << "Level:    " << board->getLevel()->getLevelNum() << std::endl;
    output << "Score:    " << board->getScore() << std::endl;
    output << "-----------" << std::endl;

    for (int row = 0; row < board->getRowAmnt(); ++row) {
        for (int col = 0; col < board->getColAmnt(); ++col) {
            output << board->getColorAtRC(row, col);
        }
        output << std::endl;
    }
    output << "-----------" << std::endl;
    output << "Next: " << std::endl;
    // TO DO: Please add NEXT block over here!
}

TextObserver::~TextObserver() {
    board->detach(this);
}

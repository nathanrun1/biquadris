#include "textobserver.h"
#include "level.h"

TextObserver::TextObserver(std::ostream& output, std::shared_ptr<Board> p1, std::shared_ptr<Board> p2): output(output), player1(p1), player2(p2) {
    p1->attach(this);
    p2->attach(this);
}


// Helper function used to help print out the next block in a Level.
//     Returns whether the vector contains the value in the array.
bool checkVec(std::vector<std::pair<int, int>> vec, std::pair<int, int> val) {
    for (long unsigned int i = 0; i < vec.size(); i++) {
        if (vec.at(i) == val) return true;
    }

    return false;
}

void TextObserver::notify() {
    // system("clear");
    std::shared_ptr<BlockShape> p1NextBlock = player1->getLevel()->checkNext();
    std::shared_ptr<BlockShape> p2NextBlock = player2->getLevel()->checkNext();

    output << "Player 1 --          Player 2 --" << std::endl;
    output << "Level:    " << player1->getLevel()->getLevelNum() << "          "  << "Level:    " << player2->getLevel()->getLevelNum() << std::endl;
    output << "Score:    " << player1->getScore() << "          " << "Score:    " << player2->getScore() << std::endl;
    output << "-----------          -----------" << std::endl;

    for (int row = 0; row < player1->getRowAmnt(); ++row) {
        for (int col = 0; col < player1->getColAmnt(); ++col) {
            output << player1->getColorAtRC(row, col);
        }

        output << "          ";

        for (int col = 0; col < player2->getColAmnt(); ++col) {
            output << player2->getColorAtRC(row, col);
        }

        output << std::endl;
    }
    output << "-----------          -----------" << std::endl;
    output << "Next:      " << "          " << "Next:      " << std::endl;
    
    // Blocks can only be at most 4 blocks tall, hence we only set row to 3.
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < player1->getColAmnt(); ++col) {
            std::pair<int, int> val = {col, row};

            if (checkVec(p1NextBlock->getShape(), val)) output << p1NextBlock->getColor();
            else                                        output << " ";
        }
        
        output << "          ";

        for (int col = 0; col < player2->getColAmnt(); ++col) {
            std::pair<int, int> val = {row, col};
            if (checkVec(p1NextBlock->getShape(), val)) output << p2NextBlock->getColor();
            else                                        output << " ";
        }

        output << std::endl;
        
    }
}

TextObserver::~TextObserver() {
    player1->detach(this);
    player2->detach(this);
}

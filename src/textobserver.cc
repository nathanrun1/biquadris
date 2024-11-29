#include "textobserver.h"
#include "level.h"

TextObserver::TextObserver(std::ostream& output, std::shared_ptr<Game> c): output(output), controller(c) {
    controller->attach(this);
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
    system("clear");
    std::shared_ptr<BlockShape> p1NextBlock = controller->getPlayer1()->getLevel()->checkNext();
    std::shared_ptr<BlockShape> p2NextBlock = controller->getPlayer2()->getLevel()->checkNext();

    output << "High Score: " << controller->getHighScore()  << "\n" << std::endl;


    output << "Player 1 --          Player 2 --" << std::endl;
    output << "Level:    " << controller->getPlayer1()->getLevel()->getLevelNum() << "          "  << "Level:    " << controller->getPlayer2()->getLevel()->getLevelNum() << std::endl;
    output << "Score:    " << controller->getPlayer1()->getScore() << "          " << "Score:    " << controller->getPlayer2()->getScore() << std::endl;
    output << "-----------          -----------" << std::endl;

    for (int row = 0; row < controller->getPlayer1()->getRowAmnt(); ++row) {
        for (int col = 0; col < controller->getPlayer1()->getColAmnt(); ++col) {
            output << controller->getPlayer1()->getColorAtRC(row, col);
        }

        output << "          ";

        for (int col = 0; col < controller->getPlayer2()->getColAmnt(); ++col) {
            output << controller->getPlayer2()->getColorAtRC(row, col);
        }

        output << std::endl;
    }
    output << "-----------          -----------" << std::endl;
    output << "Next:      " << "          " << "Next:      " << std::endl;
    
    // Blocks can only be at most 2 blocks tall, hence we only set row to 3 to include an extra line for inputs:
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < controller->getPlayer1()->getColAmnt(); ++col) {
            std::pair<int, int> val = {col, row};
            if (checkVec(p1NextBlock->getShape(), val)) output << p1NextBlock->getColor();
            else                                        output << " ";
        }
        
        output << "          ";

        for (int col = 0; col < controller->getPlayer2()->getColAmnt(); ++col) {
            std::pair<int, int> val = {col, row};
            if (checkVec(p2NextBlock->getShape(), val)) output << p2NextBlock->getColor();
            else                                        output << " ";
        }

        output << std::endl;
    }
}

TextObserver::~TextObserver() {
    controller->detach(this);
}

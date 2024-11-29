#include "game.h"

Game::Game(std::istream& input, std::shared_ptr<Board> Player1, std::shared_ptr<Board> Player2):
    input{input}, Player1{Player1}, Player2{Player2}, currPlayer{Player1}, highScore{0} {
        Player1->showBoard();
        Player2->showBoard();
    }

void runCommand(std::shared_ptr<Board> std::string command) {

}

void Game::startGame() {
    std::string command;
    int repeat = 1;

    while (input >> command) {
        // Checking for amount of time to repeat inputs IF given
        std::istringstream sstream{command};
        sstream >> repeat;
        if (sstream.fail()) repeat = 1;
        
        // Checks input for a commands, then runs the corresponding command
        
        input >> command;
        if (std::string("left").find(command) != std::string::npos) {
            for (int i = 0; i < repeat; i++) { currPlayer->actionLeft(); }
        } else if (std::string("right").find(command) != std::string::npos) {
            for (int i = 0; i < repeat; i++) { currPlayer->actionRight(); }
        } else if (std::string("down").find(command) != std::string::npos) {
            for (int i = 0; i < repeat; i++) { currPlayer->actionDown();}
        } else if (std::string("clockwise").find(command) != std::string::npos) {
            for (int i = 0; i < repeat; i++) { currPlayer->actionClockwise(); }
        } else if (std::string("counterclockwise").find(command) != std::string::npos) {
            for (int i = 0; i < repeat; i++) { currPlayer->actionCounterclockwise();}
        } else if (std::string("drop").find(command) != std::string::npos) {
            for (int i = 0; i < repeat; i++) { currPlayer->actionDrop(); }
        } else if (std::string("levelup").find(command) != std::string::npos) {
            for (int i = 0; i < repeat; i++) { currPlayer->actionLevelUp();}
        } else if (std::string("leveldown").find(command) != std::string::npos) {
            for (int i = 0; i < repeat; i++) { currPlayer->actionLevelDown(); }
        } else if (std::string("norandom").find(command) != std::string::npos) {
            std::string file;
            input >> file;
            currPlayer->actionNoRandom(file);

        } else if (std::string("random").find(command) != std::string::npos) {
            currPlayer->actionRandom();

        } else if (std::string("sequence").find(command) != std::string::npos) {
            std::string file;
            input >> file;
            currPlayer->actionNoRandom(file);
            // Have to do as written for ALL commands

        } else if (std::string("I").find(command) != std::string::npos) {
            // Set currentblock to I

        } else if (std::string("J").find(command) != std::string::npos) {
            // Set currentblock to J

        } else if (std::string("L").find(command) != std::string::npos) {
            // Set currentblock to L
        } else if (std::string("O").find(command) != std::string::npos) {
            // Set currentblock to O
        } else if (std::string("S").find(command) != std::string::npos) {
            // Set currentblock to S
        } else if (std::string("Z").find(command) != std::string::npos) {
            // Set currentblock to Z
        } else if (std::string("T").find(command) != std::string::npos) {
            // Set currentblock to T
        } else if (std::string("restart").find(command) != std::string::npos) {
            // restart the game
        } else { 
            continue;
        }

        if (currPlayer == Player1) currPlayer = Player2;
        else                       currPlayer = Player1;
    }
}

int Game::getHighScore() const { return highScore; }
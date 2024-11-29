#include "game.h"

Game::Game(std::istream& input, std::shared_ptr<Board> Player1, std::shared_ptr<Board> Player2):
    input{input}, Player1{Player1}, Player2{Player2}, currPlayer{Player1}, highScore{0} {
        Player1->getLevel()->getNext();
        Player2->getLevel()->getNext();
        Player1->notifyObservers();
    }

void Game::endGame(std::shared_ptr<Board> loser) {
    std::cout << "Game over!\n";
    std::string winner = "Player 1";
    if (loser == Player1) winner = "Player 2";
    highScore = std::max(Player1->getScore(), Player2->getScore());
    std::cout << winner << " wins! New high score: " << highScore << std::endl;
    std::cout << "Play again? Y/n" << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "Y") {
        Player1->wipeBoard();
        Player2->wipeBoard();
    } else {
        isOver = true;
        return;
    }
}

bool Game::runPlayerCommand(std::istream& input, std::shared_ptr<Board> currPlayer, int repeat, std::string command) {
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
        for (int i = 0; i < repeat; i++) { 
            if (!currPlayer->actionDrop()) {
                endGame(currPlayer);
                return false; // Loser starts first
            }
        }
        return true;
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
    } else if (std::string("I").find(command) != std::string::npos) {
        std::shared_ptr<BlockShape> newBlock = std::make_shared<I_Shape>();
        currPlayer->actionSetShape(newBlock);
    } else if (std::string("J").find(command) != std::string::npos) {
        std::shared_ptr<BlockShape> newBlock = std::make_shared<J_Shape>();
        currPlayer->actionSetShape(newBlock);
    } else if (std::string("L").find(command) != std::string::npos) {
        std::shared_ptr<BlockShape> newBlock = std::make_shared<L_Shape>();
        currPlayer->actionSetShape(newBlock);
    } else if (std::string("O").find(command) != std::string::npos) {
        std::shared_ptr<BlockShape> newBlock = std::make_shared<O_Shape>();
        currPlayer->actionSetShape(newBlock);
    } else if (std::string("S").find(command) != std::string::npos) {
        std::shared_ptr<BlockShape> newBlock = std::make_shared<S_Shape>();
        currPlayer->actionSetShape(newBlock);
    } else if (std::string("Z").find(command) != std::string::npos) {
        std::shared_ptr<BlockShape> newBlock = std::make_shared<Z_Shape>();
        currPlayer->actionSetShape(newBlock);
    } else if (std::string("T").find(command) != std::string::npos) {
        std::shared_ptr<BlockShape> newBlock = std::make_shared<T_Shape>();
        currPlayer->actionSetShape(newBlock);
    }

    return false;
}

void Game::startGame() {
    std::string command;
    int repeat = 1;
    bool switchPlayer;

    while (input >> command) {
        switchPlayer = false;        // Reset state of switchPlayer so each non-drop command does not switch to the opponent

        // Checking for amount of time to repeat inputs IF given
        std::istringstream sstream{command};
        sstream >> repeat;
        if (sstream.fail()) {        // If input fails AKA you issue a command that does NOT start with a number...
            repeat = 1;              // Repeat the input once.
            sstream.str("");         // Reset the string stream
            sstream.clear();         
            sstream >> command;      // Add the given input into the command.
        } else {
            sstream >> command;
        }

        // Reads from file and executes all possible commands for the currentPlayer ( does NOT switch turn order )
        //     When reading from file, you cannot read a command to read from another file. In other words, this command is ONE deep!
        if (std::string("sequence").find(command) != std::string::npos) {
            std::string file;
            input >> file;
            currPlayer->actionNoRandom(file);
            
            std::ifstream fstream{file};
            while (fstream >> command) { 
                std::istringstream sstream{command};
                sstream >> repeat;
                if (sstream.fail()) {
                    repeat = 1;      
                    sstream.str(""); 
                    sstream.clear();         
                    sstream >> command; 
                } else {
                    sstream >> command;
                }

                switchPlayer = runPlayerCommand(input, currPlayer, repeat, command);
            }
        } else if (std::string("restart").find(command) != std::string::npos) {
            Player1->wipeBoard();
            Player2->wipeBoard();
        } else {
            switchPlayer = runPlayerCommand(input, currPlayer, repeat, command);
        }
       if (switchPlayer && currPlayer == Player1)     currPlayer = Player2;
        else if (switchPlayer && currPlayer == Player2)     currPlayer = Player1;
        if (isOver) return; // End game if over
    }
}

int Game::getHighScore() const { return highScore; }
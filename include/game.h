#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>
#include <random>

#include "board.h"
#include "level.h"

class Game {
    std::istream& input;

    std::shared_ptr<Board> Player1;
    std::shared_ptr<Board> Player2;
    std::shared_ptr<Board> currPlayer;
    int highScore;
    
    public:
        Game(std::istream& input, std::shared_ptr<Board> Player1, std::shared_ptr<Board> Player2);
        ~Game() = default;

        void startGame();
        int getHighScore() const;
};


#endif
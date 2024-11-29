#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>
#include <random>

#include "board.h"
#include "level.h"

class Game: public Subject {
    std::istream& input;

    std::shared_ptr<Board> Player1;
    std::shared_ptr<Board> Player2;
    std::shared_ptr<Board> currPlayer;
    int highScore;
    
    public:
        Game(std::istream& input, std::shared_ptr<Board> Player1, std::shared_ptr<Board> Player2);
        ~Game() = default;

        void startGame();

        std::shared_ptr<Board> getPlayer1() const;
        std::shared_ptr<Board> getPlayer2() const;
        int getHighScore() const;
};


#endif
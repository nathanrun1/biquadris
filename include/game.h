#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>

#include "board.h"
#include "level.h"

class Game {
    std::shared_ptr<Board> Player1;
    std::shared_ptr<Board> Player2;
    std::istream& input;

    int highScore;
    std::shared_ptr<Board> currPlayer;
    
    public:
        Game(std::shared_ptr<Board> Player1, std::shared_ptr<Board> Player2, std::istream& input);
        ~Game() = default;

        void startGame();        
        int getHighScore() const;

};


#endif
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

    bool isOver = false;

    // endGame(winner) ends the game with loser 'loser'
    void endGame(std::shared_ptr<Board> loser);

    // Helper function that consolidates and executes all commands that affect the Board and currPlayer.
    //     Does NOT include commands that read from file or affects items outside the currPlayer (like resetGame.)
    //     Returns a boolean regarding whether to switch turn order.
    bool runPlayerCommand(std::istream& input, std::shared_ptr<Board> currPlayer, int repeat, std::string command);
    
public:
    Game(std::istream& input, std::shared_ptr<Board> Player1, std::shared_ptr<Board> Player2);
    ~Game() = default;
        void startGame();

        std::shared_ptr<Board> getPlayer1() const;
        std::shared_ptr<Board> getPlayer2() const;
        int getHighScore() const;
};


#endif
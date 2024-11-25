#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include "board.h"
#include "observer.h"
#include "level.h"

class Game {
private:
    // Game state for each player
    std::unique_ptr<Board> player1Board;
    std::unique_ptr<Board> player2Board;

    // Levels for each player
    std::unique_ptr<Level> player1Level;
    std::unique_ptr<Level> player2Level;

    // Observers for rendering
    std::shared_ptr<TextObserver> textObserver;
    std::shared_ptr<GraphicsObserver> graphicsObserver;

    // High score tracking
    int highScore = 0;

    // Initialize game state
    void initializeGame(int startLevel);

public:
    Game();
    ~Game();

    // Starts the game with a given starting level
    void startGame(int startLevel);

    // Restarts the game while preserving the high score
    void restartGame(int startLevel);

    // Sets the random seed for consistent block generation
    void setSeed(int seed);

    // Retrieves the current high score
    int getHighScore() const;

    // Processes a single command input
    void processCommand(const std::string &command);
};

#endif // GAME_H

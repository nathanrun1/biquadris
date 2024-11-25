// game.cc
#include "game.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include "specialaction.h"

using namespace std;

Game::Game() {}

Game::~Game() {}

void Game::initializeGame(int startLevel) {
    player1Board = make_unique<Board>();
    player2Board = make_unique<Board>();
    player1Level = Level::create(startLevel);  // Assuming Level has a static factory method
    player2Level = Level::create(startLevel);
    textObserver = make_shared<TextObserver>();
    graphicsObserver = make_shared<GraphicsObserver>();

    player1Board->attach(textObserver.get());
    player2Board->attach(textObserver.get());
    player1Board->attach(graphicsObserver.get());
    player2Board->attach(graphicsObserver.get());
}

void Game::startGame(int startLevel) {
    initializeGame(startLevel);
    string command;

    while (true) {
        try {
            cout << "> ";
            if (!getline(cin, command)) break;
            processCommand(command);
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}

void Game::restartGame(int startLevel) {
    player1Board.reset();
    player2Board.reset();
    startGame(startLevel);
}

void Game::setSeed(int seed) {
    srand(seed);
}

int Game::getHighScore() const {
    return highScore;
}

void Game::processCommand(const string &command) {
    istringstream iss(command);
    string cmd;
    int multiplier = 1;

    // Check for multiplier prefix
    if (isdigit(command[0])) {
        size_t idx = command.find_first_not_of("0123456789");
        multiplier = stoi(command.substr(0, idx));
        cmd = command.substr(idx);
    } else {
        cmd = command;
    }

    for (int i = 0; i < multiplier; ++i) {
        if (cmd == "left") {
            player1Board->moveLeft();  // Example method on Board
        } else if (cmd == "right") {
            player1Board->moveRight();
        } else if (cmd == "down") {
            player1Board->moveDown();
        } else if (cmd == "drop") {
            player1Board->drop();
        } else if (cmd == "restart") {
            restartGame(0); // Default start level for restart
        } else if (cmd == "levelup") {
            player1Board->levelUp();
        } else if (cmd == "leveldown") {
            player1Board->levelDown();
        } else {
            cerr << "Unknown command: " << cmd << endl;
        }
    }
}

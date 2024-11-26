#include <fstream>;
#include <utility>;

#include "level.h"

/*
 std::string seqFile;
    std::ifstream fstream;
    bool isRandom;

    Board* my_board;
    int turnsLastCleared;
*/

// Implementing the Level Factory Constructor/Methods
Level::Level(Board* my_board, std::string seqFile, bool isRandom):
    my_board{my_board}, seqFile{seqFile}, fstream{std::ifstream{seqFile}}, isRandom{isRandom}, turnsLastCleared{0} {}

Level::Level(const Level& other): 
    my_board{other.my_board}, seqFile{other.seqFile}, fstream{std::ifstream{other.seqFile}}, isRandom{other.isRandom}, turnsLastCleared{other.turnsLastCleared} {}

Level::Level(Level&& other): 
    my_board{other.my_board}, seqFile{other.seqFile}, fstream{std::ifstream{other.seqFile}}, isRandom{other.isRandom}, turnsLastCleared{other.turnsLastCleared} {
        other.seqFile = "";
        other.fstream = std::ifstream{""};
        other.isRandom = false;

        other.my_board = nullptr;
        other.turnsLastCleared = 0;
    }

Level& operator=(const Level& other) {
    
}
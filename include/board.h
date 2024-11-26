#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "block.h"
#include "level.h"

// INTENTION: Implement Board as an abstract base class, since it will be the concrete object for the decorator pattern
//   i.e. special actions will act as decorators on board, overriding one of those action methods (e.g. heavy overrides actionDrop() to drop the block twice)

// Impl notes: - Check block class for how to initialize them, and for other info
//             - add method for changing block shape (e.g. debugActionChangeShape)
//             - Need to implement Level class and levelup/down functionality
//             - Need to implement a "blank" version of the board which implements the default functionality for all of those pure virtual functions, e.g. DefaultBoard

const int BOARD_ROWS = 18;
const int BOARD_COLS = 11;

class Board {
    friend class Block;
    friend class Level;
protected:
    std::vector<std::vector<Cell>> grid = std::vector<std::vector<Cell>>(BOARD_ROWS, std::vector<Cell>(BOARD_COLS, Cell(nullptr)));
    int score; // Current player score
    Level* level; // Current level
    std::shared_ptr<Block> fallingBlock; // Current falling block 

    // spawnBlock(bottomLeftCoordinate) attempts to spawn a Block such that the bottom left corner of the smallest rectangle containing the Block
    //   is located at 'bottomLeftCoordinate', and set this Block as the current falling Block. If successful, returns true. Otherwise, returns false
    //   and has no effect. spawnBlock will fail (i.e. return false) when the desired position to spawn the Block is occupied by another Block.
    bool spawnBlock(std::pair<int, int> bottomLeftCoordinate);
public:
    // -- Action methods (to be implemented by decorators), along with documentation of default effects --
    //   if returns bool, return value represents whether or not action was successful
    virtual bool actionClockwise() = 0; // Rotates falling Block clockwise
    virtual bool actionCounterclockwise() = 0; // Rotates falling Block counterclockwise
    virtual bool actionLeft() = 0; // Moves falling Block left
    virtual bool actionRight() = 0; // Moves falling Block right
    virtual bool actionDown() = 0; // Moves falling Block down
    virtual void actionDrop() = 0; // Moves falling Block as far down as possible 
    virtual void actionLevelUp() = 0; // Increases the Level by 1
    virtual void actionLevelDown() = 0; // Decreases the Level by 1

    virtual void actionRandom() = 0; // Restores randomness for relevant Levels
    virtual void actionNoRandom(std::string file) = 0; // Makes relevant Levels non-random, taking input from provided file.
};

class DefaultBoard : Board {
public:
    bool actionClockwise() override; 
    bool actionCounterclockwise() override; 
    bool actionLeft() override; 
    bool actionRight() override; 
    bool actionDown() override; 
    void actionDrop() override; 
    void actionLevelUp() override;
    void actionLevelDown() override;

    void actionRandom() override; 
    void actionNoRandom(std::string file) override;
};

#endif 
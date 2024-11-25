#ifndef BOARD_H
#define BOARD_H
#include "block.h"

class Level; // temp

// INTENTION: Implement Board as an abstract base class, since it will be the concrete object for the decorator pattern
//   i.e. special actions will act as decorators on board, overriding one of those action methods (e.g. heavy overrides actionDrop() to drop the block twice)

// Impl notes: - Check block class for how to initialize them, and for other info
//             - add method for changing block shape (e.g. debugActionChangeShape)
//             - Need to implement Level class and levelup/down functionality
//             - Need to implement a "blank" version of the board which implements the default functionality for all of those pure virtual functions, e.g. DefaultBoard

class Board {
    friend class Block;

    std::vector<std::vector<Cell>> grid = std::vector<std::vector<Cell>>(15, std::vector<Cell>(11, Cell(nullptr)));
    int score; // Current player score
    Level* level; // Current level
public:
    // Action methods
    virtual void actionClockwise() = 0; // Rotates falling Block clockwise
    virtual void actionCounterclockwise() = 0; // Rotates falling Block counterclockwise
    virtual void actionLeft() = 0; // Moves falling Block left
    virtual void actionRight() = 0; // Moves falling Block right
    virtual void actionDown() = 0; // Moves falling Block down
    virtual void actionDrop() = 0; // Moves falling Block as far down as possible 
    virtual void actionLevelUp() = 0; // Increases the Level by 1
    virtual void actionLevelDown() = 0; // Decreases the Level by 1
};

#endif 
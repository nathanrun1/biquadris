#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include "blockshape.h"
#include "cell.h"

class Board;

class Block {

    // *-- IMPORTANT: Do not modify the 'position' field directly, use changePosition --*
    // std::unique_ptr<BlockShape> shape; // Block's inherent shape -- Commented out rn because might not be necessary for Block to store its shape
    char color; // Block's current color
    std::vector<std::pair<int, int>> position = {}; // Block's current position (i.e. the coordinates of all the cells it currently occupies)
    int initialLevel; // Integer representation of the Level that this Block was initialized in (for scoring purposes)

    Board& board; // Board that this Block exists in

    // changePosition(newPosition) attempts to change the block's currently occupied cells to the cells at the coordinates listed in 'newPosition'.
    //   Checks validity by ensuring all cells located at coordinates in 'newPosition' either are empty or owned by this Block. If successful,
    //   Changes the owner fields of relevant Cells accordingly, and returns true. If unsuccessful, returns false. 
    bool changePosition(std::vector<std::pair<int, int>>& newPosition);

    // getBottomLeft() returns coordinates (relative to the 'grid') of the bottom left corner of the smallest rectangle containing the block
    std::pair<int, int> getBottomLeft();
public:

    // Block(grid, shape, bottomLeftCoordinate, curLevel, success) initializes a Block, existing inside of the provided grid of cells 'grid', with BlockShape 'shape'
    //   and initial position such that the bottom left coordinate of the smallest rectangle containing the block is 'bottomLeftCoordinate'.
    //   If this initial position is invalid, 'grid' is not modified and 'success' is set to false.
    //   Otherwise, 'success' is set to true, the owners of relevant Cells in 'grid' are set accordingly, and 'success' is set to true.
    //   When this Block is cleared, if the initial position was valid, it will score according to the level it was initialized during, provided by 'curLevel'
    Block(Board& board, BlockShape* shape, std::pair<int, int> bottomLeftCoordinate, int curLevel, bool& success);

    // Block's destructor. This destructor is called whenever this Block is cleared from 'grid', i.e. there are no longer any Cells in 'grid' that have 
    //   this Block as their 'owner'.
    ~Block();

    // -- Getters --
    char getColor();

    // -- Actions --
    //   The following methods attempt the corresponding action, checking validity (i.e. collisions) using the provided grid of cells 'grid'.
    //     Each method returns true if the action is successful, or false otherwise. If action unsuccessful, no effect is produced.
    bool rotateClockwise(); // Rotate block clockwise
    bool rotateCounterclockwise(); // Rotate block counterclockwise
    bool left(); // Move block once to the left
    bool right(); // Move block once to the right
    bool down(); // Move block once down

    // drop() Moves this block down as far as possible until a movement down is no longer valid.
    void drop();
    

    // -- Debugging --

    // changeShape(newShape) attempts to change this block's BlockShape to new BlockShape. Preserves the bottom left corner of smallest rectangle containing block.
    //   Checks validity of this change using the provided grid of cells 'grid'. If change successful returns true, 
    //   otherwise returns false and has no effect.
    // bool changeShape(std::unique_ptr<BlockShape> newShape);

    // changeShape(newShape) attempts to change this block's BlockShape to new BlockShape. Preserves the bottom left corner of smallest rectangle containing block.
    //   Checks validity of this change using the provided grid of cells 'grid'. If change successful returns true, 
    //   otherwise returns false and has no effect.
    bool changeShape(BlockShape* newShape);
};

#endif
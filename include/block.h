#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include "blockshape.h"

class Board;

class Block {

    // *-- IMPORTANT: Do not modify the 'position' field directly, use changePosition --*
    // std::unique_ptr<BlockShape> shape; // Block's inherent shape -- Commented out rn because might not be necessary for Block to store its shape
    char color; // Block's current color
    // Block's current position (i.e. the coordinates of all the cells it currently occupies) when it is the current falling Block.
    //   -- IMPORTANT: The value of this field is no longer accurate after the Block has been dropped --
    std::vector<std::pair<int, int>> position = {}; 
    int initialLevel; // Integer representation of the Level that this Block was initialized in (for scoring purposes)

    Board& board; // Board that this Block exists in

    // changePosition(newPosition) attempts to change the block's currently occupied cells to the cells at the coordinates listed in 'newPosition'.
    //   Checks validity by ensuring all cells located at coordinates in 'newPosition' either are empty or owned by this Block. If successful,
    //   Changes the owner fields of relevant Cells accordingly, and returns true. If unsuccessful, returns false. 
    // Precondition: this Block is the current falling block
    bool changePosition(std::vector<std::pair<int, int>>& newPosition);

    // getBottomLeft() returns coordinates (relative to the 'grid') of the bottom left corner of the smallest rectangle containing the block
    std::pair<int, int> getBottomLeft() const;

    public:
        // Block(grid, shape, curLevel) initializes a Block with reference to board 'board', and int value of current
        //   Level 'curLevel'
        Block(Board& board, int curLevel);

        // Block's destructor. This destructor is called whenever this Block is cleared from 'grid', i.e. there are no longer any Cells in 'grid' that have 
        //   this Block as their 'owner'.
        ~Block();

        // spawn(bottomLeftCoordinate) attempts to spawn this Block with BlockShape 'shape' such that the bottom left coordinate of the smallest rectangle containing the
        //   Block is 'bottomLeftCoordinate'. If Block has already been spawned, has no effect. Returns true if spawn is valid and thus successful,
        //   false otherwise. If spawn failed, Block will not score when destroyed, and this method will have no effect if called again.
        // Precondition: 'board' stores this Block as the current falling block, and returns a shared_ptr to this from board.getFallingBlock()
        bool spawn(std::shared_ptr<BlockShape> shape, std::pair<int, int> bottomLeftCoordinate);

        // -- Getters --
        char getColor() const;

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
        bool changeShape(std::shared_ptr<BlockShape> newShape);
};

#endif
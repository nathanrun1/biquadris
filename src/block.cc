#include <algorithm>
#include <cmath>
#include <iostream>
#include "block.h"
#include "board.h"
#include "cell.h"

// yToIndex(y, rows) converts a y coordinate (second value of 2D coordinate) to its index value to use when indexing a Board's grid.
//   Converts coordinate based on total amount of rows (i.e. height of grid)
// int yToIndex(int y, int rows) {
//     return rows - 1 - y;
// }

bool Block::changePosition(std::vector<std::pair<int, int>>& newPosition) {
    if (board.getFallingBlock().get() != this) return false; // This block is not the current falling block, no effect
    std::vector<std::vector<Cell>>& grid = board.getGrid();
    // Check validity
    for (std::pair<int, int>& coordinate : newPosition) {
        // Coordinate out of range, new position is invalid
        if (coordinate.second < 0 || coordinate.second >= grid.size() || coordinate.first < 0 || coordinate.first >= grid[coordinate.second].size()) return false;
        
        // Cell owned by a different Block, new position is invalid
        if (grid[coordinate.second][coordinate.first].owner != nullptr && grid[coordinate.second][coordinate.first].owner.get() != this) return false;
    }
    
    // New position is valid...
    
    // Clear previously occupied cells
    for (std::pair<int, int>& coordinate : position) {
        grid[coordinate.second][coordinate.first].owner.reset();
    }
    

    // Assign ownership of this Block to newly occupied cells
    for (std::pair<int, int>& coordinate : newPosition) {
        grid[coordinate.second][coordinate.first].owner = std::shared_ptr<Block>(board.getFallingBlock()); // copy board's shared_ptr
    }
    position = newPosition; // Set to new position
    return true;
}

std::pair<int, int> Block::getBottomLeft() const {
    // Coordinates of current bottom left corner of smallest rectangle containing block. 
    //   Constructed using the minimum x and y coordinates out of all the block's cells' coordinates.
    return 
    std::pair<int, int>
    {
    std::min_element(position.begin(), position.end(),
    [](const std::pair<int, int>& a, const std::pair<int, int>& b){ return a.first < b.first; })->first
    ,
    std::min_element(position.begin(), position.end(),
    [](const std::pair<int, int>& a, const std::pair<int, int>& b){ return a.second < b.second; })->second
    };
}

Block::Block(Board& board, int curLevel)
    : initialLevel(curLevel), board(board) {

    // std::vector<std::pair<int, int>> newPosition{};
    // for (std::pair<int, int> coordinate : shape->getShape()) {
    //     newPosition.emplace_back(
    //         bottomLeftCoordinate.first + coordinate.first,
    //         bottomLeftCoordinate.second + coordinate.second
    //     );
    // }
    
    // if (changePosition(newPosition)) {
    //     // Initial position is valid
    //     success = true;
    //     color = shape->getColor();
        
    // } else {
    //     // Initial position is invalid, i.e. Block does not go into play
    //     success = false;
    //     initialLevel = -1; // Set level to -1 so that player does not score for an invalid Block.
    // }
}

Block::~Block() {
    // Block has been cleared, score points equal to level block was initialized on + 1, squared
    int scored = std::pow(initialLevel + 1, 2);
    board.getScore() += scored;
}

bool Block::spawn(std::shared_ptr<BlockShape> shape, std::pair<int, int> bottomLeftCoordinate) {
    if (position.size() != 0) return false; // spawn has already been called, since position is not empty
    std::vector<std::pair<int, int>> newPosition{};
    for (std::pair<int, int> coordinate : shape->getShape()) {
        newPosition.emplace_back(
            bottomLeftCoordinate.first + coordinate.first,
            bottomLeftCoordinate.second + coordinate.second
        );
    }
    
    if (changePosition(newPosition)) {
        // Initial position is valid
        color = shape->getColor();
        return true;
    } else {
        // Initial position is invalid, i.e. Block does not go into play
        initialLevel = -1; // Set level to -1 so that player does not score for an invalid Block.
        return false;
    }
}

char Block::getColor() const { 
    // return shape->getColor(); 
    return color;
}

bool Block::rotateClockwise() {
    // Amount of columns in smallest rectangle containing block
    //   Found by adding 1 to the difference between the max and min x coordinates
    int cols = std::max_element(position.begin(), position.end(),
    [&](std::pair<int, int>& a, std::pair<int, int>& b){ return a.first < b.first; })->first - 
    std::min_element(position.begin(), position.end(),
    [&](std::pair<int, int>& a, std::pair<int, int>& b){ return a.first < b.first; })->first + 1;

    std::pair<int, int> curBottomLeft = getBottomLeft();

    // Coordinates of top left corner of smallest rectangle containing the block, after it is rotated clockwise. 
    //   Found by adding the current total occupied columns to the y coordinate of the current bottom left corner. 
    //   This is because occupied columns, after rotation, becomes occupied rows.
    std::pair<int, int> newTopLeft = {curBottomLeft.first, curBottomLeft.second + cols - 1};

    std::vector<std::pair<int, int>> newPosition;
    
    for (std::pair<int, int>& coordinate : position) {

        // Get coordinates relative to the current bottom left corner
        std::pair<int, int> relativeCoordinate = {coordinate.first - curBottomLeft.first, coordinate.second - curBottomLeft.second};

        // To rotate clockwise, we:
        // Add relative y to new top left corner's x
        // Subtract relative x from new top left corner's y
        newPosition.emplace_back(
            newTopLeft.first + relativeCoordinate.second,
            newTopLeft.second - relativeCoordinate.first
        );
    }

    return changePosition(newPosition); // Attempt rotation
}

bool Block::rotateCounterclockwise() {
    // Amount of rows in smallest rectangle containing block
    //   Found by adding 1 to the difference between the max and min y coordinates
    int rows = std::max_element(position.begin(), position.end(),
    [&](std::pair<int, int>& a, std::pair<int, int>& b){ return a.second < b.second; })->second - 
    std::min_element(position.begin(), position.end(),
    [&](std::pair<int, int>& a, std::pair<int, int>& b){ return a.second < b.second; })->second + 1;

    std::pair<int, int> curBottomLeft = getBottomLeft();

    // Coordinates of bottom right corner of smallest rectangle containing the block, after it is rotated counterclockwise. 
    //   Found by adding the current total occupied rows to the x coordinate of the current bottom left corner. 
    //   This is because occupied rows, after rotation, becomes occupied columns.
    std::pair<int, int> newBottomRight = {curBottomLeft.first + rows - 1, curBottomLeft.second};

    std::vector<std::pair<int, int>> newPosition{};
    
    for (std::pair<int, int>& coordinate : position) {

        // Get coordinates relative to the current bottom left corner
        std::pair<int, int> relativeCoordinate = {coordinate.first - curBottomLeft.first, coordinate.second - curBottomLeft.second};

        // To rotate counterclockwise, we:
        // Subtract relative y from new bottom right corner's x
        // Add relative x to new bottom right corner's y
        newPosition.emplace_back(
            newBottomRight.first - relativeCoordinate.second,
            newBottomRight.second + relativeCoordinate.first
        );
    }

    return changePosition(newPosition); // Attempt rotation
}

bool Block::left() {
    std::vector<std::pair<int, int>> newPosition;
    for (std::pair<int, int>& coordinate : position) {
        // To move left, subtract 1 from x coordinate
        newPosition.emplace_back(
            coordinate.first - 1,
            coordinate.second
        );
    }

    return changePosition(newPosition); // Attempt move left
}

bool Block::right() {
    std::vector<std::pair<int, int>> newPosition;
    for (std::pair<int, int>& coordinate : position) {
        // To move right, add 1 to x coordinate
        newPosition.emplace_back(
            coordinate.first + 1,
            coordinate.second
        );
    }

    return changePosition(newPosition); // Attempt move right
}

bool Block::down() {
    std::vector<std::pair<int, int>> newPosition;
    for (std::pair<int, int>& coordinate : position) {
        // To move down, subtract 1 from y coordinate
        newPosition.emplace_back(
            coordinate.first,
            coordinate.second - 1
        );
    }

    return changePosition(newPosition); // Attempt move down
}

void Block::drop() {
    while (down()) {} // Move down until down() returns false (i.e. was invalid)
}


// -- DEBUGGING METHODS --

// bool Block::changeShape(std::unique_ptr<BlockShape> newShape) {
//     std::pair<int, int> curBottomLeft = getBottomLeft();

//     std::vector<std::pair<int, int>> newPosition;
//     for (std::pair<int, int> coordinate : newShape->getShape()) {
//         newPosition.emplace_back(
//             curBottomLeft.first + coordinate.first,
//             curBottomLeft.second + coordinate.second
//         );
//     }

//     if (changePosition(newPosition)) {
//         shape = std::move(newShape);
//         return true;
//     }
//     return false;
// }

bool Block::changeShape(std::shared_ptr<BlockShape> newShape) {
    std::pair<int, int> curBottomLeft = getBottomLeft();

    std::vector<std::pair<int, int>> newPosition;
    for (std::pair<int, int> coordinate : newShape->getShape()) {
        newPosition.emplace_back(
            curBottomLeft.first + coordinate.first,
            curBottomLeft.second + coordinate.second
        );
    }
    if (changePosition(newPosition)) {
        color = newShape->getColor();
        return true;
    }
    return false;
}

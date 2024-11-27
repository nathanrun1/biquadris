#include "board.h"
#include <memory>

bool Board::spawnBlock(std::pair<int, int> bottomLeftCoordinate, std::shared_ptr<BlockShape> shape = nullptr) {
    bool spawnSuccess;
    if (!shape) { shape = level->getNext(); }
    std::shared_ptr<Block> spawnedBlock = std::make_shared<Block>(*this, shape, bottomLeftCoordinate, level->getLevelNum(), spawnSuccess);
    if (spawnSuccess) { fallingBlock = spawnedBlock; }
    return spawnSuccess;
}

int Board::clearLines() {int clearedCount = 0;
    for (std::vector<std::vector<Cell>>::iterator it = grid.begin(); it != grid.end();) {
        std::vector<Cell>& row = *it;

        bool isFull = true; // Whether or not every Cell in this row is non-empty (has a non-null 'owner')        
        for (Cell& cell : row) {
            if (!cell.owner) {
                // Cell is empty, row is not full (should not be cleared)
                isFull = false;
                break;
            }
        }
        if (isFull) {
            // Clear the row, and add an empty row at the top of the grid
            it = grid.erase(it); 
            grid.push_back(std::vector<Cell>(BOARD_COLS, Cell(nullptr)));
            clearedCount++; // Increment count
        } else {
            ++it; // Next row
        }
    }
    return clearedCount;
}

bool ConcreteBoard::actionClockwise() {
    return fallingBlock->rotateClockwise();
}
bool ConcreteBoard::actionCounterclockwise() {
    return fallingBlock->rotateCounterclockwise();
}
bool ConcreteBoard::actionLeft() {
    return fallingBlock->left();
}
bool ConcreteBoard::actionRight() {
    return fallingBlock->right();
} 
bool ConcreteBoard::actionDown() {
    return fallingBlock->down();
}
void ConcreteBoard::actionDrop() {
    fallingBlock->drop();
    clearLines();
    spawnBlock({0, 14}); 
}


/*
void ConcreteBoard::action() {
    std::shared_ptr<BlockShape> block = level->getNext();
    // Block(Board& board, std::shared_ptr<BlockShape> shape, std::pair<int, int> bottomLeftCoordinate, int curLevel, bool& success);
    std::shared_ptr<Block> output = std::make_shared<Block>(*this, block, output.getBottomLeft(), block.getLevel(), true); ???
    fallingBlock = output;
}
*/

void ConcreteBoard::actionRandom() {
    // TO DO
}
void ConcreteBoard::actionNoRandom(std::string file) {
    // TODO
}

char ConcreteBoard::getColorAt(int x, int y) const {
    return grid[y][x].owner->getColor();
}
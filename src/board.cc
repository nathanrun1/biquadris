#include "board.h"
#include <memory>

bool Board::spawnBlock(std::pair<int, int> bottomLeftCoordinate) {
    bool spawnSuccess;
    std::shared_ptr<Block> spawnedBlock = std::make_shared<Block>(*this, level->getNext(), bottomLeftCoordinate, level->getLevelNum(), spawnSuccess);
    if (spawnSuccess) { fallingBlock = spawnedBlock; }
    return spawnSuccess;
}

bool DefaultBoard::actionClockwise() {
    return fallingBlock->rotateClockwise();
}
bool DefaultBoard::actionCounterclockwise() {
    return fallingBlock->rotateCounterclockwise();
}
bool DefaultBoard::actionLeft() {
    return fallingBlock->left();
}
bool DefaultBoard::actionRight() {
    return fallingBlock->right();
} 
bool DefaultBoard::actionDown() {
    return fallingBlock->down();
}
void DefaultBoard::actionDrop() {
    fallingBlock->drop();
    // TODO: check each line to see if all cells are occupied. If so, clear all of the cells in all cleared lines and move all above blocks down
    spawnBlock({0, 14}); 
}
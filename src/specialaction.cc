#include "specialaction.h"
#include "board.h"
#include <stdexcept>

// Base class implementation
SpecialAction::~SpecialAction() {}

// BlindAction implementation
void BlindAction::apply(Board &board) {
    board.setBlind(true);
}

// HeavyAction implementation
void HeavyAction::apply(Board &board) {
    board.setHeavy(2); // Adds a heaviness increment of 2
}

// ForceAction implementation
ForceAction::ForceAction(BlockShape *newBlock) : newBlock(newBlock) {
    if (!newBlock) {
        throw std::invalid_argument("ForceAction requires a valid BlockShape.");
    }
}

void ForceAction::apply(Board &board) {
    Block *forcedBlock = new Block(board.getBoard(), newBlock, {0, 0}, board.getLevel(), true);
    board.forceBlock(forcedBlock);
}

#include "boardmods.h"

BoardModification::BoardModification(Board* component) : component(component) {}

HeavyBoard::HeavyBoard(Board* component) : BoardModification(component) {}

bool HeavyBoard::actionClockwise() {
    return component->actionClockwise();
}
bool HeavyBoard::actionCounterclockwise() {
    return component->actionCounterclockwise();
}
bool HeavyBoard::actionLeft() {
    if (fallingBlock->left()) {
        for (int i = 0; i < 2; ++i) {
            // Attempt to move falling Block down twice. If either of the down movements fail, then force drop the falling Block.
            if (!fallingBlock->down()) {
                actionDrop();
                break;
            }
            return true;
        }
    } 
    else return false;
}
bool HeavyBoard::actionRight() {
    if (fallingBlock->right()) {
        for (int i = 0; i < 2; ++i) {
            // Attempt to move falling Block down twice. If either of the down movements fail, then force drop the falling Block.
            if (!fallingBlock->down()) {
                actionDrop();
                break;
            }
        }
        return true;
    } 
    else return false;
} 
bool HeavyBoard::actionDown() {
    return component->actionDown();
}
void HeavyBoard::actionDrop() {
    component->actionDrop();
}

void HeavyBoard::actionRandom() {
    component->actionRandom();
}
void HeavyBoard::actionNoRandom(std::string file) {
    component->actionNoRandom(file);
}

char HeavyBoard::getColorAt(int x, int y) const {
    component->getColorAt(x, y);
}

BlindBoard::BlindBoard(Board* component) : BoardModification(component) {}

bool BlindBoard::actionClockwise() {
    return component->actionClockwise();
}
bool BlindBoard::actionCounterclockwise() {
    return component->actionCounterclockwise();
}
bool BlindBoard::actionLeft() {
    return component->actionLeft();
}
bool BlindBoard::actionRight() {
    return component->actionRight();
} 
bool BlindBoard::actionDown() {
    return component->actionDown();
}
void BlindBoard::actionDrop() {
    component->actionDrop();
    // TODO: Implement such that this modifier removes itself (i.e. replaces itself with its component in the Game, or in whatever class manages the Board)
}

void BlindBoard::actionRandom() {
    component->actionRandom();
}
void BlindBoard::actionNoRandom(std::string file) {
    component->actionNoRandom(file);
}

char BlindBoard::getColorAt(int x, int y) const {
    if (2 <= x && x <= 8 && 6 <= y && y <= 15) { // Rows 2-11 correspond to indices 15-6 (15 is row 2, 6 is row 11)
        return '?';
    }
    else return component->getColorAt(x, y);
}
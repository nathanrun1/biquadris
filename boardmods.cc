#include "boardmods.h"

BoardModification::BoardModification(Board* component) : component(component) {}

BoardModification::~BoardModification() {}

std::vector<std::vector<Cell>>& BoardModification::getGrid() {
    return component->getGrid();
}
std::shared_ptr<Block>& BoardModification::getFallingBlock() {
    return component->getFallingBlock();
}

int BoardModification::getRowAmnt() const {
    return component->getRowAmnt();
}
int BoardModification::getColAmnt() const {
    return component->getColAmnt();
}
int& BoardModification::getScore() {
    return component->getScore();
}
Level* BoardModification::getLevel() {
    return component->getLevel();
}

HeavyBoard::HeavyBoard(Board* component) : BoardModification(component) {}

bool HeavyBoard::actionClockwise() {
    return component->actionClockwise();
}
bool HeavyBoard::actionCounterclockwise() {
    return component->actionCounterclockwise();
}
bool HeavyBoard::actionLeft() {
    if (component->actionLeft()) {
        for (int i = 0; i < 2; ++i) {
            // Attempt to move falling Block down twice. If either of the down movements fail, then force drop the falling Block.
            if (!component->actionDown()) {
                component->actionDrop();
                break;
            }
            return true;
        }
    } 
    else return false;
}
bool HeavyBoard::actionRight() {
    if (component->actionRight()) {
        for (int i = 0; i < 2; ++i) {
            // Attempt to move falling Block down twice. If either of the down movements fail, then force drop the falling Block.
            if (!component->actionDown()) {
                component->actionDrop();
                break;
            }
            return true;
        }
        return true;
    } 
    else return false;
} 
bool HeavyBoard::actionDown() {
    return component->actionDown();
}
bool HeavyBoard::actionDrop() {
    component->actionDrop();
    return false;
}
void HeavyBoard::actionLevelUp() {
    component->actionLevelUp();
}
void HeavyBoard::actionLevelDown() {
    component->actionLevelDown();
}
void HeavyBoard::actionRandom() {
    component->actionRandom();
}
void HeavyBoard::actionNoRandom(std::string file) {
    component->actionNoRandom(file);
}
char HeavyBoard::getColorAt(int x, int y) const {
    return component->getColorAt(x, y);
}
char HeavyBoard::getColorAtRC(const int row, const int col) const {
    return getColorAt(getRowAmnt() - row - 1, col);
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
bool BlindBoard::actionDrop() {
    component->actionDrop();
    return false;
    // TODO: Implement such that this modifier removes itself (i.e. replaces itself with its component in the Game, or in whatever class manages the Board)
}
void BlindBoard::actionLevelUp() {
    component->actionLevelUp();
}
void BlindBoard::actionLevelDown() {
    component->actionLevelDown();
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
char BlindBoard::getColorAtRC(const int row, const int col) const {
    return getColorAt(getRowAmnt() - row - 1, col);
}
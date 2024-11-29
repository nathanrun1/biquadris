#include "board.h"
#include "level.h"
#include "cell.h"
#include <memory>
#include <iostream>


Board::Board() {}

Board::~Board() {}

bool ConcreteBoard::spawnBlock(std::pair<int, int> bottomLeftCoordinate, std::shared_ptr<BlockShape> shape) {
    if (!shape) { 
        shape = level->checkNext();
        level->getNext(); 
    }
    //std::shared_ptr<Block> spawnedBlock = std::make_shared<Block>(*this, shape, bottomLeftCoordinate, level->getLevelNum(), spawnSuccess);
    std::shared_ptr<Block> spawnedBlock = std::shared_ptr<Block>(new Block(*this, level->getLevelNum()));
    fallingBlock = spawnedBlock;
    bool spawnSuccess = spawnedBlock->spawn(shape, bottomLeftCoordinate);
    if (!spawnSuccess) fallingBlock = nullptr;
    return spawnSuccess;
}

int ConcreteBoard::clearLines() {
    int clearedCount = 0;

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

void ConcreteBoard::setLevelFromNum(const int levelNum, const std::string seqFile) {
    switch (levelNum) {
        case 0: 
            if (level) level = new Level_0(std::move(*level));
            else level = new Level_0(*this, randGen, seqFile, true);
            break;
        case 1: 
            if (level) level = new Level_1(std::move(*level));
            else level = new Level_1(*this, randGen, seqFile, true);
            break;
        case 2: 
            if (level) level = new Level_2(std::move(*level));
            else level = new Level_2(*this, randGen, seqFile, true);
            break;
        case 3: 
            if (level) level = new Level_3(std::move(*level));
            else level = new Level_3(*this, randGen, seqFile, true);
            break;
        case 4: 
            if (level) level = new Level_4(std::move(*level));
            else level = new Level_4(*this, randGen, seqFile, true);
            break;
    }
}

std::vector<std::vector<Cell>>& ConcreteBoard::getGrid() {
    return grid;
}
std::shared_ptr<Block>& ConcreteBoard::getFallingBlock() {
    return fallingBlock;
}

ConcreteBoard::ConcreteBoard(std::mt19937 gen, const int initialLevelNum, const std::string initialSeqFile) 
    : grid(std::vector<std::vector<Cell>>(BOARD_ROWS, std::vector<Cell>(BOARD_COLS, Cell(nullptr)))), randGen(gen) { 
    setLevelFromNum(initialLevelNum, initialSeqFile);
    spawnBlock({0, 14});
}

ConcreteBoard::~ConcreteBoard() {
    delete level;
}

int ConcreteBoard::getRowAmnt() const {
    return grid.size();
}
int ConcreteBoard::getColAmnt() const {
    return grid[0].size();
}
char ConcreteBoard::getColorAtRC(const int row, const int col) const {
    return getColorAt(col, getRowAmnt() - row - 1);
}
int& ConcreteBoard::getScore() {
    return score;
}
Level* ConcreteBoard::getLevel() {
    return level;
}

void ConcreteBoard::setGen(const std::mt19937 newGen) { 
    randGen = newGen; 
}
void ConcreteBoard::setInitialLevelNum(const int newLevel) { 
    setLevelFromNum(newLevel, level->getSeqFile()); 
}
void ConcreteBoard::setInitialSeqFile(const std::string seqFile) { 
    setLevelFromNum(level->getLevelNum(), seqFile);
}

bool ConcreteBoard::actionClockwise() {
    bool result = fallingBlock->rotateClockwise();
    notifyObservers();
    return result;
}
bool ConcreteBoard::actionCounterclockwise() {
    bool result = fallingBlock->rotateCounterclockwise();
    notifyObservers();
    return result;
}
bool ConcreteBoard::actionLeft() {
    bool result = fallingBlock->left();
    notifyObservers();
    return result;
}
bool ConcreteBoard::actionRight() {
    bool result = fallingBlock->right();
    notifyObservers();
    return result;
} 
bool ConcreteBoard::actionDown() {
    bool result = fallingBlock->down();
    notifyObservers();
    return result;
}
bool ConcreteBoard::actionDrop() {
    fallingBlock->drop();
    int amntCleared = clearLines();
    if (amntCleared > 0) level->notifyClear();
    else {
        level->notifyDrop();
        if (level->getLevelNum() == 4) clearLines(); // Extra clear in case Level 4 and the added Dot block fills a line
    }

    bool canSpawn = spawnBlock({0, 14});

    if (canSpawn) { 
        notifyObservers();
        return true;
    } else {
        return false;
    }
}

void ConcreteBoard::actionLevelUp() {
    setLevelFromNum(level->getLevelNum() + 1, level->getSeqFile());
    notifyObservers();
}

void ConcreteBoard::actionLevelDown() {
    setLevelFromNum(level->getLevelNum() - 1, level->getSeqFile());
    notifyObservers();
}

void ConcreteBoard::actionRandom() {
    level->setRandom(true);
    notifyObservers();
}
void ConcreteBoard::actionNoRandom(std::string file) {
    level->setRandom(false);
    level->setSeqFile(file);
    notifyObservers();
}

void ConcreteBoard::actionSetShape(std::shared_ptr<BlockShape>& newShape) {
    fallingBlock->changeShape(newShape);
    notifyObservers();
}

void ConcreteBoard::wipeBoard() {
    // for (std::vector<std::vector<Cell>>::iterator it = grid.begin(); it != grid.end();) {        
    //     it = grid.erase(it);
    //     grid.push_back(std::vector<Cell>(BOARD_COLS, Cell(nullptr)));
    // }
    grid = std::vector<std::vector<Cell>>(BOARD_ROWS, std::vector<Cell>(BOARD_COLS, Cell(nullptr))); // Reset grid to initial state
    spawnBlock({0, 14});
    notifyObservers();
}

char ConcreteBoard::getColorAt(int x, int y) const {
    const Cell& cell = grid[y][x];
    if (cell.owner) return cell.owner->getColor();
    else return ' ';
}
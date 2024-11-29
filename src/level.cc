#include "level.h"
#include "cell.h"
#include <iostream>
#include <memory>

// Helper function charToBlock() to convert characters inside files into various blockshapes
std::shared_ptr<BlockShape> Level::stringToBlock(const std::string s)  const {
    if (s == "I") return std::make_shared<I_Shape>();
    else if (s == "J") return std::make_shared<J_Shape>();
    else if (s == "L") return std::make_shared<L_Shape>();
    else if (s == "O") return std::make_shared<O_Shape>();
    else if (s == "S") return std::make_shared<S_Shape>();
    else if (s == "Z") return std::make_shared<Z_Shape>();
    else if (s == "T") return std::make_shared<T_Shape>();

    return nullptr;
}

// Helper function to simplify code below for reading directly from file.
//     If end of file is reached, open the file again starting from the beginning.
std::shared_ptr<BlockShape> Level::readFromFile() {
    std::string char_block;

    if (fstream >> char_block) {
        return stringToBlock(char_block);
    } else {
        fstream = std::ifstream{seqFile};
        fstream >> char_block;
        return stringToBlock(char_block);
    }
} 

// Level Factory Constructor/Methods -------------------------------------------------------------------------------------------------------
Level::Level(Board& myBoard, std::mt19937& seed, std::string seqFile, bool isRandom):
    myBoard{myBoard}, sinceCleared{0}, seed{seed}, seqFile{seqFile}, fstream{std::ifstream{seqFile}}, isRandom{isRandom} {}

Level::Level(Level&& other) :
    Level(other.myBoard, other.seed, other.seqFile, other.isRandom) {}
void Level::setSeed(const std::mt19937 new_seed) { seed = new_seed; }
void Level::setRandom(const bool r)              { isRandom = r; }
void Level::setSeqFile(const std::string fname)  { seqFile = fname; fstream = std::ifstream{seqFile}; }

std::string Level::getSeqFile() const            { return seqFile; }

void Level::notifyClear() {}
void Level::notifyDrop() {}

// Level Concrete Subclass Constructor/Methods
// Level_0
Level_0::Level_0(Board& myBoard, std::mt19937& seed, std::string seqFile, bool isRandom):
    Level(myBoard, seed, seqFile, isRandom) { currBlock = getNext(); }
Level_0::Level_0(Level&& other) : Level(std::move(other)) {}

int Level_0::getLevelNum() const { return 0; }
std::shared_ptr<BlockShape> Level_0::checkNext() const { return currBlock; }
std::shared_ptr<BlockShape> Level_0::getNext() { currBlock = readFromFile(); return currBlock; }

// Level_1
Level_1::Level_1(Board& myBoard, std::mt19937& seed, std::string seqFile, bool isRandom):
    Level(myBoard, seed, seqFile, isRandom) { currBlock = getNext(); }
Level_1::Level_1(Level&& other) : Level(std::move(other)) {}

int Level_1::getLevelNum() const { return 1; }
std::shared_ptr<BlockShape> Level_1::checkNext() const { return currBlock; }
std::shared_ptr<BlockShape> Level_1::getNext() {
    int randNum = seed() % 12;
    if (randNum == 0 || randNum == 1)         currBlock = std::make_shared<I_Shape>();
    else if (randNum == 2 || randNum == 3)    currBlock = std::make_shared<J_Shape>();
    else if (randNum == 4 || randNum == 5)    currBlock = std::make_shared<L_Shape>();
    else if (randNum == 6 || randNum == 7)    currBlock = std::make_shared<O_Shape>();
    else if (randNum == 8)                    currBlock = std::make_shared<S_Shape>();
    else if (randNum == 9)                    currBlock = std::make_shared<Z_Shape>();
    else if (randNum == 10 || randNum == 11)  currBlock = std::make_shared<T_Shape>();
    return currBlock;
}

// Level_2
Level_2::Level_2(Board& myBoard, std::mt19937& seed, std::string seqFile, bool isRandom):
    Level(myBoard, seed, seqFile, isRandom) { currBlock = getNext(); }
Level_2::Level_2(Level&& other) : Level(std::move(other)) {}

int Level_2::getLevelNum() const { return 2; }
std::shared_ptr<BlockShape> Level_2::checkNext() const { return currBlock; }
std::shared_ptr<BlockShape> Level_2::getNext() {
    if (!isRandom) { 
        currBlock = readFromFile(); 
        return currBlock;
    }

    int randNum = seed() % 7;
    if (randNum == 0)         currBlock = std::make_shared<I_Shape>();
    else if (randNum == 1)    currBlock = std::make_shared<J_Shape>();
    else if (randNum == 2)    currBlock = std::make_shared<L_Shape>();
    else if (randNum == 3)    currBlock = std::make_shared<O_Shape>();
    else if (randNum == 4)    currBlock = std::make_shared<S_Shape>();
    else if (randNum == 5)    currBlock = std::make_shared<Z_Shape>();
    else if (randNum == 6)    currBlock = std::make_shared<T_Shape>();
    return currBlock;
}

// Level_3
Level_3::Level_3(Board& myBoard, std::mt19937& seed, std::string seqFile, bool isRandom):
    Level(myBoard, seed, seqFile, isRandom) { currBlock = getNext(); }
Level_3::Level_3(Level&& other) : Level(std::move(other)) {}

int Level_3::getLevelNum() const { return 3; }
std::shared_ptr<BlockShape> Level_3::checkNext() const { return currBlock; }
std::shared_ptr<BlockShape> Level_3::getNext() {
    if (!isRandom) { 
        currBlock = readFromFile(); 
        return currBlock;
    } 

    int randNum = seed() % 9;
    if (randNum == 0)                        currBlock = std::make_shared<I_Shape>();
    else if (randNum == 1)                   currBlock = std::make_shared<J_Shape>();
    else if (randNum == 2)                   currBlock = std::make_shared<L_Shape>();
    else if (randNum == 3)                   currBlock = std::make_shared<O_Shape>();
    else if (randNum == 4 || randNum == 5)   currBlock = std::make_shared<S_Shape>();
    else if (randNum == 6 || randNum == 7)   currBlock = std::make_shared<Z_Shape>();
    else if (randNum == 8)                   currBlock = std::make_shared<T_Shape>();
    return currBlock;
}


// Level_4
Level_4::Level_4(Board& myBoard, std::mt19937& seed, std::string seqFile, bool isRandom):
    Level(myBoard, seed, seqFile, isRandom) { currBlock = getNext(); }
Level_4::Level_4(Level&& other) : Level(std::move(other)) {}

void Level_4::notifyClear() {
    sinceCleared = 0;
}
void Level_4::notifyDrop() {
    sinceCleared++;
    if (sinceCleared >= 5) { 
        sinceCleared = 0;
        std::vector<std::vector<Cell>> grid = myBoard.getGrid();
        int middleCol = (grid[0].size() - 1) / 2;
        for (int y = 0; y < grid.size(); ++y) {
            if (grid[y][middleCol].owner == nullptr) {
                std::shared_ptr<Block> newBlock = std::shared_ptr<Block>(new Block(myBoard, getLevelNum()));
                newBlock->spawn(std::make_shared<Dot_Shape>(), std::pair<int, int>(middleCol, y));
            }
        }
    }
}

int Level_4::getLevelNum() const { return 4; }
std::shared_ptr<BlockShape> Level_4::checkNext() const { return currBlock; }
std::shared_ptr<BlockShape> Level_4::getNext() {
    if (!isRandom) { 
        currBlock = readFromFile(); 
        return currBlock;
    }

    int randNum = seed() % 9;
    if (randNum == 0)                        currBlock = std::make_shared<I_Shape>();
    else if (randNum == 1)                   currBlock = std::make_shared<J_Shape>();
    else if (randNum == 2)                   currBlock = std::make_shared<L_Shape>();
    else if (randNum == 3)                   currBlock = std::make_shared<O_Shape>();
    else if (randNum == 4 || randNum == 5)   currBlock = std::make_shared<S_Shape>();
    else if (randNum == 6 || randNum == 7)   currBlock = std::make_shared<Z_Shape>();
    else if (randNum == 8)                   currBlock = std::make_shared<T_Shape>();
    return currBlock;
}
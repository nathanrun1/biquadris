#include "../include/blockshape.h"
#include "../include/level.h"

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
Level::Level(Board* my_board, std::string seqFile, std::mt19937 seed, bool isRandom):
    my_board{my_board}, turnsLastCleared{0}, seqFile{seqFile}, fstream{std::ifstream{seqFile}}, seed{seed}, isRandom{isRandom} {}

void Level::setSeed(const std::mt19937 new_seed) { seed = new_seed; }
void Level::setRandom(const bool r)              { isRandom = r; }
void Level::setSeqFile(const std::string fname)  { seqFile = fname; fstream = std::ifstream{seqFile}; }
void Level::incrementCounter()                   { turnsLastCleared++; }
void Level::resetCounter()                       { turnsLastCleared = 0; }

// Level Concrete Subclass Constructor/Methods
int Level_0::getLevelNum() const { return 0; }
std::shared_ptr<BlockShape> Level_0::getNext() {
    return readFromFile();
}

int Level_1::getLevelNum() const { return 1; }
std::shared_ptr<BlockShape> Level_1::getNext() {
    if (isRandom) return readFromFile();   

    int randNum = seed() % 12;
    if (randNum == 0 || randNum == 1)         return std::make_shared<I_Shape>();
    else if (randNum == 2 || randNum == 3)    return std::make_shared<J_Shape>();
    else if (randNum == 4 || randNum == 5)    return std::make_shared<L_Shape>();
    else if (randNum == 6 || randNum == 7)    return std::make_shared<O_Shape>();
    else if (randNum == 8)                    return std::make_shared<S_Shape>();
    else if (randNum == 9)                    return std::make_shared<Z_Shape>();
    else if (randNum == 10 || randNum == 11)  return std::make_shared<T_Shape>();
    return nullptr;
}

int Level_2::getLevelNum() const { return 2; }
std::shared_ptr<BlockShape> Level_2::getNext() {
    if (isRandom) return readFromFile();

    int randNum = seed() % 7;
    if (randNum == 0)         return std::make_shared<I_Shape>();
    else if (randNum == 1)    return std::make_shared<J_Shape>();
    else if (randNum == 2)    return std::make_shared<L_Shape>();
    else if (randNum == 3)    return std::make_shared<O_Shape>();
    else if (randNum == 4)    return std::make_shared<S_Shape>();
    else if (randNum == 5)    return std::make_shared<Z_Shape>();
    else if (randNum == 6)    return std::make_shared<T_Shape>();
    return nullptr;
}

int Level_3::getLevelNum() const { return 3; }
std::shared_ptr<BlockShape> Level_3::getNext() {
    if (isRandom) return readFromFile();  

    int randNum = seed() % 9;
    if (randNum == 0)                        return std::make_shared<I_Shape>();
    else if (randNum == 1)                   return std::make_shared<J_Shape>();
    else if (randNum == 2)                   return std::make_shared<L_Shape>();
    else if (randNum == 3)                   return std::make_shared<O_Shape>();
    else if (randNum == 4 || randNum == 5)   return std::make_shared<S_Shape>();
    else if (randNum == 6 || randNum == 7)   return std::make_shared<Z_Shape>();
    else if (randNum == 8)                   return std::make_shared<T_Shape>();
    return nullptr;
}


int Level_4::getLevelNum() const { return 4; }
std::shared_ptr<BlockShape> Level_4::getNext() {
    if (isRandom) return readFromFile();  

    int randNum = seed() % 9;
    if (randNum == 0)                        return std::make_shared<I_Shape>();
    else if (randNum == 1)                   return std::make_shared<J_Shape>();
    else if (randNum == 2)                   return std::make_shared<L_Shape>();
    else if (randNum == 3)                   return std::make_shared<O_Shape>();
    else if (randNum == 4 || randNum == 5)   return std::make_shared<S_Shape>();
    else if (randNum == 6 || randNum == 7)   return std::make_shared<Z_Shape>();
    else if (randNum == 8)                   return std::make_shared<T_Shape>();
    return nullptr;
}
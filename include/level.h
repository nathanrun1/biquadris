#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <random>

#include "board.h"
#include "blockshape.h"

// Factory Class for Level --
class Level {
    protected:
        Board* my_board;
        int turnsLastCleared;

        std::string seqFile;
        std::ifstream fstream;
        std::mt19937 seed;
        bool isRandom;
        
        // Helper functions for majority of public functions below:
        std::shared_ptr<BlockShape> stringToBlock(const std::string s) const;
        std::shared_ptr<BlockShape> readFromFile();

    public:
        Level(Board* my_board, std::string seqFile, std::mt19937 seed, bool isRandom);
        ~Level() = default;

        void setSeed(const std::mt19937 new_seed);
        void setRandom(const bool r);
        void setSeqFile(const std::string fname);
        void incrementCounter();
        void resetCounter();

        virtual int getLevelNum() const;
        virtual std::shared_ptr<BlockShape> getNext();


};

// Concrete Claseses Level 0 - 4:
//     Returns the level number (for score calculations) and blocks
class Level_0: public Level {
    int getLevelNum() const;
    std::shared_ptr<BlockShape> getNext();
};

class Level_1: public Level {
    int getLevelNum() const;
    std::shared_ptr<BlockShape> getNext();
};

class Level_2: public Level {
    int getLevelNum() const;
    std::shared_ptr<BlockShape> getNext();
};

class Level_3: public Level {
    int getLevelNum() const;
    std::shared_ptr<BlockShape> getNext();
};


class Level_4: public Level {
    int getLevelNum() const;
    std::shared_ptr<BlockShape> getNext();
};

#endif
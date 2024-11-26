#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>;

#include "board.h"
#include "blockshape.h"

// Factory Class for Level --
class Level {
    std::string seqFile;
    std::ifstream fstream;
    bool isRandom;

    Board* my_board;
    int turnsLastCleared;

    public:
        Level(Board* board, std::string seqFile, bool isRandom);
        Level(const Level& other);
        Level(Level&& other);
        virtual ~Level() = default;

        Level& operator=(const Level& other);
        Level& operator=(Level&& other);

        void setRandom(bool isRandom);
        void setSeqFile(std::string fname);
        // void incrementCounter();
        // void clearCounter();

        Board* getBoard();
        virtual int getLevelNum();
        virtual std::shared_ptr<BlockShape> getNext();


};


// Concrete Claseses Level 0 - 4 --
//     Returns the level number (for score calculations) and blocks
class Level_0: public Level {
    int getLevelNum();
    std::shared_ptr<BlockShape> getNext();
};

class Level_1: public Level {
    int getLevelNum();
    std::shared_ptr<BlockShape> getNext();
};

class Level_2: public Level {
    int getLevelNum();
    std::shared_ptr<BlockShape> getNext();
};

class Level_3: public Level {
    int getLevelNum();
    std::shared_ptr<BlockShape> getNext();
};

/*
class Level_4: public Level {
    int getLevelNum();
    std::shared_ptr<BlockShape> getNext();
};
*/

#endif
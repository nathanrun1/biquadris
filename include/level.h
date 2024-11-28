#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <random>

#include "board.h"
#include "blockshape.h"

// Factory Class for Level --
class Level {
    protected:
        Board& myBoard;
        int turnsLastCleared;
        
        std::mt19937& seed;
        std::string seqFile;
        std::ifstream fstream;
        std::shared_ptr<BlockShape> currBlock;
        bool isRandom;
        
        // Helper functions for majority of public functions below:
        std::shared_ptr<BlockShape> stringToBlock(const std::string s) const;
        std::shared_ptr<BlockShape> readFromFile();

    public:
        Level(Board& myBoard, std::mt19937& seed, std::string seqFile, bool isRandom);
        Level(const Level& other) = delete;
        Level(Level&& other);
        virtual ~Level() = default;

        void setSeed(const std::mt19937 newSeed);
        void setRandom(const bool r);
        void setSeqFile(const std::string fname);
        void incrementCounter();
        void resetCounter();

        virtual int getLevelNum() const = 0;
        virtual std::shared_ptr<BlockShape> checkNext() const = 0;
        virtual std::shared_ptr<BlockShape> getNext() = 0;
};

// Concrete Claseses Level 0 - 4:
//     Returns the level number (for score calculations) and blocks
class Level_0: public Level {
    public:
        Level_0(Board& myBoard, std::mt19937& randGen, std::string seqFile, bool isRandom);
        Level_0(Level&& other);

        int getLevelNum() const override;
        std::shared_ptr<BlockShape> checkNext() const;
        std::shared_ptr<BlockShape> getNext() override;
};

class Level_1: public Level {
    public:
        Level_1(Board& myBoard, std::mt19937& randGen, std::string seqFile, bool isRandom);
        Level_1(Level&& other);

        int getLevelNum() const override;
        std::shared_ptr<BlockShape> checkNext() const;
        std::shared_ptr<BlockShape> getNext() override;
};

class Level_2: public Level {
    public:
        Level_2(Board& myBoard, std::mt19937& randGen, std::string seqFile, bool isRandom);
        Level_2(Level&& other);

        int getLevelNum() const override;
        std::shared_ptr<BlockShape> checkNext() const;
        std::shared_ptr<BlockShape> getNext() override;
};

class Level_3: public Level {
    public:
        Level_3(Board& myBoard, std::mt19937& randGen, std::string seqFile, bool isRandom);
        Level_3(Level&& other);

        int getLevelNum() const override;
        std::shared_ptr<BlockShape> checkNext() const;
        std::shared_ptr<BlockShape> getNext() override;
};

class Level_4: public Level {
    public:
        Level_4(Board& myBoard, std::mt19937& randGen, std::string seqFile, bool isRandom);
        Level_4(Level&& other);

        int getLevelNum() const override;
        std::shared_ptr<BlockShape> checkNext() const;
        std::shared_ptr<BlockShape> getNext() override;
};

#endif
#ifndef BOARDMODS_H
#define BOARDMODS_H

#include "board.h"
// -- BOARD MODIFICATIONS --
// Definitions for Decorators of Board that implement special gameplay modifications


class BoardModification : public Board { // Base Decorator class for Board modifications
    protected:
        Board* component;
    public:
        BoardModification(Board* component);
        virtual ~BoardModification();

        int getRowAmnt() const override; 
        int getColAmnt() const override; 
        int& getScore() override; 
        Level* getLevel() override;
        std::vector<std::vector<Cell>>& getGrid() override;
        std::shared_ptr<Block>& getFallingBlock() override;
};

// Heavy: Every time a player moves a block left or right, the block automatically falls by two rows, after the horizontal
// move. If it is not possible for the block to drop two rows, it is considered to be dropped, and the turn ends.
class HeavyBoard : public BoardModification { 
    public:
        HeavyBoard(Board* component);

        bool actionClockwise() override; 
        bool actionCounterclockwise() override; 
        bool actionLeft() override; 
        bool actionRight() override; 
        bool actionDown() override; 
        bool actionDrop() override; 
        void actionLevelUp() override;
        void actionLevelDown() override;

        void actionRandom() override; 
        void actionNoRandom(std::string file) override;

        char getColorAt(int x, int y) const override;
        char getColorAtRC(const int row, const int col) const override;
};

// Blind: The player’s board, from columns 3-9, and from rows 3-12, is covered with question marks (?), until the player
// drops a block; then the display reverts to normal.
class BlindBoard : public BoardModification {
    public:
        BlindBoard(Board* component);

        bool actionClockwise() override; 
        bool actionCounterclockwise() override; 
        bool actionLeft() override; 
        bool actionRight() override; 
        bool actionDown() override; 
        bool actionDrop() override; 
        void actionLevelUp() override;
        void actionLevelDown() override;

        void actionRandom() override; 
        void actionNoRandom(std::string file) override;

        char getColorAt(int x, int y) const override;
        char getColorAtRC(const int row, const int col) const override;
};

#endif
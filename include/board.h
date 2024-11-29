#ifndef BOARD_H
#define BOARD_H
#include <chrono>
#include <string>
#include <random>
#include "block.h"
#include "subject.h"

// INTENTION: Implement Board as an abstract base class, since it will be the concrete object for the decorator pattern
//   i.e. special actions will act as decorators on board, overriding one of those action methods (e.g. heavy overrides actionDrop() to drop the block twice)

// Impl notes: - Check block class for how to initialize them, and for other info
//             - add method for changing block shape (e.g. debugActionChangeShape)
//             - Need to implement Level class and levelup/down functionality
//             - Need to implement a "blank" version of the board which implements the default functionality for all of those pure virtual functions, e.g. DefaultBoard

const int BOARD_ROWS = 18;
const int BOARD_COLS = 11;

class Cell;
class Level;

class Board : public Subject {
public:
    Board();
    virtual ~Board();

    // -- Getters --
    virtual int getRowAmnt() const = 0; // Returns amount of rows in board grid
    virtual int getColAmnt() const = 0; // Returns amount of columns in board grid
    virtual int& getScore() = 0; // Returns player's current score by reference
    virtual Level* getLevel() = 0; // Returns level
    // getColorAtRC(row, col) returns the character that should be displayed at the specified row and column
    virtual char getColorAtRC(const int row, const int col) const = 0; 
    // getGrid() returns this Board's grid for the purpose of direct modification. 
    virtual std::vector<std::vector<Cell>>& getGrid() = 0;
    // getFallingBlock() returns this Board's current falling Block for purpose of direct interaction. 
    virtual std::shared_ptr<Block>& getFallingBlock() = 0;

    // -- Setters --
    virtual void setGen(const std::mt19937 newGen) = 0;                  // Sets the generator
    virtual void setInitialLevelNum(const int newLevel) = 0;             // Sets the Board's initial level
    virtual void setInitialSeqFile(const std::string seqFile) = 0;       // Sets the Board's sequence file

    // -- Action methods (to be implemented by decorators), along with documentation of default effects --
    //   if returns bool, return value represents whether or not action was successful
    virtual bool actionClockwise() = 0; // Rotates falling Block clockwise
    virtual bool actionCounterclockwise() = 0; // Rotates falling Block counterclockwise
    virtual bool actionLeft() = 0; // Moves falling Block left
    virtual bool actionRight() = 0; // Moves falling Block right
    virtual bool actionDown() = 0; // Moves falling Block down
    virtual void actionDrop() = 0; // Moves falling Block as far down as possible 
    virtual void actionLevelUp() = 0; // Increases the Level by 1
    virtual void actionLevelDown() = 0; // Decreases the Level by 1

    virtual void actionRandom() = 0; // Restores randomness for relevant Levels
    virtual void actionNoRandom(std::string file) = 0; // Makes relevant Levels non-random, taking input from provided file.

    // -- Display methods --
    // showBoard() notifies the attatched observers
    virtual void showBoard() = 0;

    // getColorAt(x, y) returns the character that should be displayed at the specified (x,y) coordinates.
    //   Note that x increases to the right, y increases upward (e.g. bottom left corner of grid is (0,0)).
    virtual char getColorAt(int x, int y) const = 0;
};

class ConcreteBoard : public Board {
    std::vector<std::vector<Cell>> grid;
    int score; // Current player score
    Level* level; // Current level
    std::shared_ptr<Block> fallingBlock; // Current falling block 
    std::mt19937& randGen;

    // spawnBlock(bottomLeftCoordinate) attempts to spawn a Block such that the bottom left corner of the smallest rectangle containing the Block
    //   is located at 'bottomLeftCoordinate', and set this Block as the current falling Block. If successful, returns true. Otherwise, returns false
    //   and has no effect. spawnBlock will fail (i.e. return false) when the desired position to spawn the Block is occupied by another Block.
    //   If shape provided, spawns the Block using the provided shape. Otherwise, generates a shape from the current Level's getNext() method.
    bool spawnBlock(std::pair<int, int> bottomLeftCoordinate, std::shared_ptr<BlockShape> shape = nullptr);

    // clearLines() checks if any rows on the grid should be cleared, i.e. all Cells in that row have a non-null 'owner'. If so,
    //   for each such row, sets nullifies the 'owner' field in each Cell it contains, and "move all above Blocks" down by one.
    //   Returns total amount of cleared lines.
    int clearLines();

    // setLevelFromNum(levelNum) sets the level (i.e. the type of 'level') based on the provided levelNum.
    //   e.g. levelNum = 1 -> level is converted to type Level_1. If levelNum is not a valid Level type, has no effect.
    void setLevelFromNum(const int levelNum, const std::string seqFile = "");
public:
    ConcreteBoard(std::mt19937 gen = std::mt19937(std::chrono::system_clock::now().time_since_epoch().count()), const int initialLevelNum = 1, std::string initialSeqFile = "");
    ~ConcreteBoard();

    int getRowAmnt() const override; 
    int getColAmnt() const override; 
    int& getScore() override; 
    Level* getLevel() override; 
    char getColorAtRC(const int row, const int col) const override;
    std::vector<std::vector<Cell>>& getGrid() override;
    std::shared_ptr<Block>& getFallingBlock() override; 

    void setGen(const std::mt19937 newGen) override;
    void setInitialLevelNum(const int newLevel) override;
    void setInitialSeqFile(const std::string seqFile) override;

    bool actionClockwise() override; 
    bool actionCounterclockwise() override; 
    bool actionLeft() override; 
    bool actionRight() override; 
    bool actionDown() override; 
    void actionDrop() override; 
    void actionLevelUp() override;
    void actionLevelDown() override;

    void actionRandom() override; 
    void actionNoRandom(std::string file) override;

    void showBoard() override;
    char getColorAt(int x, int y) const override;
};

#endif 
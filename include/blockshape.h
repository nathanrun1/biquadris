#ifndef BLOCKSHAPE_H
#define BLOCKSHAPE_H

#include <map>
#include <vector>

struct BlockShape {
    // getColor() returns the "color" (i.e. the character) that this block is visually constructed with
    virtual char getColor() = 0;

    // getShape() returns a vector of 2D coordinates defining the initial configuration of this block shape, treating
    //    the bottom left corner of the smallest rectangle containing the initial configuration as the coordinate (0,0).
    //    Each 2D coordinate in the vector represents a the relative position of a cell occupied by a block of this shape.
    virtual std::vector<std::pair<int, int>> getShape() = 0;

    virtual ~BlockShape() {}
};

// Concrete block shapes

struct I_Shape : public BlockShape {
    char getColor() override;
    std::vector<std::pair<int, int>> getShape() override;
};

struct J_Shape : public BlockShape {
    char getColor() override;
    std::vector<std::pair<int, int>> getShape() override;
};

struct S_Shape : public BlockShape {
    char getColor() override;
    std::vector<std::pair<int, int>> getShape() override;
};

struct Z_Shape : public BlockShape {
    char getColor() override;
    std::vector<std::pair<int, int>> getShape() override;
};

struct L_Shape : public BlockShape {
    char getColor() override;
    std::vector<std::pair<int, int>> getShape() override;
};

struct T_Shape : public BlockShape {
    char getColor() override;
    std::vector<std::pair<int, int>> getShape() override;
};

struct O_Shape : public BlockShape {
    char getColor() override;
    std::vector<std::pair<int, int>> getShape() override;
};

struct Dot_Shape : public BlockShape {
    char getColor() override;
    std::vector<std::pair<int, int>> getShape() override;
};

struct Custom_Shape : public BlockShape {
    char color;
    std::vector<std::pair<int, int>> shape;

    Custom_Shape(char color, std::vector<std::pair<int, int>> shape);

    char getColor() override;
    std::vector<std::pair<int, int>> getShape() override;
};

#endif
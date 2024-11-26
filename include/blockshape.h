#ifndef BLOCKSHAPE_H
#define BLOCKSHAPE_H

#include <map>
#include <vector>

struct BlockShape {
    // getColor() returns the "color" (i.e. the character) that this block is visually constructed with
    virtual char getColor() const = 0;

    // getShape() returns a vector of 2D coordinates defining the initial configuration of this block shape, treating
    //    the bottom left corner of the smallest rectangle containing the initial configuration as the coordinate (0,0).
    //    Each 2D coordinate in the vector represents a the relative position of a cell occupied by a block of this shape.
    virtual std::vector<std::pair<int, int>> getShape() const = 0;

    virtual ~BlockShape() {}
};

// Concrete block shapes

struct I_Shape : public BlockShape {
    char getColor() const override;
    std::vector<std::pair<int, int>> getShape() const override;
};

struct J_Shape : public BlockShape {
    char getColor() const override;
    std::vector<std::pair<int, int>> getShape() const override;
};

struct S_Shape : public BlockShape {
    char getColor() const override;
    std::vector<std::pair<int, int>> getShape() const override;
};

struct Z_Shape : public BlockShape {
    char getColor() const override;
    std::vector<std::pair<int, int>> getShape() const override;
};

struct L_Shape : public BlockShape {
    char getColor() const override;
    std::vector<std::pair<int, int>> getShape() const override;
};

struct T_Shape : public BlockShape {
    char getColor() const override;
    std::vector<std::pair<int, int>> getShape() const override;
};

struct O_Shape : public BlockShape {
    char getColor() const override;
    std::vector<std::pair<int, int>> getShape() const override;
};

struct Dot_Shape : public BlockShape {
    char getColor() const override;
    std::vector<std::pair<int, int>> getShape() const override;
};

struct Custom_Shape : public BlockShape {
    char color;
    std::vector<std::pair<int, int>> shape;

    Custom_Shape(char color, std::vector<std::pair<int, int>> shape);

    char getColor() const override;
    std::vector<std::pair<int, int>> getShape() const override;
};

#endif
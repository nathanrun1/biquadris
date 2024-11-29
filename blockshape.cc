#include "blockshape.h"

// IIII
char I_Shape::getColor() const {
    return 'I';
}
std::vector<std::pair<int, int>> I_Shape::getShape() const {
    return {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
}


// J
// JJJ
char J_Shape::getColor() const {
    return 'J';
}
std::vector<std::pair<int, int>> J_Shape::getShape() const {
    return {{0, 1}, {0, 0}, {1, 0}, {2, 0}};
}

//  SS
// SS
char S_Shape::getColor() const {
    return 'S';
}
std::vector<std::pair<int, int>> S_Shape::getShape() const {
    return {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
}

// ZZ
//  ZZ
char Z_Shape::getColor() const {
    return 'Z';
}
std::vector<std::pair<int, int>> Z_Shape::getShape() const {
    return {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
}

//   L
// LLL
char L_Shape::getColor() const {
    return 'L';
}
std::vector<std::pair<int, int>> L_Shape::getShape() const {
    return {{0, 0}, {1, 0}, {2, 0}, {2, 1}};
}

// TTT
//  T
char T_Shape::getColor() const {
    return 'T';
}
std::vector<std::pair<int, int>> T_Shape::getShape() const {
    return {{0, 1}, {1, 1}, {2, 1}, {1, 0}};
}

// OO
// OO
char O_Shape::getColor() const {
    return 'O';
}
std::vector<std::pair<int, int>> O_Shape::getShape() const {
    return {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
}

// D
char Dot_Shape::getColor() const {
    return '*';
}
std::vector<std::pair<int, int>> Dot_Shape::getShape() const {
    return {{0, 0}};
}

// Custom (Created by user)
Custom_Shape::Custom_Shape(char color, std::vector<std::pair<int, int>> shape) : color{color}, shape{shape} {}

char Custom_Shape::getColor() const { return color; }
std::vector<std::pair<int, int>> Custom_Shape::getShape() const { return shape; }

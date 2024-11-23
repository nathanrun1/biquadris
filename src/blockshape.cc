#include "blockshape.h"

// IIII
char I_Shape::getColor() {
    return 'I';
}
std::vector<std::pair<int, int>> I_Shape::getShape() {
    return {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
}


// J
// JJJ
char J_Shape::getColor() {
    return 'J';
}
std::vector<std::pair<int, int>> J_Shape::getShape() {
    return {{0, 1}, {0, 0}, {1, 0}, {2, 0}};
}

//  SS
// SS
char S_Shape::getColor() {
    return 'S';
}
std::vector<std::pair<int, int>> S_Shape::getShape() {
    return {{0, 0}, {1, 0}, {1, 1}, {2, 1}};
}

// ZZ
//  ZZ
char Z_Shape::getColor() {
    return 'Z';
}
std::vector<std::pair<int, int>> Z_Shape::getShape() {
    return {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
}

//   L
// LLL
char L_Shape::getColor() {
    return 'L';
}
std::vector<std::pair<int, int>> L_Shape::getShape() {
    return {{0, 0}, {1, 0}, {2, 0}, {2, 1}};
}

// TTT
//  T
char T_Shape::getColor() {
    return 'T';
}
std::vector<std::pair<int, int>> T_Shape::getShape() {
    return {{0, 1}, {1, 1}, {2, 1}, {1, 0}};
}

// OO
// OO
char O_Shape::getColor() {
    return 'O';
}
std::vector<std::pair<int, int>> O_Shape::getShape() {
    return {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
}

// D
char Dot_Shape::getColor() {
    return '*';
}
std::vector<std::pair<int, int>> Dot_Shape::getShape() {
    return {{0, 0}};
}

// Custom (Created by user)
Custom_Shape::Custom_Shape(char color, std::vector<std::pair<int, int>> shape) : color{color}, shape{shape} {}

char Custom_Shape::getColor() { return color; }
std::vector<std::pair<int, int>> Custom_Shape::getShape() { return shape; }

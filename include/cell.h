#ifndef CELL_H
#define CELL_H
#include <memory>
#include "block.h"

struct Cell {
    std::shared_ptr<Block> owner = nullptr;
};

#endif
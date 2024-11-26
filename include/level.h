#ifndef LEVEL_H
#define LEVEL_H
#include "blockshape.h"

class Level {
public:
    int getLevelNum();
    std::shared_ptr<BlockShape> getNext();
    
};

#endif
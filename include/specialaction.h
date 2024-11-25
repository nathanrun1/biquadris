// specialaction.h
#ifndef SPECIALACTION_H
#define SPECIALACTION_H

#include "board.h"

class SpecialAction {
public:
    virtual void apply(Board &board) = 0;
    virtual ~SpecialAction() = default;
};

class BlindAction : public SpecialAction {
public:
    void apply(Board &board) override;
};

class HeavyAction : public SpecialAction {
public:
    void apply(Board &board) override;
};

class ForceAction : public SpecialAction {
    char blockType; // The type of block to force
public:
    explicit ForceAction(char blockType);
    void apply(Board &board) override;
};

#endif // SPECIALACTION_H

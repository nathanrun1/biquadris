#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "observer.h"
#include "game.h"
#include <memory>
#include <iostream>

class TextObserver : public Observer {
private:
    std::ostream& output;
    std::shared_ptr<Game> controller;

public:
    explicit TextObserver(std::ostream& output, std::shared_ptr<Game> c);
    void notify() override;
    ~TextObserver() override;
};

#endif // TEXTOBSERVER_H

#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H

#include "observer.h"
#include "board.h"
#include "graphicalwindow.h"

class GraphicsObserver : public Observer {
private:
    Board *board;
    GraphicalWindow *window;

public:
    explicit GraphicsObserver(Board *board);
    void notify() override;
    ~GraphicsObserver() override;
};

#endif // GRAPHICSOBSERVER_H

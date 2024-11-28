/*#ifndef GRAPHICS_OBSERVER_H
#define GRAPHICS_OBSERVER_H

#include "observer.h"
#include "studio.h"
#include "window.h"

class GraphicsObserver : public Observer {
    Studio &studio;
    int top, bottom, left, right;
    Xwindow window;

public:
    GraphicsObserver(Studio &studio, int top, int bottom, int left, int right);
    void notify() override;
};

#endif*/

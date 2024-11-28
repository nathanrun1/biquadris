#ifndef GRAPHICALWINDOW_H
#define GRAPHICALWINDOW_H

#include <string>
#include <X11/Xlib.h>

class GraphicalWindow {
private:
    Display *display;
    int screen;
    Window rootWindow;
    GC gc;

public:
    explicit GraphicalWindow(int width = 500, int height = 500);
    void drawRectangle(int x, int y, int width, int height, unsigned long color);
    void clear();
    ~GraphicalWindow();
};

#endif // GRAPHICALWINDOW_H

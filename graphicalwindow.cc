/*#include "graphicalwindow.h"
#include <stdexcept>

GraphicalWindow::GraphicalWindow(int width, int height) {
    display = XOpenDisplay(nullptr);
    if (!display) throw std::runtime_error("Unable to open X display");

    screen = DefaultScreen(display);
    rootWindow = XCreateSimpleWindow(display, RootWindow(display, screen), 0, 0, width, height, 1,
                                    BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, rootWindow, ExposureMask | KeyPressMask);
    XMapWindow(display, rootWindow);
    gc = XCreateGC(display, rootWindow, 0, nullptr);
}

void GraphicalWindow::drawRectangle(int x, int y, int width, int height, unsigned long color) {
    XSetForeground(display, gc, color);
    XFillRectangle(display, rootWindow, gc, x, y, width, height);
}

void GraphicalWindow::clear() {
    XClearWindow(display, rootWindow);
}

GraphicalWindow::~GraphicalWindow() {
    XFreeGC(display, gc);
    XDestroyWindow(display, rootWindow);
    XCloseDisplay(display);
}
*/
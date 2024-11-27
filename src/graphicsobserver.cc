#include "GraphicsObserver.h"

GraphicsObserver::GraphicsObserver(Studio &studio, int top, int bottom, int left, int right)
    : studio{studio}, top{top}, bottom{bottom}, left{left}, right{right},
      window{10 * (right - left + 1), 10 * (bottom - top + 1)} {
    studio.attach(this);
}

void GraphicsObserver::notify() {
    for (int row = top; row <= bottom; ++row) {
        for (int col = left; col <= right; ++col) {
            char ch = studio.getState(row, col);
            int color = Xwindow::White;

            // Manually check for character types
            if (ch >= 'a' && ch <= 'z') {
                color = Xwindow::Red;
            } else if (ch >= 'A' && ch <= 'Z') {
                color = Xwindow::Green;
            } else if (ch >= '0' && ch <= '9') {
                color = Xwindow::Blue;
            } else if (ch >= 33 && ch <= 126) { // Printable ASCII range excluding space
                color = Xwindow::Black;
            }

            window.fillRectangle((col - left) * 10, (row - top) * 10, 10, 10, color);
        }
    }
}

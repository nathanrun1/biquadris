#include "graphicsobserver.h"

GraphicsObserver::GraphicsObserver(Board *board)
    : board(board), window(new GraphicalWindow(500, 750)) { // Adjust window size as necessary
    if (board) board->attach(this);  // Attach observer to board if valid
}

void GraphicsObserver::notify() {
    window->clear();  // Use pointer dereferencing
    const int cellSize = 30;  // Size of each cell in pixels
    const auto &grid = board->getGrid();  // Assume getGrid() exists and provides the board layout

    for (int row = 0; row < static_cast<int>(grid.size()); ++row) {
        for (int col = 0; col < static_cast<int>(grid[row].size()); ++col) {
            if (grid[row][col].owner) {
                char color = grid[row][col].owner->getColor();
                unsigned long colorCode;

                // Map block colors to graphical colors
                switch (color) {
                    case 'I': colorCode = 0x00FFFF; break; // Cyan
                    case 'J': colorCode = 0x0000FF; break; // Blue
                    case 'L': colorCode = 0xFFA500; break; // Orange
                    case 'O': colorCode = 0xFFFF00; break; // Yellow
                    case 'S': colorCode = 0x00FF00; break; // Green
                    case 'T': colorCode = 0x800080; break; // Purple
                    case 'Z': colorCode = 0xFF0000; break; // Red
                    default:  colorCode = 0x000000; break; // Black (unknown)
                }

                window->drawRectangle(col * cellSize, row * cellSize, 
                                        cellSize, cellSize, colorCode);
            }
        }
    }
}

GraphicsObserver::~GraphicsObserver() {
    if (board) board->detach(this);
    delete window;
}

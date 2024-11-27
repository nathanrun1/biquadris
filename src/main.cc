#include "block.h"
#include "blockshape.cc"
#include "board.h"
#include "cell.h"
#include <iostream>
#include <memory>


int main(){
    try {
    // Instantiate a ConcreteBoard (derived from Board)
    std::unique_ptr<Board> board = std::make_unique<ConcreteBoard>();

    // Example: spawn a block at a specific location
    if (board->spawnBlock({0, 14})) {
        std::cout << "Block spawned successfully!" << std::endl;
    } else {
        std::cerr << "Failed to spawn block!" << std::endl;
    }

    // Perform some actions on the falling block
    board->actionLeft();
    board->actionRight();
    board->actionDown();
    board->actionDrop();

    // Output the color of a cell on the board (example at 0,0)
    char color = board->getColorAt(0, 0);
    if (color) {
        std::cout << "Color at (0,0): " << color << std::endl;
    } else {
        std::cout << "No block at (0,0)." << std::endl;
    }
} catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
}

return 0;
}
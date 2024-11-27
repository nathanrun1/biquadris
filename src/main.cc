#include <iostream>
#include <memory>
#include "game.h"
#include "textobserver.h"
#include "graphicsobserver.h"

int main(int argc, char *argv[]) {
    try {
        // Process command-line arguments
        int startLevel = 0;
        bool textMode = false;

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-text") {
                textMode = true;
            } else if (arg.substr(0, 12) == "-startlevel=") {
                startLevel = std::stoi(arg.substr(12));
            } else {
                std::cerr << "Unknown argument: " << arg << std::endl;
                return 1;
            }
        }

        // Initialize Game
        Game game;
        game.startGame(startLevel);

        // Attach observers based on mode
        std::shared_ptr<TextObserver> textObserver = std::make_shared<TextObserver>();
        game.attachObserver(textObserver.get());

        if (!textMode) {
            std::shared_ptr<GraphicsObserver> graphicsObserver = std::make_shared<GraphicsObserver>();
            game.attachObserver(graphicsObserver.get());
        }

        // Run the game loop
        std::cout << "Welcome to Biquadris!" << std::endl;
        game.run();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

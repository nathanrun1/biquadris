// #include "board.h"
#include "game.h"
// #include ..observer classes...

#include <iostream>

int main(int argc, char* argv[]) {
   // Create the two PLAYER classes as Concrete Boards
   
   for (int i = 0; i < argc - 1; i++) {
      if (argv[i] == "-text") {
         // Set to ONLY create the graphical observer
         std::cout << argv[i + 1] << std::endl;
      } else if (argv[i] == "-seed") {
         std::cout << argv[i + 1] << std::endl;
      } else if (argv[i] == "-scriptfile1") {
         std::cout << argv[i + 1] << std::endl;
      } else if (argv[i] == "-scriptfile2") {
         std::cout << argv[i + 1] << std::endl;
      } else if (argv[i] == "-startlevel") {
         std::cout << argv[i + 1] << std::endl;
      }
   }

   // Create the GAME Object using Board classes as paramters
   // Set the observer to the two PLAYER classes
   // Use Game startGame() function
}
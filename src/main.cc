// #include "board.h"
#include "game.h"
#include "textobserver.h"
// #include ..observer classes...

#include <iostream>

int main(int argc, char* argv[]) {
   // Create the two PLAYER classes as Concrete Boards
   std::cout << "main" << std::endl;
   std::mt19937 gen(10);
   std::cout << "gen constructed" << std::endl;
   Board* player1 = new ConcreteBoard(gen);
   std::cout << "board made" << std::endl;
   TextObserver textObserver(player1);
   std::cout << "main" << std::endl;
   std::cout << (bool)player1->getFallingBlock() << std::endl;
   std::cout << "color: " << player1->getColorAtRC(0, 3) << std::endl;
   player1->actionRight();
   player1->actionRight();
   player1->actionRight();
   player1->actionClockwise();
   std::cout << "color: " << player1->getColorAtRC(0, 3) << std::endl;

   // for (int i = 0; i < argc - 1; i++) {
   //    if (argv[i] == "-text") {
   //       // Set to ONLY create the graphical observer
   //       std::cout << argv[i + 1] << std::endl;
   //    } else if (argv[i] == "-seed") {
   //       std::cout << argv[i + 1] << std::endl;
   //    } else if (argv[i] == "-scriptfile1") {
   //       std::cout << argv[i + 1] << std::endl;
   //    } else if (argv[i] == "-scriptfile2") {
   //       std::cout << argv[i + 1] << std::endl;
   //    } else if (argv[i] == "-startlevel") {
   //       std::cout << argv[i + 1] << std::endl;
   //    }
   // }

   

   // Create the GAME Object using Board classes as paramters
   // Set the observer to the two PLAYER classes
   // Use Game startGame() function

   
}
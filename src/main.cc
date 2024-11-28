// #include "board.h"
#include "game.h"
#include "textobserver.h"
// #include ..observer classes...

#include <memory>
#include <sstream>
#include <iostream>

int main(int argc, char* argv[]) {
   // Start with declaring the new Boards
   std::shared_ptr<Board> player1 = std::make_shared<ConcreteBoard>();
   std::shared_ptr<Board> player2 = std::make_shared<ConcreteBoard>();
   TextObserver textObserver1(player1);
   TextObserver textObserver2(player2);

   // ...Add graphical observers here...
   // ...
   // ...

   for (int cmdIndex = 1; cmdIndex < argc; cmdIndex++) {
      // Sets the seed of the board:
      if (std::string(argv[cmdIndex]) == "-seed") {
         if (cmdIndex + 1 == argc) {
            std::cerr << "Seed NOT Provided!" << std::endl;
            return 1;
         }

         std::string seedArg = argv[cmdIndex + 1];
         std::seed_seq seedArgSeq (seedArg.begin(), seedArg.end());
         std::mt19937 gen(seedArgSeq);

         player1->setGen(gen);
         player2->setGen(gen);
         cmdIndex++;
         continue;

      // Sets the level of the board:
      } else if (std::string(argv[cmdIndex]) == "-startlevel") {
         if (cmdIndex + 1 == argc) {
            std::cerr << "Level NOT Provided!" << std::endl;
            return 1;
         }

         std::istringstream sstream{std::string(argv[cmdIndex + 1])};
         int level;
         sstream >> level;

         // Checks for invalid level inputs!
         if (sstream.fail()) {
            std::cerr << "Provided level is NOT an Integer!" << std::endl;
            return 1;
         } else if (level < 0 || level > 4) {
            std::cerr << "Provided integer level is NOT VALID!" << std::endl;
            return 1;
         }

         std::cout << "Set Level: " << level << std::endl; 
         player1->setInitialLevelNum(level);
         player2->setInitialLevelNum(level);
         cmdIndex++;
         continue;
      } else if(std::string(argv[cmdIndex]) == "-scriptfile1") {
            if (cmdIndex + 1 == argc) {
               std::cerr << "Scriptfile1 NOT Provided!" << std::endl;
               return 1;
            }

            std::string scriptfile1 = argv[cmdIndex + 1];
            std::cout << "Set Scriptfile1 " << scriptfile1 << std::endl; 
            player1->setInitialSeqFile(scriptfile1);
            cmdIndex++;
            continue;
      } else if(std::string(argv[cmdIndex]) == "-scriptfile2") {
            if (cmdIndex + 1 == argc) {
               std::cerr << "Scriptfile2 NOT Provided!" << std::endl;
               return 1;
            }

            std::string scriptfile2 = argv[cmdIndex + 1];
            std::cout << "Set Scriptfile2 " << scriptfile2 << std::endl; 
            player1->setInitialSeqFile(scriptfile2);
            cmdIndex++;
            continue;
      } else if (std::string(argv[cmdIndex]) == "-text") {
         // Delete the graphical observers here...
      } else {
         std::cerr << "Unknown Argument Provided!" << std::endl;
         return 1;
      }
   }

   
   
   // player1->actionRight();


  /*
   // Create the two PLAYER classes as Concrete Boards
   std::cout << "main" << std::endl;
   std::mt19937 gen(10);
   std::cout << "gen constructed" << std::endl;
   std::shared_ptr<Board> player1 = std::make_shared<ConcreteBoard>(gen);
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
   

   // Create the GAME Object using Board classes as paramters
   // Set the observer to the two PLAYER classes
   // Use Game startGame() function
   */

   return 0;   
}
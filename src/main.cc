// #include "board.h"
#include "game.h"
#include "textobserver.h"
// #include ..observer classes...

#include <memory>
#include <sstream>
#include <iostream>

// Helper function used to search for specific arg keywords
//    Returns the index of the word found from the command line
int searchCommand(int argc, char* argv[], std::string val) {
  for (int i = 1; i < argc; i++) {
    if (argv[i] == val) return i;
  }

  return -1;    // Default value if cmd NOT found
}

int main(int argc, char* argv[]) {
   // Start with declaring the new Boards
   std::shared_ptr<Board> player1 = std::make_shared<ConcreteBoard>();
   std::shared_ptr<Board> player2 = std::make_shared<ConcreteBoard>();

   
   // If user wishes to input their own seed, then replace the current seed with the inputted seed.
   //     If a seed is not provided, then print an error and return the program.
   int cmdIndex = searchCommand(argc, argv, "-seed");
   if (cmdIndex != -1 && cmdIndex + 1 != argc) { 
      std::string seedArg = argv[cmdIndex + 1];
      std::seed_seq seedArgSeq (seedArg.begin(), seedArg.end());
      std::mt19937 gen(seedArgSeq);

      player1->setGen(gen);
      player2->setGen(gen);
   } else if (cmdIndex + 1 == argc) {
      std::cerr << "Seed NOT Provided!" << std::endl;
      return 1;
   }

   // Setting the levels for BOTH players (if given).
   //     Otherwise set the default level for both players to 1.
   cmdIndex = searchCommand(argc, argv, "-startlevel");
   if (cmdIndex != -1 && cmdIndex + 1 != argc) { 
      std::istringstream sstream{argv[cmdIndex + 1]};
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
   } else if (cmdIndex + 1 == argc) {
      std::cerr << "Level NOT Provided!" << std::endl;
      return 1;
   }
   
   // Set player1's scriptfile (if given).
   cmdIndex = searchCommand(argc, argv, "-scriptfile1");
   if (cmdIndex != -1 && cmdIndex + 1 != argc) { 
      std::string scriptfile1 = argv[cmdIndex + 1];
      std::cout << "Set Scriptfile1 " << scriptfile1 << std::endl; 
      player1->setInitialSeqFile(scriptfile1);
   } else if (cmdIndex + 1 == argc) {
      std::cerr << "Scriptfile1 NOT Provided!" << std::endl;
      return 1;
   }

   // Set Player2's scriptfile (if given).
   cmdIndex = searchCommand(argc, argv, "-scriptfile2");
   if (cmdIndex != -1 && cmdIndex + 1 != argc) { 
      std::string scriptfile2 = argv[cmdIndex + 1];
      std::cout << "Set Scriptfile2: " << scriptfile2 << std::endl; 
      player2->setInitialSeqFile(scriptfile2);
   } else if (cmdIndex + 1 == argc) {
      std::cerr << "Scriptfile2 NOT Provided!" << std::endl;
      return 1;
   }

   // Determine whether to ONLY add the text observer.
   cmdIndex = searchCommand(argc, argv, "-text");
   if (cmdIndex != -1) {
      TextObserver textObserver1(player1);
      TextObserver textObserver2(player2);
   } else {
      TextObserver textObserver1(player1);
      TextObserver textObserver2(player2);

      // Add graphical observers HERE!
   }
   
   

   /*
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
   */
   

   // Create the GAME Object using Board classes as paramters
   // Set the observer to the two PLAYER classes
   // Use Game startGame() function

   return 0;   
}
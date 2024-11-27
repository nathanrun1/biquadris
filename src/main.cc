// #include "board.h"
// #include "block.h"
// #include "blockshape.cc"
// #include "cell.h"
// #include "game.h"

#include <random>
#include <iostream>
#include <chrono>

int main(int argc, char* argv[]) {
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator (seed);  // mt19937 is a standard mersenne_twister_engine
  int num = generator() % 100;
  
  std::cout << "Random value: " << generator() % 100 << std::endl;
  

   return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Board.h"
#include "Solver.h"

#define SIZE 16

int main(int argc, char** argv) {

  std::ifstream input;

  std::vector<short> initial(SIZE); 
  std::vector<short> final(SIZE);
 
  if (argc == 2)
    input.open(argv[1]);
  else { 
    std::cerr << "Wrong argument format" << std::endl;
    return 1;
  }

  for(int i = 0; i < SIZE; i++){
    //std::cin >> initial[i];
    input >> initial[i];
  }
  
  for(int i = 0; i < SIZE; i++){
    //std::cin >> final[i];	
    input >> final[i];
  }
  
  input.close();

  Board initialBoard(initial); 
  Board finalBoard(final); 
	
  Solver solver(initialBoard, finalBoard);

  std::string s, algorithm = "", heuristic = "";
  
  std::cout << "Enter 'exit' or a new search query (algorithm, heuristic):" << std::endl;
  getline(std::cin, s);

  while(s!= "exit"){
    algorithm = heuristic = "";
    std::istringstream iss(s);

    iss >> algorithm;
    iss >> heuristic;
    try {
      solver.solve(algorithm, heuristic);
    }catch(const char* e) {
      std::cerr << e << std::endl;
    }
    std::cout << "Enter 'exit' or a new search query (algorithm, heuristic):" << std::endl;
    getline(std::cin, s);
  }

  return 0;
}

#ifndef SOLVER_H
#define SOLVER_H

#include <bitset>
#include <vector>
#include <climits>
#include <chrono>
#include "Board.hpp"
#include "Utils.hpp"

#define MAX_DEPTH 10
#define HEURISTIC utility_fast

class Solver {

public:

  Solver();
  ~Solver();
  Solver(std::vector<Board> board, std::vector<int> columnHeight);

  int utility(std::vector<Board> curBoard);
  int utility_fast(std::vector<Board> curBoard);
  int getMove(bool player);  

private:
  
  int minimax(int depth, bool player, std::vector<Board> board, std::vector<int> columnHeight, int alpha, int beta);
  //int max_value(int depth, std::vector<Board> curBoard, std::vector<int> height, int alpha, int beta);
  //int min_value(int depth, std::vector<Board> curBoard, std::vector<int> height, int alpha, int beta);
  
  bool isLegal(std::vector<Board> curBoard, std::vector<int> height, int column, bool player);
  bool isTie(std::vector<Board> state);

  std::vector<Board> board;
  std::vector<int> columnHeight;
 
 bool maximizer;
  int  bestMove;
  int  bestVal;
  int  nodes;

};

#endif

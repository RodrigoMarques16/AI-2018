#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Board.h"
#include "Util.h"
#include <chrono>
#include <iomanip>

/*
Solver implements all the diferent search algorithms for this assignment

*/

#define NOT_VISITED 0
#define VISITING 1
#define VISITED 2

class Solver {

  Board initial;
  Board final;

  std::string moves;
  Board last;
  int found;
  int total_nodes;
  int nodes;
  int max_nodes;
  std::chrono::high_resolution_clock::time_point time;

  std::unordered_map<std::size_t, short> visited;
  std::unordered_map<std::size_t, int> cost_so_far;
  std::unordered_map<std::size_t, int> depth;
  
  std::unordered_map<std::string, std::function<int(Board&)>> costFunctions;
  std::unordered_map<std::string, std::function<void(std::string)>> solveFunctions;

 public:

  Solver(Board& initial, Board& final);
  
  int getInversions(std::vector<short> &v);
  bool isSolvable(Board& initial, Board& target);
  int calcHamming(Board& a);
  int calcManhattan(Board &a);

  void solve(std::string fn, std::string heuristic);
  void clear();
  void update_node_count(int sum);
  void print();

  bool cmp(Board* left, Board* right);

  void dfs(std::string heuristic);
  void iddfs(std::string heuristic);
  void dfs_visit(Board &b, int max_depth, int checkCycles);
  void bfs(std::string heuristic);
  void greedy(std::string heuristic);
  void a_star(std::string heuristic);
		
};

#endif

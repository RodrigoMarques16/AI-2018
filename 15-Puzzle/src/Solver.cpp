#include "Solver.h"

using namespace std;

Solver::Solver(Board& _initial, Board& _final) :
  initial(_initial),
  final(_final){ 

  costFunctions = {
    {"hamming", std::bind(&Solver::calcHamming, this, std::placeholders::_1)},
    {"manhattan", std::bind(&Solver::calcManhattan, this, std::placeholders::_1)}
  };
  
  solveFunctions = {
    {"dfs", std::bind(&Solver::dfs, this, std::placeholders::_1)},
    {"iddfs", std::bind(&Solver::iddfs, this,std::placeholders::_1)},
    {"bfs", std::bind(&Solver::bfs, this, std::placeholders::_1)},
    {"greedy", std::bind(&Solver::greedy, this, std::placeholders::_1)},
    {"a_star", std::bind(&Solver::a_star, this, std::placeholders::_1)}
  };

}

void Solver::solve(std::string fn, std::string heuristic){

  if(!solveFunctions[fn])
    throw "Invalid algorithm.";

  system("clear");
  cout << "Solving 15-Puzzle for " << fn
       << " (" << heuristic << ")" << endl
       << "==========================\n"
       << "Initial state: \n"; initial.print();
  cout << "==========================\n"
       << "Final state: \n"; final.print();
  cout << "==========================\n"
       << "Beginning search..\n" << endl;
  time = std::chrono::high_resolution_clock::now();
  solveFunctions[fn](heuristic);
}


void Solver::print() { 

  std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - time;

  double mem = (max_nodes * 1.0 * sizeof(Board)) / 1000000;
 
  if (!found) cout << "Couldn't find a solution within the limits" << endl;
  else{
    cout << "Solution found!" << endl;
    last.print();
    cout << "\nOperators: " << last.moves
       << "\nNumber of moves: " << last.moves.size() << endl;
  }

  cout << std::fixed;
  cout << std::setprecision(6)
       << "\nExecution length: " << elapsed.count() << " seconds" << endl;

  cout << std::setprecision(6)  
       << "\nMaximum number of nodes in memory: " << max_nodes << endl
       << "Memory used: " << mem << "MB" << endl
       << "Total nodes generated: " << total_nodes << endl; 

  cout << endl;
}


int Solver::getInversions(std::vector<short> &v) {
  int inversions = 0;
  for(unsigned int i = 0; i < v.size(); i++) {
    for(unsigned int j = i; j < v.size(); j++) {
      if (v[i] > v[j] && v[i] != 0 && v[j] != 0) {
	inversions++;
      }
    }
  }
  return inversions;
}

bool Solver::isSolvable(Board& initial, Board& final) { 
  
  int invI = getInversions(initial.values);
  int invF = getInversions(final.values);

  int blankRowI = 4 - getX(initial.blankIndex);
  int blankRowF = 4 - getX(final.blankIndex);

  return ((invI % 2 == 0) == (blankRowI % 2 == 1)) == ((invF % 2 == 0) == (blankRowF % 2 == 1));
}

int Solver::calcHamming(Board& a){
  int sum = 0;
  for(unsigned int i = 0; i < a.values.size(); i++){
    if (a.values[i] != final.values[i]){
      sum++;
    }
  }
  return sum;
}

int Solver::calcManhattan(Board& a) {	
  int sum = 0;
  for(unsigned int index = 0; index < a.values.size(); index++){
    unsigned int targetIndex = findInVector(final.values, a.values[index]);
    if (index != targetIndex) {
      int x1 = getX(index);
      int y1 = getY(index);
      int x2 = getX(targetIndex);
      int y2 = getY(targetIndex);
      sum += abs(x2-x1) + abs(y2-y1);
    }  
  }
  return sum;
}

void Solver::clear(){
  visited.clear();
  depth.clear();
  cost_so_far.clear();
  found = 0;
  total_nodes = 2;
  nodes = 2;
  max_nodes = nodes;
  initial.cost = 0;
  initial.moves = "";
  initial.op = -1;
}

void Solver::update_node_count(int sum){
  nodes += sum;
  if (sum == 1) total_nodes += sum;
  if(nodes > max_nodes) max_nodes = nodes;
}

void Solver::dfs(std::string heuristic) {
  clear();
  int maxcost = string_to_int(heuristic);
  if (maxcost == 0) maxcost = 30;
  dfs_visit(initial, maxcost, 1);
  print();
}

void Solver::iddfs(std::string heuristic) {
  int i = 1;
  int maxcost = string_to_int(heuristic);
  if (maxcost == 0) maxcost = 30;
  do {
    clear();
    dfs_visit(initial, i, 0);
  }while(++i <= maxcost && !found);
  print();
}

void Solver::dfs_visit(Board &board, int max_cost, int checkCycles){

  visited[board.hash] = VISITING;

  if (board == final){
    found = 1;
    last = board;
    return;
  }

  if(board.cost <= max_cost && !found) {
    for(int dir = 0; dir < 4; dir++){
      Board * b = board.move((DIRECTION) dir);
      if(b != NULL){
	update_node_count(1);
	if (!checkCycles || (checkCycles && visited[b->hash] == NOT_VISITED)){
	  b->cost = board.cost+1;
	  dfs_visit(*b, max_cost, checkCycles);
	  delete b;
	  update_node_count(-1);
	} 
      }
    }
  }

  visited[board.hash] = VISITED;

}

void Solver::bfs(std::string heuristic){

  clear();

  int maxdepth = string_to_int(heuristic);
  if (maxdepth == 0)
    throw "Limit BFS to prevent infinite execution";

  std::queue<Board*> q;

  q.push(&initial);
  depth[initial.hash] = 0;

  while(!q.empty()){

    Board * curBoard = q.front();
    q.pop();

    visited[curBoard->hash] = VISITED;
    
    if (*curBoard == final){
      found = 1;
      last = *curBoard;
      break;
    }
    
    if(depth[curBoard->hash] > maxdepth)
      break;

    for(int dir = 0; dir < 4; dir++){
      Board * next = curBoard->move((DIRECTION) dir);    
      if(next != NULL){
	depth[next->hash] = depth[curBoard->hash]++;
	update_node_count(1);
	next->cost = curBoard->cost+1;
	q.push(next);
      }
    }

    curBoard = NULL;
    delete curBoard;
    update_node_count(-1);
  }

  print();
  return;
}

void Solver::greedy(std::string heuristic){
  
  clear();

  //int maxdepth = 250;

  auto calcCost = costFunctions[heuristic];
  if (!calcCost)
    throw "Invalid heuristic";

  auto cmp = [](Board* left, Board* right) {return left->cost > right-> cost;};
  std::priority_queue<Board*, std::vector<Board*>, decltype(cmp)> q(cmp);
  
  initial.cost = calcCost(initial);
  cost_so_far[initial.hash] = calcCost(initial);
  initial.cost = cost_so_far[initial.hash];
  depth[initial.hash] = 0;

  q.push(&initial);
  
  while(!q.empty()){

    Board * curBoard = q.top();
    q.pop();

    visited[curBoard->hash] = VISITED;

    if (*curBoard == final){
      found = 1;
      last = *curBoard;
      break;
    }

    //if(depth[curBoard->hash] > maxdepth)
    //break;

    for(int dir = 0; dir < 4; dir++){
      Board * next = curBoard->move((DIRECTION) dir);
      if(next != NULL) {
	int newCost = calcCost(*next);
	if (visited[next->hash] != VISITED || cost_so_far[next->hash] > newCost) { 
	  update_node_count(+1);
	  next->cost = newCost;
	  cost_so_far[next->hash] = newCost;
	  depth[next->hash] = depth[curBoard->hash]++;
	  q.push(next);
	}
      }
    }
    
    curBoard = NULL;
    delete curBoard;
    update_node_count(-1);
  }

  print();
  return;
}

void Solver::a_star(std::string heuristic){
  
  clear();
  
  //int maxdepth = 250;

  auto calcCost = costFunctions[heuristic];
  if (!calcCost)
    throw "Invalid heuristic";

  auto cmp = [](Board* left, Board* right) {return left->cost > right-> cost;};
  std::priority_queue<Board*, std::vector<Board*>, decltype(cmp)> q(cmp);
  
  initial.cost = calcCost(initial);
  q.push(&initial);
  cost_so_far[initial.hash] = 0;
  
  while(!q.empty()){

    Board * curBoard = q.top();
    q.pop();
    
    visited[curBoard->hash] = VISITED;
    
    if (*curBoard == final){
      found = 1;
      last = *curBoard;
      break;
    }

    //if(depth[curBoard->hash] > maxdepth)
    //break;

    for(int dir = 0; dir < 4; dir++){
      Board * next = curBoard->move((DIRECTION) dir);
      if(next != NULL){
	int newCost = cost_so_far[curBoard->hash] + 1;
	if (visited[next->hash] != VISITED || newCost < cost_so_far[next->hash]){
	  update_node_count(1);
	  cost_so_far[next->hash] = newCost;
	  next->cost = newCost + calcCost(*next);
	  q.push(next);
	}
      }
    }
    
    curBoard = NULL;
    delete curBoard;
    update_node_count(-1);
  }

  print();
  return;
}

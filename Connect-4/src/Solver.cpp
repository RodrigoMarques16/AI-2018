#include "Solver.hpp"

const int MOVE_BONUS    = 16;
const int MAX           = 512;
const int MIN           = -MAX;
const int SCORES[4]     = { 0, 1, 10, 50 };
const int MULTIPLIER[2] = { -1, 1 };
const int OFFSETMAP[4]  = { 1, HEIGHT, HEIGHT+1, HEIGHT+2 };   

Solver::Solver()
{ /* do nothing */ }

Solver::~Solver() {
  /* destructor */
}

Solver::Solver(std::vector<Board> b, std::vector<int> h) : 
  board(b),
  columnHeight(h)
{  /* do nothing */ }


int Solver::utility(std::vector<Board> curBoard) {
  
  int value = 0;

  segment segmentO;
  segment segmentX;
  segment merged;
  
  for(int direction = 0; direction < 4; direction++) {
    for (int i = 0; i < (WIDTH * HEIGHT+1) - OFFSETMAP[direction]; i += OFFSETMAP[direction]) {

      // finding segments of four positions would probably 
      // be much faster if we were using bitmasks

      segmentO   = curBoard[0].getSegment(i, OFFSETMAP[direction]);
      segmentX   = curBoard[1].getSegment(i, OFFSETMAP[direction]);
      merged     = segmentO | segmentX;
      
      int countO = segmentO.count();
      int countX = segmentX.count();
      int count  = merged.count();

      if (countO == count) {
	// only O pieces
	//cout << "counted " << countO << " O pieces" << endl;
	value += SCORES[countO] * MULTIPLIER[!maximizer];
	    
      }
      else if (countX == count) {
	// only X pieces
	//cout << "counted " << countX << " X pieces" << endl;
	value += SCORES[countX] * MULTIPLIER[maximizer];
      }
      // else it's a mix of pieces, value isn't updated
    }
  }
  //cout << "utility returned " << value << endl;
  return value;
}

int Solver::utility_fast(std::vector<Board> curBoard) {
  int value = curBoard[maximizer].threeSegments() - curBoard[!maximizer].threeSegments();
   value += curBoard[maximizer].twoSegments() - curBoard[!maximizer].twoSegments();
  //cout << "utility returned " << value << endl;
  return value;
}

bool Solver::isTie(std::vector<Board> state) {
  return (state[0].count() + state[1].count()) == BITSIZE;
} 

int Solver::getMove(bool player) {

  nodes = 0;
  bestMove = -1;
  bestVal = INT_MIN;
  maximizer = player;

  std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

  minimax(0, maximizer, board, columnHeight, INT_MIN, INT_MAX);

  std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - time;
  std::cout << "Pesquisa terminada após " << elapsed.count() << " segundos e "
	    << nodes << " nós percorridos\n";

  return bestMove;
}

int Solver::minimax(int depth, bool player, std::vector<Board> curBoard, std::vector<int> height, int alpha, int beta) {
  
  nodes++;

  int mult;
  if(player == maximizer) 
    mult = MULTIPLIER[1];
  else mult = MULTIPLIER[0];

  if (curBoard[player].isWin(false)) {
    return (MAX + MOVE_BONUS / depth) * mult; 
  }

  if (isTie(curBoard)) {
    //cout << "no more moves here" << endl;
    return MOVE_BONUS * mult;
  }
  
  if (depth == MAX_DEPTH) {
    //cout << "max depth" << endl;
    return HEURISTIC(curBoard) + MOVE_BONUS * mult;
  }
  
  int max = INT_MIN, min = INT_MAX;

  for(int column = 0 ; column < WIDTH ; column++){
    if(height[column] < HEIGHT) {	
			
      std::vector<Board> nextBoard(curBoard);
      std::vector<int>   nextHeight(height);
      
      nextBoard[player].set(column, height[column]);
      nextHeight[column]++;
      
      int value = minimax(depth + 1, !player, nextBoard, nextHeight, alpha, beta);
			
      // if(depth == 0) std::cout << "Column" << column+1 << " is valued " << value << std::endl;
			
      if (player == maximizer) {
	if (value > max) {
	  max = value;
          if (depth == 0) {
            bestMove = column;
	  }
	}
        alpha = getMax(value, alpha);
      }
      else if (player == !maximizer) {
	if (value < min) {
	  min = value;
	  if (depth == 0)
            bestMove = column;
        } 
        beta = getMin(value, beta);
      }
      
      if(beta <= alpha) break; // fail-soft doesn't seem to lose compared to fail-hard
      
    }
  }
	
  if(player == maximizer) 
    return max;
  return min;
  
}

/*
int Solver::max_value(int depth, std::vector<Board> curBoard, std::vector<int> height, int alpha, int beta) {
  
  if (curBoard[1].isWin()) 
    return MAX * MULTIPLIER[1];
  
  if (depth == MAX_DEPTH) 
    return utility2(curBoard) + MULTIPLIER[1];
  
  int value = MIN;
  for(int column = 0 ; column < WIDTH ; column++) {
    if (height[column] < HEIGHT) {
	    
      std::vector<Board> nextBoard(curBoard);
      std::vector<int>   nextHeight(height);
	    
      nextBoard[1].set(column, height[column]);
      nextHeight[column]++;
  		
      int v = min_value(depth + 1, nextBoard, nextHeight, alpha, beta);
      
      if (v >= value) {
	value = v;
	//bestMove = column;
      }
      
      if (v >= beta){
	bestMove = column;
	return value;
      }
      alpha = getMax(alpha, v);
      
    }
  }
  
  return value;
}

int Solver::min_value(int depth, std::vector<Board> curBoard, std::vector<int> height, int alpha, int beta) {
  
  if (curBoard[0].isWin()) 
    return MAX * MULTIPLIER[0];
  
  if (depth == MAX_DEPTH) 
    return utility2(curBoard) + MULTIPLIER[0];
  
  int value = MIN;
  for(int column = 0 ; column < WIDTH ; column++) {
    if (height[column] < HEIGHT) {
	    
      std::vector<Board> nextBoard(curBoard);
      std::vector<int>   nextHeight(height);
	    
      nextBoard[0].set(column, height[column]);
      nextHeight[column]++;
  		
      int v = max_value(depth + 1, nextBoard, nextHeight, alpha, beta);
      
      if (v <= value) {
	value = v;
	//bestMove = column;
      }
      
      if (v <= alpha){
	bestMove = column;
	return value;
      }
      beta = getMin(beta, v);
      
    }
  }
  
  return value;
}

*/


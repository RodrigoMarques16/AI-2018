#ifndef BOARD_H
#include "Board.hpp"
#endif

int _offsetmap[4] = { 1, HEIGHT, HEIGHT+1, HEIGHT+2 }; 

int indexes[WIDTH][HEIGHT+1] = {
  0,   1,  2,  3,  4,  5,  6,
  7,   8,  9, 10, 11, 12, 13,
  14, 15, 16, 17, 18, 19, 20,
  21, 22, 23, 24, 25, 26, 27,
  28, 29, 30, 31, 32, 33, 34,
  35, 36, 37, 38, 39, 40, 41,
  42, 43, 44, 45, 46, 47, 48
};

int getIndex(int x, int y) {
  return indexes[x][y];
}

Board::Board() { 
}

Board::Board(const Board& other) :
  board(other.board)
{ /* do nothing */}

Board::~Board() {
  /* destructor */
}

Board& Board::operator=(Board other) {
  std::swap(*this, other);
  return *this;
}

bitboard Board::getBoard() {
  return this->board;
}

bool Board::get(int x, int y) {
  try {
    return this->board[getIndex(x,y)];
  } 
  catch(...) {
  }
}
bool Board::set(int x, int y) {
  try {
    this->board.set(getIndex(x,y), true);
    return true;
  } 
  catch(...) {
    return false;
  }
}

int Board::count() {
  return board.count();
}

bool Board::checkFour(int offset) {
  //bitboard tmp = board & board >> offset;
  //return (tmp & (tmp >> offset * 2)).any();
  return ((board & board >> offset) & (board >> 2*offset & board >> 3*offset)).any();
}

int Board::checkThree(int offset) { 
  return (board & board >> offset & board >> 2*offset).count();
}

int Board::checkTwo(int offset) { 
  return (board & board >> offset).count();
}

bool Board::isWin(bool debug) {
  for(int i = 0; i < 4; i++) 
    if (checkFour(_offsetmap[i])){
      if(debug) {
	std::cout << board.to_string()                      << std::endl;
	std::cout << (board << _offsetmap[i]).to_string()   << std::endl;
	std::cout << (board << 2*_offsetmap[i]).to_string() << std::endl;
	std::cout << (board << 3*_offsetmap[i]).to_string() << std::endl;
      }
      return true;
    }
  return false;
}

int Board::threeSegments() {
  int count = 0;
  for(int i = 0; i < 4; i++) 
    count += checkThree(_offsetmap[i]);
  return count;
}

int Board::twoSegments() {
  int count = 0;
  for(int i = 0; i < 4; i++) 
    count += checkTwo(_offsetmap[i]);
  return count;
}

segment Board::getSegment(int pos, int offset) {
  segment seg;
  for(int i = 0; i < 4; i++) {
    seg.set(i, board[pos]);
    pos += offset;
  }
  return seg;
}						

bitboard Board::merge(const Board &other) { 
  return this->board | other.board;
}

void Board::draw() {
  std::cout << board.to_string() << std::endl;
}

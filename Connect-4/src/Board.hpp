#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "Utils.hpp"

typedef std::bitset<BITSIZE+WIDTH> bitboard;
typedef std::bitset<4> segment;

class Board { 
  
public:
  
  Board();
  ~Board(); 
  Board(const Board &other);

  Board& operator=(Board other);

  bitboard getBoard();
  bitboard getCurrentBoard();
  bitboard merge(const Board &other);
  segment  getSegment(int post, int offset);
  
  bool     get(int x, int y);
  bool     set(int x, int y);
  bool     isWin(bool debug=false);
  bool     isWin(bitboard b);
  int      threeSegments();
  int      twoSegments();
  int      count();
  void     draw();

private:

  bitboard board;
  
  bool checkFour(int offset);
  int  checkThree(int offset);
  int  checkTwo(int offset);
  
};

#endif

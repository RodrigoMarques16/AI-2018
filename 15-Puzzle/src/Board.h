#ifndef BOARD_H
#define BOARD_H

#include <iostream>	 // std::strnig
#include <vector>	 // std::vector

/*
Board is the class used to represent a state of the 15-Puzzle game

The board's state is stored in a vector and is also represented by a hash
The string moves represents all the operators used to get to the current state

*/

typedef enum {UP, DOWN, LEFT, RIGHT} DIRECTION;

class Board {
 public:

  std::vector<short> values;
  std::size_t hash;
  std::string moves;

  unsigned short blankIndex;
  int cost;

  int op;
  
  Board();
  Board(const std::vector<short>& _values);
  Board(const Board& other);
  Board * move(DIRECTION Dir);
  
  bool operator==(const Board &other) const;		
  
  bool isMoveValid(DIRECTION dir);
  void print();
};

#endif

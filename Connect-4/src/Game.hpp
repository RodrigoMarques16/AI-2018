#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cctype>

#include "Board.hpp"
#include "Solver.hpp"
#include "Utils.hpp"

#define PLAYER 0
#define COMPUTER 1

class Game {

public:

  Game();
  bool play();

private:

  std::vector<Board> board; // 0 is player, 1 is computer
  std::vector<int>   columnHeight;

  bool player;
  int  turn;

  void init();
  void printBoard();
  bool makeMove(int column, bool player);
  int  getMove();
  char getPiece(int i, int j);
};

#endif

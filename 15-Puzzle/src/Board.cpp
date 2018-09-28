#include "Board.h"

#ifndef UTIL_H
#include "Util.h"
#endif

using namespace std;

// Lookup table to determine if a certain move is possible for a certain index in the values vector
int validMove[4][16] = {
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //up
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}, // down
  {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, // left
  {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}  // right
};

// The difference in indexes in the vector relative to each move
// up means going back 4 indexes, down going forward 4, ...
int add[4] = {-4, 4, -1, 1};

// To represent the directions as characters
char ops[4] = {'u', 'd', 'l', 'r'};

// To help prevent a board from creating the board that created it
// as would happen in board.move(UP)->move(DOWN)
int prevOp[4] = {DOWN, UP, RIGHT, LEFT};


Board::Board(){
  /* do nothing */
}

Board::Board(const std::vector<short>& _values) :
  values(_values) { 
  hash = getHash(values);
  for(unsigned int i = 0; i < values.size(); i++) {
    if (values[i] == 0)
      this->blankIndex = i;
  }
}

Board::Board(const Board& other) :
  values(other.values),
  hash(other.hash),
  blankIndex(other.blankIndex)
{ /* nothing to do */ }


bool Board::operator==(const Board& other) const{
  return hash == other.hash;
}

bool Board::isMoveValid(DIRECTION dir){
  if (op < 0 || op > 4)
    return validMove[dir][blankIndex];
  return validMove[dir][blankIndex] && dir != prevOp[op];
}

Board * Board::move(DIRECTION dir) {

  if (this->isMoveValid(dir)) {
    Board * b = new Board(this->values);
    int newIndex = blankIndex + add[dir];

    // swap pieces
    std::swap(b->values[blankIndex], b-> values[newIndex]);
    //b->values[blankIndex] = b->values[newIndex]; 
    b->blankIndex = newIndex;
    //b->values[b->blankIndex] = 0;
    
    // update hash
    b->hash = getHash(b->values);

    // update data
    b->moves = moves + ops[dir];
    b->op = dir;
    //b->prev = this;
    b->cost = cost;

    return b;
  }
 
  return NULL;
}

void Board::print() {
  for(unsigned int i = 0; i < values.size(); i++){
    std::cout << values[i] << " ";
    if ((i+1)%4 == 0) std::cout << std::endl;
  }
}

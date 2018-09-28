#include "Game.hpp"

char playerCharacter[3] = {'O', 'X', '-'};

Game::Game() {
  /* do nothing */
}

void Game::init() {

  board.clear();
  columnHeight.clear();

  board.push_back(Board());
  board.push_back(Board());

  player = PLAYER;
  turn = 1;

  for(int i = 0; i < WIDTH; i++)
    columnHeight.push_back(0);

}

int Game::getMove() {
  char c;
  std::cin >> c;
  int move = toDigit(c);
  
  if (move == -1) // not a digit
    return -1;

  if (move > WIDTH || move < 1) // out of bounds
    return -1;

  if (columnHeight[move-1] >= HEIGHT) // column is full
    return -1;
  
  return move-1;
}

bool Game::makeMove(int column, bool player) {
  /*
  if (columnHeight[column] >= HEIGHT) {
    std::cout << "Jogada impossivel\n";
    board[0].draw();
    board[1].draw();
    std::cout << board[0].getIndex(column, columnHeight[column]) << std::endl;
    return false;
  }
  */

  board[player].set(column, columnHeight[column]);
  columnHeight[column]++;
  return true;
}

bool Game::play() {

  int column;
  bool playAgain = false;
  
  init();

  printBoard();
  
  while(true) {

    std::cout << "Turno do jogador " << playerCharacter[player] << std::endl;
    
    if (player == COMPUTER) {
      Solver solver(board, columnHeight);
      column = solver.getMove(player);
      std::cout << "Computador jogou na coluna "  << column+1 << std::endl;
    }
    else if (player == PLAYER) {
      std::cout << "Insira o numero da coluna a jogar:" << std::endl;
      column = getMove();
      while(column == -1) {
	std::cout << "Jogada invalida." << std::endl;
	std::cout << "Insira o número da coluna a jogar:" << std::endl;
	column = getMove();
      }
    }
    
    if (!makeMove(column, player))
      break;

    printBoard();

    if (board[player].isWin(false)) {
      std::cout << "O JOGADOR " << playerCharacter[player] << " GANHOU!" << std::endl;
      break;
    }
    else if ( turn == BITSIZE) {
      std::cout << "JOGO ACABOU EM EMPATE" << std::endl;
      break;
    }
    
    player = !player;
    turn++;
    
  }

  char c;
  std::cout << "Jogar outra vez? y/n" << std::endl;
  std::cin >> c;

  if ( c == 'y')
    playAgain = true;

  system("clear");

  return playAgain;
 
}

char Game::getPiece(int i, int j) {
  if (board[0].get(i,j))
    return playerCharacter[0];
  else if(board[1].get(i,j)) 
    return playerCharacter[1];
  else return playerCharacter[2];
}

void Game::printBoard() {

  // board[0].draw(); 
  // board[1].draw();

  std::cout << "\n     1   2   3   4   5   6   7\n"
            << "   =============================\n";

  for(int y = HEIGHT-1; y >= 0; y--) {
    std::cout << " " << y+1 << " |";
    for(int x = 0; x < WIDTH; x++) {
      std::cout << " " << getPiece(x,y) << " |";
    }
    std::cout << "\n   =============================\n";
  }

  std::cout << std::endl;
}



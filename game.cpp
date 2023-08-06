#include "game.hpp"

Game::Game(int size) : board(size) {}

void Game::Start() {
  board.Display();
  int firstMove = GetMove();

  board.FirstMove(firstMove);
}

void Game::Update() {
  do
  {
    board.Display();

    int move = GetMove();

    board.ExecuteMove(move);
  } while (!board.GetState() and !board.CheckWin());

  if (board.CheckWin()) {
    std::cout << "You won" << std::endl;
  }
  else
  {
    std::cout << "Hit a mine" << std::endl;
  }
}

int Game::GetMove() {
  int x = 0;
  int y = 0;

  while (true) {
    std::cout << std::endl;
    std::cout << "Enter your move (x y):" << std::endl;

    if (std::cin >> x >> y) {
      if (x >= 1 && x <= board.GetSize() && y >= 1 && y <= board.GetSize()) {
        break;
      } else {
        std::cout << "Invalid move. Please enter numbers within the board's dimensions." << std::endl;
      }
    } else {
      std::cout << "Invalid input. Please enter two integers." << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  int index = (x - 1) * board.GetSize() + (y - 1);
  return index;
}

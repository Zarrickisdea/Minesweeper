#include "game.hpp"

Game::Game(int size) : board(size) {}

void Game::Start() {
  Update();
}

void Game::Update() {
  board.Display();
  int move = GetMove();

  board.ExecuteMove(move);
  board.PlaceMines(move);
  board.Display();
}

int Game::GetMove() {
  std::cout << std::endl;
  std::cout << "Enter your move:" << std::endl;
  int x;
  int y;
  std::cin >> x;
  std::cin >> y;
  std::cout << std::endl;

  int index = (x - 1) * board.GetSize() + (y - 1);
  return index;
}
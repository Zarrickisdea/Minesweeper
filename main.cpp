#include "board.hpp"

int main () {
  Board board(5);

  board.Display();
  std::cout << std::endl;
  std::cout << "Enter your move:" << std::endl;
  int x;
  int y;
  std::cin >> x;
  std::cin >> y;

  int index = (x-1) * board.GetSize() + (y-1);
  board.PlaceMines(index);
}